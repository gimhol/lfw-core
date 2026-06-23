#ifndef LFW_CORE_GRAVES_HPP
#define LFW_CORE_GRAVES_HPP

#include <cstddef>
#include <optional>
#include <vector>

// ============================================================
// Graves — 对象池，用于复用已分配的对象，避免反复构造/析构
//
// 对应 TypeScript 中的 Graves<T>，用来避免 GC 触发。
// 内部用 LIFO（栈）管理空闲对象。
//
// 用法:
//   Graves<Bullet> pool;
//   pool.add(Bullet(x, y));   // 归还对象
//   auto b = pool.take();     // 取出对象（std::optional）
//   if (b) use(*b);
// ============================================================
template <typename T>
class Graves
{
public:
  /// 归还一个对象到池中
  void add(T t)
  {
    if (_i == 0)
    {
      _l.push_back(std::move(t));
    }
    else
    {
      _l[--_i] = std::move(t);
    }
  }

  /// 从池中取出一个对象，池空时返回 std::nullopt
  [[nodiscard]] std::optional<T> take()
  {
    if (_i >= _l.size())
      return std::nullopt;
    auto ret = std::move(_l[_i]);
    _l[_i].reset();
    ++_i;
    return ret;
  }

  /// 清空池
  void clear()
  {
    _l.clear();
    _i = 0;
  }

  /// 池中可用对象数量
  [[nodiscard]] std::size_t available() const { return _l.size() - _i; }

  /// 池是否为空
  [[nodiscard]] bool empty() const { return _i >= _l.size(); }

  /// 池的容量（包括已取出的槽位）
  [[nodiscard]] std::size_t capacity() const { return _l.size(); }

private:
  std::vector<std::optional<T>> _l;
  std::size_t _i = 0;
};

#endif // LFW_CORE_GRAVES_HPP
