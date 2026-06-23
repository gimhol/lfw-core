#ifndef LFW_CORE_CONDITIONCHAIN_HPP
#define LFW_CORE_CONDITIONCHAIN_HPP

#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

#include "lfw-core/base/Expression.hpp"

// ============================================================
// ConditionChain — 条件链
//
// 对应 TypeScript 的 Expressions<T>：
//   一组 IJudger<T> 按顺序链式求值
//   - run()  执行当前条件
//   - next() 前进到下一个
//   - flow() 从当前位置连续执行，直到失败或末尾
//
// 用法:
//   ConditionChain<BattleContext> chain;
//   chain.reset({ &cond1, &cond2 });
//   bool ok = chain.flow(ctx);
// ============================================================
template <typename T>
class ConditionChain
{
public:
  using ExprPtr = IJudger<T> *;

  /// 当前表达式列表（只读视图）
  const std::vector<ExprPtr> &list() const { return _list; }

  /// 是否在开头（_index <= 0）
  bool is_first() const { return _index <= 0; }

  /// 是否在末尾（_index >= length - 1）
  bool is_last() const { return _index >= _list.size() - 1; }

  /// 当前索引
  std::size_t index() const { return _index; }

  // ----------------------------------------------------------
  /// 重置表达式列表 — 对应 reset()
  void reset(const std::vector<ExprPtr> &list)
  {
    _index = 0;
    if (&_list == &list)
      return; // 自赋值保护
    _list = list;
  }

  /// 从初始化列表重置
  void reset(std::initializer_list<ExprPtr> il)
  {
    _index = 0;
    _list.assign(il);
  }

  // ----------------------------------------------------------
  /// 执行当前表达式 — 对应 run()
  bool run(const T &arg)
  {
    if (_index >= _list.size())
      return false;
    return _list[_index]->run(arg);
  }

  // ----------------------------------------------------------
  /// 前进到下一个表达式 — 对应 next()
  void next()
  {
    if (!_list.empty())
      _index = std::min(_index + 1, _list.size() - 1);
  }

  // ----------------------------------------------------------
  /// 从当前位置连续执行表达式，直到失败或到达末尾
  /// 返回 true 表示所有执行的表达式都通过了
  /// 对应 TS 的 flow()
  bool flow(const T &arg)
  {
    bool pass = false;
    do
    {
      bool is_last = this->is_last();
      pass = run(arg);
      if (!pass || is_last)
        break;
      next();
    } while (true);
    return pass;
  }

  /// 重置索引到开头
  void reset_index() { _index = 0; }

private:
  std::vector<ExprPtr> _list;
  std::size_t _index = 0;
};

#endif // LFW_CORE_CONDITIONCHAIN_HPP
