#ifndef LFW_CORE_INSTFACTORY_H
#define LFW_CORE_INSTFACTORY_H

#include "lfw-core/core.hpp"


#include <cstddef>
#include <cstdio>
#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN


// ============================================================
// InstFactory — 实例工厂，带对象池和命名实例管理
//
// Kind 支持任意类型，默认 std::string，也可传 int / enum。
//
// 用法:
//   InstFactory<Bullet>            → Kind = std::string
//   InstFactory<Bullet, int>       → Kind = int
//   InstFactory<Bullet, HeroType>  → Kind = 枚举
// ============================================================
template <typename T, typename K = std::string>
class InstFactory
{
public:
  using Kind = K;

  /// 创建器 — 对应 TypeScript 的 IInstCreator
  struct Creator
  {
    std::function<std::unique_ptr<T>()> create;
    std::function<void(T &)> reset;
    std::function<void(T &)> init; // optional
  };

  virtual ~InstFactory() = default;

  /// 子类返回 TAG 标识（用于错误信息）
  virtual std::string tag() const = 0;

  /// 从实例中读取 kind
  virtual Kind get_kind(const T &inst) const = 0;

  /// 将 kind 写入实例
  virtual void set_kind(T &inst, Kind kind) = 0;

  // ----------------------------------------------------------
  /// 注册一个 kind 的创建器
  void register_kind(const Kind &kind, Creator creator)
  {
    if (!creator.create)
      throw std::runtime_error("[" + tag() + "::register] create is null");
    if (!creator.reset)
      throw std::runtime_error("[" + tag() + "::register] reset is null");
    if (kind == Kind{})
      throw std::runtime_error("[" + tag() + "::register] kind is default");

    if (_creators.find(kind) != _creators.end())
    {
      // 重复注册 — 对应 Ditto.warn
      std::fprintf(stderr, "[WARN] [%s::register] duplicate kind=%s, overriding\n",
                   tag().c_str(), kind_to_string(kind).c_str());
    }
    _creators[kind] = std::move(creator);
  }

  // ----------------------------------------------------------
  /// 获取一个实例，kind + key 标识命名实例
  T *get(const Kind &kind, const std::string &key = "",
         std::function<void(T &)> init = nullptr)
  {
    auto it = _creators.find(kind);
    if (it == _creators.end())
      throw std::runtime_error("[" + tag() + "::get] invalid kind " + kind_to_string(kind));

    auto &creator = it->second;

    // 检查命名实例
    if (!key.empty())
    {
      auto kkey = make_key(kind, key);
      auto inst_it = _instances.find(kkey);
      if (inst_it != _instances.end())
        return inst_it->second.get();
    }

    // 从池中取或新建
    std::unique_ptr<T> obj;
    auto pool_it = _pools.find(kind);
    if (pool_it != _pools.end() && !pool_it->second.empty())
    {
      obj = std::move(pool_it->second.back());
      pool_it->second.pop_back();
    }
    if (!obj)
      obj = creator.create();

    T *raw = obj.get();

    // 重置 + init
    creator.reset(*raw);
    set_kind(*raw, kind);
    if (creator.init)
      creator.init(*raw);
    if (init)
      init(*raw);

    // 管理生命周期
    if (!key.empty())
    {
      // 命名实例 → 存入 instances
      auto kkey = make_key(kind, key);
      _instances[kkey] = std::move(obj);
    }
    else
    {
      // 无名实例 → 存入 holdings 保持有效
      _holdings.push_back(std::move(obj));
    }

    return raw;
  }

  // ----------------------------------------------------------
  /// 回收命名实例到对象池
  void recycle(const Kind &kind, const std::string &key)
  {
    auto kkey = make_key(kind, key);
    auto it = _instances.find(kkey);
    if (it == _instances.end())
      throw std::runtime_error("[" + tag() + "::recycle] instance not found: " + kkey);
    _pools[kind].push_back(std::move(it->second));
    _instances.erase(it);
  }

  /// 通过裸指针回收（会从 holdings 中找到并转移所有权）
  void recycle(T &inst)
  {
    auto kind = get_kind(inst);
    if (kind == Kind{})
      throw std::runtime_error("[" + tag() + "::recycle] invalid kind");

    // 从 holdings 中找到匹配的实例
    for (auto it = _holdings.begin(); it != _holdings.end(); ++it)
    {
      if (it->get() == &inst)
      {
        _pools[kind].push_back(std::move(*it));
        _holdings.erase(it);
        return;
      }
    }
    throw std::runtime_error("[" + tag() + "::recycle] instance not found in holdings");
  }

  /// 回收实例到对象池（转移 unique_ptr 所有权）
  void recycle(std::unique_ptr<T> obj)
  {
    if (!obj)
      throw std::runtime_error("[" + tag() + "::recycle] null pointer");

    auto kind = get_kind(*obj);
    if (kind == Kind{})
      throw std::runtime_error("[" + tag() + "::recycle] invalid kind");

    _pools[kind].push_back(std::move(obj));
  }

  // ----------------------------------------------------------
  /// 检查命名实例是否存在
  bool exists(const Kind &kind, const std::string &key) const
  {
    auto kkey = make_key(kind, key);
    return _instances.find(kkey) != _instances.end();
  }

  /// 获取命名实例（不创建）
  T *find(const Kind &kind, const std::string &key) const
  {
    auto kkey = make_key(kind, key);
    auto it = _instances.find(kkey);
    return it != _instances.end() ? it->second.get() : nullptr;
  }

  /// 清除所有池和命名实例
  void clear()
  {
    _pools.clear();
    _instances.clear();
    _holdings.clear();
  }

protected:
  std::map<Kind, Creator> _creators;
  std::map<Kind, std::vector<std::unique_ptr<T>>> _pools;
  std::vector<std::unique_ptr<T>> _holdings; // 保存无名实例的生命周期
  std::map<std::string, std::unique_ptr<T>> _instances;

private:
  static std::string make_key(const Kind &kind, const std::string &key)
  {
    return kind_to_string(kind) + "##" + key;
  }

  // Kind → string（用于复合键）
  template <typename U = K>
  static std::string kind_to_string(const U &k)
  {
    if constexpr (std::is_same_v<U, std::string>)
      return k;
    else if constexpr (std::is_arithmetic_v<U>)
      return std::to_string(k);
    else
      return std::to_string(static_cast<int>(k));
  }
};


LFW_NS_END

#endif // LFW_CORE_INSTFACTORY_H
