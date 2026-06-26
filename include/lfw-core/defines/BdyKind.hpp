#ifndef LFW_CORE_DEFINES_BDYKIND_HPP
#define LFW_CORE_DEFINES_BDYKIND_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#define ENUM_ITEMS(X)                       \
  X(BdyKind, Normal, "normal", "", = 0)     \
  X(BdyKind, Criminal, "criminal", "", = 1) \
  X(BdyKind, Defend, "defend", "", = 2000)  \
  X(BdyKind, Ignore, "ignore", "", = 10000)

enum class BdyKind : int32_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(BdyKindStringMap, ENUM_ITEMS, BdyKind)
GEN_ENUM_NAME_MAP(BdyKindNameMap, ENUM_ITEMS, BdyKind)
GEN_ENUM_DESC_MAP(BdyKindDescMap, ENUM_ITEMS, BdyKind)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(bdy_kind_to_string, bdy_kind_from_string, BdyKind, BdyKindStringMap)
DEFINE_ENUM_STR_CONVERTERS(bdy_kind_to_name, bdy_kind_from_name, BdyKind, BdyKindNameMap)
DEFINE_ENUM_TO_STR(bdy_kind_to_desc, BdyKind, BdyKindDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_BDYKIND_HPP
