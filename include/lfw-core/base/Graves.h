#ifndef LFW_CORE_GRAVES_H
#define LFW_CORE_GRAVES_H

#include <cstddef>
#include <vector>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// ============================================================
// Graves — 对象池，持有指针以复用已分配对象
//
// 对应 TS Graves<T>（存 T|undefined 引用），C++ 用 void*
// 消除模板。调用方负责对象的实际生命周期。
// 内部用 LIFO（栈）管理空闲指针。
//
// 用法:
//   Graves pool;
//   Bullet b1, b2;
//   pool.add(&b1);
//   auto *p = static_cast<Bullet*>(pool.take());
// ============================================================
class Graves
{
public:
  void add(void *obj)
  {
    if (_i == 0)
      _l.push_back(obj);
    else
      _l[--_i] = obj;
  }

  [[nodiscard]] void *take()
  {
    if (_i >= _l.size())
      return nullptr;
    void *ret = _l[_i];
    _l[_i] = nullptr;
    ++_i;
    return ret;
  }

  void clear()
  {
    _l.clear();
    _i = 0;
  }

  [[nodiscard]] std::size_t available() const { return _l.size() - _i; }
  [[nodiscard]] bool empty() const { return _i >= _l.size(); }
  [[nodiscard]] std::size_t capacity() const { return _l.size(); }

private:
  std::vector<void *> _l;
  std::size_t _i = 0;
};

LFW_NS_END

#endif
