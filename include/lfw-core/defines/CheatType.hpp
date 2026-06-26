#ifndef LFW_CORE_DEFINES_CHEATTYPE_HPP
#define LFW_CORE_DEFINES_CHEATTYPE_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#define ENUM_ITEMS(X)                    \
  X(CheatType, LF2_NET, "LF2_NET", "", ) \
  X(CheatType, HERO_FT, "HERO_FT", "", ) \
  X(CheatType, GIM_INK, "GIM_INK", "", )

enum class CheatType : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(CheatTypeStringMap, ENUM_ITEMS, CheatType)
GEN_ENUM_NAME_MAP(CheatTypeNameMap, ENUM_ITEMS, CheatType)
GEN_ENUM_DESC_MAP(CheatTypeDescMap, ENUM_ITEMS, CheatType)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(cheat_type_to_string, cheat_type_from_string, CheatType, CheatTypeStringMap)
DEFINE_ENUM_STR_CONVERTERS(cheat_type_to_name, cheat_type_from_name, CheatType, CheatTypeNameMap)
DEFINE_ENUM_TO_STR(cheat_type_to_desc, CheatType, CheatTypeDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_CHEATTYPE_HPP
