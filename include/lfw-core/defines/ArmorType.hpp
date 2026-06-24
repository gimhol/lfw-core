#ifndef LFW_CORE_DEFINES_ARMORTYPE_HPP
#define LFW_CORE_DEFINES_ARMORTYPE_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

/* 格式: X(枚举类型, 枚举名, "字符串值", "描述", 值) */
#define ENUM_ITEMS(X)                     \
  X(ArmorType, Defend, "defend", "", = 1) \
  X(ArmorType, Fall, "fall", "", = 2)     \
  X(ArmorType, Times, "times", "", = 3)   \
  X(ArmorType, Injury, "injury", "", = 4)

#define ENUM_ITEM(ENUM, NAME, STR, DESC, VAL) NAME VAL,
enum class ArmorType : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(ArmorTypeStringMap, ENUM_ITEMS, ArmorType)
GEN_ENUM_NAME_MAP(ArmorTypeNameMap, ENUM_ITEMS, ArmorType)
GEN_ENUM_DESC_MAP(ArmorTypeDescMap, ENUM_ITEMS, ArmorType)
#undef ENUM_ITEM
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(armor_type_to_string, armor_type_from_string, ArmorType, ArmorTypeStringMap)
DEFINE_ENUM_STR_CONVERTERS(armor_type_to_name, armor_type_from_name, ArmorType, ArmorTypeNameMap)
DEFINE_ENUM_TO_STR(armor_type_to_desc, ArmorType, ArmorTypeDescMap)
#endif // LFW_CORE_DEFINES_ARMORTYPE_HPP
