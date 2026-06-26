#ifndef LFW_CORE_CONDITIONCHAIN_H
#define LFW_CORE_CONDITIONCHAIN_H

#include <algorithm>
#include <cstddef>
#include <vector>

#include "lfw-core/base/Expression.h"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// ============================================================
// ConditionChain — 条件链
//
// 对应 TypeScript 的 Expressions<T>：
//   一组 IJudger 按顺序链式求值
//   - run()  执行当前条件
//   - next() 前进到下一个
//   - flow() 从当前位置连续执行，直到失败或末尾
//
// 用法:
//   ConditionChain chain;
//   chain.reset({ &cond1, &cond2 });
//   bool ok = chain.flow(&ctx);  // void* 上下文
// ============================================================
class ConditionChain
{
public:
  using ExprPtr = IJudger *;

  const std::vector<ExprPtr> &list() const { return _list; }
  bool is_first() const { return _index <= 0; }
  bool is_last() const { return _index >= _list.size() - 1; }
  std::size_t index() const { return _index; }

  void reset(const std::vector<ExprPtr> &list)
  {
    _index = 0;
    if (&_list == &list)
      return;
    _list = list;
  }

  void reset(std::initializer_list<ExprPtr> il)
  {
    _index = 0;
    _list.assign(il);
  }

  bool run(void *ctx)
  {
    if (_index >= _list.size())
      return false;
    return _list[_index]->run(ctx);
  }

  void next()
  {
    if (!_list.empty())
      _index = std::min(_index + 1, _list.size() - 1);
  }

  bool flow(void *ctx)
  {
    bool pass = false;
    do
    {
      bool last = is_last();
      pass = run(ctx);
      if (!pass || last)
        break;
      next();
    } while (true);
    return pass;
  }

  void reset_index() { _index = 0; }

private:
  std::vector<ExprPtr> _list;
  std::size_t _index = 0;
};

LFW_NS_END

#endif
