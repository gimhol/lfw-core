#ifndef LFW_CORE_DEFINES_IBOT_ACTION_HPP
#define LFW_CORE_DEFINES_IBOT_ACTION_HPP

#include <optional>
#include <string>
#include <vector>

#include "BotState.hpp"
#include "IBotRay.hpp"
#include "lfw-core/base/Fields.hpp"

/// IBotAction — Bot 动作
struct IBotAction
{
  std::string action_id;

  /// 欲望值 [0, 10000]，随机值 < desire 时才可能触发
  std::optional<double> desire;
  std::optional<double> desire_base;
  std::optional<double> desire_step;

  /// 对敌人的 XZ 射线检测，需符合其中之一
  std::optional<std::vector<IBotRay>> e_ray;

  /// 判定式（字符串形式，运行时编译为 judger）
  std::optional<std::string> expression;

  /// 运行时生成的判定器（由 expression 编译而来）
  void *judger = nullptr;

  std::optional<std::vector<BotState>> status;

  /// 触发时按下的键：'F'/'B'/LGK
  std::vector<std::string> keys;
};

inline const auto &bot_action_fields()
{
  static const auto fs = fields<IBotAction>(
      field("action_id", FieldKind::String, &IBotAction::action_id, "动作ID"),
      field("desire", FieldKind::Float, &IBotAction::desire, "欲望值"),
      field("desire_base", FieldKind::Float, &IBotAction::desire_base, "欲望基础值"),
      field("desire_step", FieldKind::Float, &IBotAction::desire_step, "欲望步进值"),
      field("e_ray", FieldKind::ObjectArray, &IBotAction::e_ray, "敌人射线"),
      field("expression", FieldKind::String, &IBotAction::expression, "判定式"),
      field("status", FieldKind::IntArray, &IBotAction::status, "Bot状态"),
      field("keys", FieldKind::StringArray, &IBotAction::keys, "按键"));
  return fs;
}

#endif
