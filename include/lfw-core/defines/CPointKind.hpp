#ifndef LFW_CORE_DEFINES_CPOINTKIND_HPP
#define LFW_CORE_DEFINES_CPOINTKIND_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#define ENUM_ITEMS(X)                          \
  X(CPointKind, Attacker, "attacker", "", = 1) \
  X(CPointKind, Victim, "victim", "", = 2)

enum class CPointKind : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(CPointKindStringMap, ENUM_ITEMS, CPointKind)
GEN_ENUM_NAME_MAP(CPointKindNameMap, ENUM_ITEMS, CPointKind)
GEN_ENUM_DESC_MAP(CPointKindDescMap, ENUM_ITEMS, CPointKind)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(cpoint_kind_to_string, cpoint_kind_from_string, CPointKind, CPointKindStringMap)
DEFINE_ENUM_STR_CONVERTERS(cpoint_kind_to_name, cpoint_kind_from_name, CPointKind, CPointKindNameMap)
DEFINE_ENUM_TO_STR(cpoint_kind_to_desc, CPointKind, CPointKindDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_CPOINTKIND_HPP
