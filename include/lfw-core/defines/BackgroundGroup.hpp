#ifndef LFW_CORE_DEFINES_BACKGROUNDGROUP_HPP
#define LFW_CORE_DEFINES_BACKGROUNDGROUP_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/* 格式: X(枚举类型, 枚举名, "字符串值", "描述", 值) */
#define ENUM_ITEMS(X)                          \
  X(BackgroundGroup, Regular, "regular", "", ) \
  X(BackgroundGroup, Hidden, "hidden", "", )

enum class BackgroundGroup : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(BackgroundGroupStringMap, ENUM_ITEMS, BackgroundGroup)
GEN_ENUM_NAME_MAP(BackgroundGroupNameMap, ENUM_ITEMS, BackgroundGroup)
GEN_ENUM_DESC_MAP(BackgroundGroupDescMap, ENUM_ITEMS, BackgroundGroup)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(background_group_to_string, background_group_from_string, BackgroundGroup, BackgroundGroupStringMap)
DEFINE_ENUM_STR_CONVERTERS(background_group_to_name, background_group_from_name, BackgroundGroup, BackgroundGroupNameMap)
DEFINE_ENUM_TO_STR(background_group_to_desc, BackgroundGroup, BackgroundGroupDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_BACKGROUNDGROUP_HPP
