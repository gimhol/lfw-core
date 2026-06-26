#ifndef LFW_CORE_DEFINES_FRAMEBEHAVIOR_HPP
#define LFW_CORE_DEFINES_FRAMEBEHAVIOR_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#define ENUM_ITEMS(X)                                                     \
  X(FrameBehavior, JohnChase, "john_chase", "", = 1)                      \
  X(FrameBehavior, DennisChase, "dennis_chase", "", = 2)                  \
  X(FrameBehavior, Boomerang, "boomerang", "", = 3)                       \
  X(FrameBehavior, AngelBlessing, "angel_blessing", "", = 4)              \
  X(FrameBehavior, AngelBlessingStart, "angel_blessing_start", "", = 5)   \
  X(FrameBehavior, DevilJudgementStart, "devil_judgement_start", "", = 6) \
  X(FrameBehavior, ChasingSameEnemy, "chasing_same_enemy", "", = 7)       \
  X(FrameBehavior, BatStart, "bat_start", "", = 8)                        \
  X(FrameBehavior, FirzenDisasterStart, "firzen_disaster_start", "", = 9)

enum class FrameBehavior : int32_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(FrameBehaviorStringMap, ENUM_ITEMS, FrameBehavior)
GEN_ENUM_NAME_MAP(FrameBehaviorNameMap, ENUM_ITEMS, FrameBehavior)
GEN_ENUM_DESC_MAP(FrameBehaviorDescMap, ENUM_ITEMS, FrameBehavior)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(frame_behavior_to_string, frame_behavior_from_string, FrameBehavior, FrameBehaviorStringMap)
DEFINE_ENUM_STR_CONVERTERS(frame_behavior_to_name, frame_behavior_from_name, FrameBehavior, FrameBehaviorNameMap)
DEFINE_ENUM_TO_STR(frame_behavior_to_desc, FrameBehavior, FrameBehaviorDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_FRAMEBEHAVIOR_HPP
