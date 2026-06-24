#ifndef LFW_CORE_SIGNAL_HPP
#define LFW_CORE_SIGNAL_HPP

#include <cstddef>
#include <deque>
#include <memory>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

// ============================================================
// Signal — 单个事件的信号，零类型擦除
// 可重入安全（emit 中再次 emit 会排队）
// emit 期间的 add/disconnect 会延迟到 emit 结束后执行
// ============================================================
template <typename... Args>
class Signal
{
public:
  // 监听器抽象基类 — 用户通过继承实现 invoke
  struct IListener
  {
    virtual ~IListener() = default;
    virtual void invoke(Args... args) = 0;
  };

  // 包装：成员函数指针
  template <typename T>
  struct MemberFnListener : IListener
  {
    T *obj;
    void (T::*cb)(Args...);

    MemberFnListener(T *o, void (T::*c)(Args...)) : obj(o), cb(c) {}
    void invoke(Args... args) override
    {
      (obj->*cb)(std::move(args)...);
    }
  };

  // 包装：普通函数指针 或 静态函数
  struct FnPtrListener : IListener
  {
    void (*cb)(Args...);
    explicit FnPtrListener(void (*c)(Args...)) : cb(c) {}
    void invoke(Args... args) override
    {
      cb(std::move(args)...);
    }
  };

private:
  struct Entry
  {
    std::unique_ptr<IListener> listener;
    bool once = false;
  };

  bool _emiting = false;
  std::deque<std::tuple<Args...>> _pendings;
  std::unordered_map<std::size_t, Entry> _entries;
  std::size_t _next_id = 0;

  struct DeferredOp
  {
    enum Type
    {
      Add,
      Del
    };
    Type type;
    std::size_t id;
    Entry entry; // Add 时有效
  };
  std::vector<DeferredOp> _waits;

  void flush_pendings()
  {
    if (_pendings.empty())
      return;
    auto args = std::move(_pendings.front());
    _pendings.pop_front();

    _emiting = true;
    // 快照当前 id 列表
    std::vector<std::size_t> ids;
    ids.reserve(_entries.size());
    for (auto &[id, _] : _entries)
      ids.push_back(id);

    for (auto id : ids)
    {
      auto it = _entries.find(id);
      if (it == _entries.end())
        continue;
      // 用 std::apply 将 tuple<Args...> 解包后传给 invoke(Args...)
      std::apply([&](Args... unpacked)
                 { it->second.listener->invoke(std::move(unpacked)...); }, args);
      if (it->second.once)
      {
        _waits.push_back({DeferredOp::Del, id, {}});
      }
    }
    flush_waits();
    _emiting = false;
  }

  void flush_waits()
  {
    for (auto &op : _waits)
    {
      if (op.type == DeferredOp::Add)
      {
        _entries[op.id] = std::move(op.entry);
      }
      else
      {
        _entries.erase(op.id);
      }
    }
    _waits.clear();
  }

public:
  ~Signal() = default;
  Signal() = default;
  Signal(Signal &&) = default;
  Signal &operator=(Signal &&) = default;

  // --- 禁止拷贝（因为 unique_ptr）---
  Signal(const Signal &) = delete;
  Signal &operator=(const Signal &) = delete;

  // --- 注册 ---

  /** 注册成员函数，返回 id（可用来 disconnect） */
  template <typename T>
  std::size_t on(T *obj, void (T::*cb)(Args...))
  {
    return add_impl(std::make_unique<MemberFnListener<T>>(obj, cb), false);
  }

  /** 注册一次性成员函数 */
  template <typename T>
  std::size_t once(T *obj, void (T::*cb)(Args...))
  {
    return add_impl(std::make_unique<MemberFnListener<T>>(obj, cb), true);
  }

  /** 注册函数指针 */
  std::size_t on_fn(void (*cb)(Args...))
  {
    return add_impl(std::make_unique<FnPtrListener>(cb), false);
  }

  /** 注册自定义 IListener */
  std::size_t add(std::unique_ptr<IListener> listener, bool once = false)
  {
    return add_impl(std::move(listener), once);
  }

  /** 按 id 取消注册（可重入安全） */
  void disconnect(std::size_t id)
  {
    if (_emiting)
    {
      _waits.push_back({DeferredOp::Del, id, {}});
    }
    else
    {
      _entries.erase(id);
    }
  }

  /** 触发信号 */
  void emit(Args... args)
  {
    _pendings.emplace_back(std::move(args)...);
    if (_emiting)
      return;
    while (!_pendings.empty())
      flush_pendings();
  }

  void clear()
  {
    if (_emiting)
    {
      _pendings.clear();
      for (auto &[id, _] : _entries)
      {
        _waits.push_back({DeferredOp::Del, id, {}});
      }
    }
    else
    {
      _entries.clear();
    }
  }

  bool empty() const { return _entries.empty(); }
  std::size_t size() const { return _entries.size(); }

private:
  std::size_t add_impl(std::unique_ptr<IListener> listener, bool once)
  {
    std::size_t id = _next_id++;
    Entry entry{std::move(listener), once};
    if (_emiting)
    {
      _waits.push_back({DeferredOp::Add, id, std::move(entry)});
    }
    else
    {
      _entries[id] = std::move(entry);
    }
    return id;
  }
};

// ============================================================
// SignalGroup — 组合式信号容器（无需继承）
//
// 用法:
//   struct PlayerEvents {
//       Signal<int, int> on_attack;
//       Signal<>         on_death;
//   };
//   SignalGroup<PlayerEvents> group;
//   group.signals.on_attack.emit(1, 30);
//
// SignalOwner — 继承式（旧用法兼容）
//   struct Player : SignalOwner<PlayerEvents> { ... };
// ============================================================
template <typename Signals>
struct SignalGroup
{
  Signals signals;
};

template <typename Signals>
struct SignalOwner : SignalGroup<Signals>
{
protected:
  using SignalGroup<Signals>::signals; // 保持 protected 访问
};

#endif // LFW_CORE_SIGNAL_HPP
