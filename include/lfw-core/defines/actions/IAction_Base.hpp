#ifndef LFW_CORE_DEFINES_ACTIONS_IACTION_BASE_H
#define LFW_CORE_DEFINES_ACTIONS_IACTION_BASE_H

#include <optional>
#include <string>

#include "lfw-core/base/Expression.h"

/// IAction_Base — 条件动作基类
struct IAction_Base
{
  /// 条件表达式字符串
  std::optional<std::string> test;

  /// 预测试（通常表示上一帧已通过，跳过重复评估）
  std::optional<bool> pretest;

  /// 条件测试器（由 test 生成）
  /// 当 test 和 tester 都不存在时，视为测试通过
  IExpression *tester = nullptr;
};

#endif
