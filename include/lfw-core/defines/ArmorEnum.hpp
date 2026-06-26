#ifndef LFW_CORE_DEFINES_ARMORENUM_HPP
#define LFW_CORE_DEFINES_ARMORENUM_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/* 格式: X(枚举类型, 枚举名, "字符串值", "描述", 值) */
#define ENUM_ITEMS(X)                     \
  X(ArmorEnum, Defend, "defend", "", = 1) \
  X(ArmorEnum, Fall, "fall", "", = 2)     \
  X(ArmorEnum, Times, "times", "", = 3)   \
  X(ArmorEnum, Injury, "injury", "", = 4)

enum class ArmorEnum : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(ArmorTypeStringMap, ENUM_ITEMS, ArmorEnum)
GEN_ENUM_NAME_MAP(ArmorTypeNameMap, ENUM_ITEMS, ArmorEnum)
GEN_ENUM_DESC_MAP(ArmorTypeDescMap, ENUM_ITEMS, ArmorEnum)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(armor_type_to_string, armor_type_from_string, ArmorEnum, ArmorTypeStringMap)
DEFINE_ENUM_STR_CONVERTERS(armor_type_to_name, armor_type_from_name, ArmorEnum, ArmorTypeNameMap)
DEFINE_ENUM_TO_STR(armor_type_to_desc, ArmorEnum, ArmorTypeDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_ARMORENUM_HPP
