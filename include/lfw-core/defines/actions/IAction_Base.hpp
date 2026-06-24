#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_BASE_HPP
#define LFW_CORE_DEFINES_ACTIONS_IACTION_BASE_HPP

#include <optional>
#include <string>

/// IAction_Base — 条件动作基类
struct IAction_Base
{
  /// 条件表达式字符串
  std::optional<std::string> test;

  /// 预测试（通常表示上一帧已通过，跳过重复评估）
  std::optional<bool> pretest;

  /// 条件测试器（由 test 生成）
  /// 当 test 和 tester 都不存在时，视为测试通过
  std::optional<void *> tester; // TODO: IExpression<T> 待实现后替换
};

#endif
