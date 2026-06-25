#ifndef LFW_CORE_DEFINES_STAGEGROUP_HPP
#define LFW_CORE_DEFINES_STAGEGROUP_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                          \
  X(StageGroup, Hidden, "hidden", "隐藏", = 0) \
  X(StageGroup, Dev, "Dev", "开发", = 1)

enum class StageGroup : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto StageGroup_MIN = StageGroup::Hidden;
constexpr auto StageGroup_MAX = StageGroup::Dev;
GEN_ENUM_STR_MAP(StageGroupStringMap, ENUM_ITEMS, StageGroup)
GEN_ENUM_NAME_MAP(StageGroupNameMap, ENUM_ITEMS, StageGroup)
GEN_ENUM_DESC_MAP(StageGroupDescMap, ENUM_ITEMS, StageGroup)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(stage_group_to_string, stage_group_from_string, StageGroup, StageGroupStringMap)
DEFINE_ENUM_STR_CONVERTERS(stage_group_to_name, stage_group_from_name, StageGroup, StageGroupNameMap)
DEFINE_ENUM_TO_STR(stage_group_to_desc, StageGroup, StageGroupDescMap)
#endif // LFW_CORE_DEFINES_STAGEGROUP_HPP
