#ifndef LFW_CORE_DEFINES_STAGEACTION_HPP
#define LFW_CORE_DEFINES_STAGEACTION_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                                                     \
  X(StageAction, GoGoGoRight, "gogogo_right", "向右", = 0)                \
  X(StageAction, EnterNextPhase, "enter_next_phase", "进入下一阶段", = 1) \
  X(StageAction, LoopGoGoGoRight, "loop_gogogo_right", "向右", = 2)

enum class StageAction : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto StageAction_MIN = StageAction::GoGoGoRight;
constexpr auto StageAction_MAX = StageAction::LoopGoGoGoRight;
GEN_ENUM_STR_MAP(StageActionStringMap, ENUM_ITEMS, StageAction)
GEN_ENUM_NAME_MAP(StageActionNameMap, ENUM_ITEMS, StageAction)
GEN_ENUM_DESC_MAP(StageActionDescMap, ENUM_ITEMS, StageAction)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(stage_action_to_string, stage_action_from_string, StageAction, StageActionStringMap)
DEFINE_ENUM_STR_CONVERTERS(stage_action_to_name, stage_action_from_name, StageAction, StageActionNameMap)
DEFINE_ENUM_TO_STR(stage_action_to_desc, StageAction, StageActionDescMap)
#endif // LFW_CORE_DEFINES_STAGEACTION_HPP
