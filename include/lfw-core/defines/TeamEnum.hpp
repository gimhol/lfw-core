#ifndef LFW_CORE_DEFINES_TEAMENUM_HPP
#define LFW_CORE_DEFINES_TEAMENUM_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#define ENUM_ITEMS(X)                       \
  X(TeamEnum, Independent, "", "独立", = 0) \
  X(TeamEnum, Team_1, "1", "队伍1", = 1)    \
  X(TeamEnum, Team_2, "2", "队伍2", = 2)    \
  X(TeamEnum, Team_3, "3", "队伍3", = 3)    \
  X(TeamEnum, Team_4, "4", "队伍4", = 4)    \
  X(TeamEnum, Team_5, "5", "队伍5", = 5)    \
  X(TeamEnum, Team_6, "6", "队伍6", = 6)    \
  X(TeamEnum, Team_7, "7", "队伍7", = 7)    \
  X(TeamEnum, Team_8, "8", "队伍8", = 8)

enum class TeamEnum : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto TeamEnum_MIN = TeamEnum::Independent;
constexpr auto TeamEnum_MAX = TeamEnum::Team_8;
GEN_ENUM_STR_MAP(TeamEnumStringMap, ENUM_ITEMS, TeamEnum)
GEN_ENUM_NAME_MAP(TeamEnumNameMap, ENUM_ITEMS, TeamEnum)
GEN_ENUM_DESC_MAP(TeamEnumDescMap, ENUM_ITEMS, TeamEnum)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(team_enum_to_string, team_enum_from_string, TeamEnum, TeamEnumStringMap)
DEFINE_ENUM_STR_CONVERTERS(team_enum_to_name, team_enum_from_name, TeamEnum, TeamEnumNameMap)
DEFINE_ENUM_TO_STR(team_enum_to_desc, TeamEnum, TeamEnumDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_TEAMENUM_HPP
