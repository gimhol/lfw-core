#ifndef LFW_CORE_DEFINES_STAGEVAL_HPP
#define LFW_CORE_DEFINES_STAGEVAL_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#define ENUM_ITEMS(X)                                                \
  X(StageVal, EnemiesCleared, "enemies_cleared", "敌人已清除", = 0)  \
  X(StageVal, DialogCleared, "dialog_cleared", "对话已清除", = 1)    \
  X(StageVal, CurPhaseTime, "cur_phase_time", "当前阶段时间", = 2)   \
  X(StageVal, CurDialogTime, "cur_dialog_time", "当前对话时间", = 3) \
  X(StageVal, PressAttack, "press_attack", "按下攻击", = 4)          \
  X(StageVal, PressJump, "press_jump", "按下跳跃", = 5)              \
  X(StageVal, PressDefend, "press_defend", "按下防御", = 6)          \
  X(StageVal, PressUp, "press_up", "按下上", = 7)                    \
  X(StageVal, PressDown, "press_down", "按下下", = 8)                \
  X(StageVal, PressLeft, "press_left", "按下左", = 9)                \
  X(StageVal, PressRight, "press_right", "按下右", = 10)             \
  X(StageVal, Broadcast, "broadcast", "广播", = 11)

enum class StageVal : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto StageVal_MIN = StageVal::EnemiesCleared;
constexpr auto StageVal_MAX = StageVal::Broadcast;
GEN_ENUM_STR_MAP(StageValStringMap, ENUM_ITEMS, StageVal)
GEN_ENUM_NAME_MAP(StageValNameMap, ENUM_ITEMS, StageVal)
GEN_ENUM_DESC_MAP(StageValDescMap, ENUM_ITEMS, StageVal)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(stage_val_to_string, stage_val_from_string, StageVal, StageValStringMap)
DEFINE_ENUM_STR_CONVERTERS(stage_val_to_name, stage_val_from_name, StageVal, StageValNameMap)
DEFINE_ENUM_TO_STR(stage_val_to_desc, StageVal, StageValDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_STAGEVAL_HPP
