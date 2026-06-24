#ifndef LFW_CORE_DEFINES_BOTVAL_HPP
#define LFW_CORE_DEFINES_BOTVAL_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include "EnumHelper.hpp"
#define ENUM_ITEMS(X)                         \
  X(BotVal, Desire, "desire", "", = 0)        \
  X(BotVal, BotStatus, "bot_status", "", )    \
  X(BotVal, EnemyY, "enemy_y", "", )          \
  X(BotVal, EnemyDiffY, "enemy_diff_y", "", ) \
  X(BotVal, EnemyX, "enemy_x", "", )          \
  X(BotVal, EnemyDiffX, "enemy_diff_x", "", ) \
  X(BotVal, EnemyState, "enemy_state", "", )  \
  X(BotVal, Safe, "safe", "", )               \
  X(BotVal, EnemyOutOfRange, "en_oor", "", )

#define ENUM_ITEM(ENUM, NAME, STR, DESC, VAL) NAME VAL,
enum class BotVal : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(BotValStringMap, ENUM_ITEMS, BotVal)
GEN_ENUM_NAME_MAP(BotValNameMap, ENUM_ITEMS, BotVal)
GEN_ENUM_DESC_MAP(BotValDescMap, ENUM_ITEMS, BotVal)
#undef ENUM_ITEM
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(bot_val_to_string, bot_val_from_string, BotVal, BotValStringMap)
DEFINE_ENUM_STR_CONVERTERS(bot_val_to_name, bot_val_from_name, BotVal, BotValNameMap)
DEFINE_ENUM_TO_STR(bot_val_to_desc, BotVal, BotValDescMap)
#endif // LFW_CORE_DEFINES_BOTVAL_HPP
