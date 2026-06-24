#ifndef LFW_CORE_DEFINES_CMD_HPP
#define LFW_CORE_DEFINES_CMD_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                            \
  X(CMD, F1, "f1", "", )                         \
  X(CMD, F2, "f2", "", )                         \
  X(CMD, F3, "f3", "", )                         \
  X(CMD, F4, "f4", "", )                         \
  X(CMD, F5, "f5", "", )                         \
  X(CMD, F6, "f6", "", )                         \
  X(CMD, F7, "f7", "", )                         \
  X(CMD, F8, "f8", "", )                         \
  X(CMD, F9, "f9", "", )                         \
  X(CMD, F10, "f10", "", )                       \
  X(CMD, LF2_NET, "LF2_NET", "", )               \
  X(CMD, HERO_FT, "HERO_FT", "", )               \
  X(CMD, GIM_INK, "GIM_INK", "", )               \
  X(CMD, KILL_ENEMIES, "KILL_ENEMIES", "", )     \
  X(CMD, KILL_BOSS, "KILL_BOSS", "", )           \
  X(CMD, KILL_SOLIDERS, "KILL_SOLIDERS", "", )   \
  X(CMD, KILL_OTHERS, "KILL_OTHERS", "", )       \
  X(CMD, DEL_PUPPET, "DEL_PUPPET", "", )         \
  X(CMD, SET_DIFFICULTY, "SET_DIFFICULTY", "", ) \
  X(CMD, DIST_CAM, "DIST_CAM", "", )             \
  X(CMD, LOCK_CAM, "LOCK_CAM", "", )             \
  X(CMD, CHANGE_BG, "CHANGE_BG", "", )           \
  X(CMD, CHANGE_STAGE, "CHANGE_STAGE", "", )     \
  X(CMD, PAUSE, "PAUSE", "", )

enum class CMD : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(CMDStringMap, ENUM_ITEMS, CMD)
GEN_ENUM_NAME_MAP(CMDNameMap, ENUM_ITEMS, CMD)
GEN_ENUM_DESC_MAP(CMDDescMap, ENUM_ITEMS, CMD)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(cmd_to_string, cmd_from_string, CMD, CMDStringMap)
DEFINE_ENUM_STR_CONVERTERS(cmd_to_name, cmd_from_name, CMD, CMDNameMap)
DEFINE_ENUM_TO_STR(cmd_to_desc, CMD, CMDDescMap)
#endif // LFW_CORE_DEFINES_CMD_HPP
