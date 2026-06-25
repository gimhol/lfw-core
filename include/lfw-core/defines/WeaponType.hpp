#ifndef LFW_CORE_DEFINES_WEAPONTYPE_HPP
#define LFW_CORE_DEFINES_WEAPONTYPE_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                                  \
  X(WeaponType, None, "none", "无", = 0)               \
  X(WeaponType, Stick, "stick", "棍", = 1)             \
  X(WeaponType, Heavy, "heavy", "重武器", = 2)          \
  X(WeaponType, Knife, "knife", "刀", = 3)             \
  X(WeaponType, Baseball, "baseball", "棒球棍", = 4)    \
  X(WeaponType, Drink, "drink", "饮料", = 5)

enum class WeaponType : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto WeaponType_MIN = WeaponType::None;
constexpr auto WeaponType_MAX = WeaponType::Drink;
GEN_ENUM_STR_MAP(WeaponTypeStringMap, ENUM_ITEMS, WeaponType)
GEN_ENUM_NAME_MAP(WeaponTypeNameMap, ENUM_ITEMS, WeaponType)
GEN_ENUM_DESC_MAP(WeaponTypeDescMap, ENUM_ITEMS, WeaponType)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(weapon_type_to_string, weapon_type_from_string, WeaponType, WeaponTypeStringMap)
DEFINE_ENUM_STR_CONVERTERS(weapon_type_to_name, weapon_type_from_name, WeaponType, WeaponTypeNameMap)
DEFINE_ENUM_TO_STR(weapon_type_to_desc, WeaponType, WeaponTypeDescMap)
#endif // LFW_CORE_DEFINES_WEAPONTYPE_HPP
