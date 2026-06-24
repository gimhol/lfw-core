#ifndef LFW_CORE_DEFINES_BOTSTATE_HPP
#define LFW_CORE_DEFINES_BOTSTATE_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                       \
  X(BotState, Idle, "Idle", "", )           \
  X(BotState, Avoiding, "Avoiding", "", )   \
  X(BotState, Chasing, "Chasing", "", )     \
  X(BotState, Following, "Following", "", ) \
  X(BotState, StageEnd, "StageEnd", "", )   \
  X(BotState, Dead, "Dead", "", )

#define ENUM_ITEM(ENUM, NAME, STR, DESC, VAL) NAME VAL,
enum class BotState : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(BotStateStringMap, ENUM_ITEMS, BotState)
GEN_ENUM_NAME_MAP(BotStateNameMap, ENUM_ITEMS, BotState)
GEN_ENUM_DESC_MAP(BotStateDescMap, ENUM_ITEMS, BotState)
#undef ENUM_ITEM
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(bot_state_to_string, bot_state_from_string, BotState, BotStateStringMap)
DEFINE_ENUM_STR_CONVERTERS(bot_state_to_name, bot_state_from_name, BotState, BotStateNameMap)
DEFINE_ENUM_TO_STR(bot_state_to_desc, BotState, BotStateDescMap)
#endif // LFW_CORE_DEFINES_BOTSTATE_HPP
