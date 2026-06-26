#ifndef LFW_CORE_DEFINES_WPOINTKIND_HPP
#define LFW_CORE_DEFINES_WPOINTKIND_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#define ENUM_ITEMS(X)                            \
  X(WpointKind, None, "none", "无", = 0)         \
  X(WpointKind, Bearer, "bearer", "持握者", = 1) \
  X(WpointKind, Holded, "holded", "被持握", = 2) \
  X(WpointKind, Drop, "drop", "掉落", = 3)

enum class WpointKind : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto WpointKind_MIN = WpointKind::None;
constexpr auto WpointKind_MAX = WpointKind::Drop;
GEN_ENUM_STR_MAP(WpointKindStringMap, ENUM_ITEMS, WpointKind)
GEN_ENUM_NAME_MAP(WpointKindNameMap, ENUM_ITEMS, WpointKind)
GEN_ENUM_DESC_MAP(WpointKindDescMap, ENUM_ITEMS, WpointKind)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(wpoint_kind_to_string, wpoint_kind_from_string, WpointKind, WpointKindStringMap)
DEFINE_ENUM_STR_CONVERTERS(wpoint_kind_to_name, wpoint_kind_from_name, WpointKind, WpointKindNameMap)
DEFINE_ENUM_TO_STR(wpoint_kind_to_desc, WpointKind, WpointKindDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_WPOINTKIND_HPP
