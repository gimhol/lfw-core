#ifndef LFW_CORE_DEFINES_DATTYPEENUM_HPP
#define LFW_CORE_DEFINES_DATTYPEENUM_HPP

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

/* 格式: X(枚举类型, 枚举名, "字符串值", "描述", 值) */
#define ENUM_ITEMS(X)                       \
  X(DatTypeEnum, Invalid, "", "", = 0)      \
  X(DatTypeEnum, Fighter, "0", "", = 1)     \
  X(DatTypeEnum, WeaponA, "1", "", = 2)     \
  X(DatTypeEnum, WeaponB, "2", "", = 3)     \
  X(DatTypeEnum, Ball, "3", "", = 4)        \
  X(DatTypeEnum, WeaponC, "4", "", = 5)     \
  X(DatTypeEnum, Criminal, "5", "", = 6)    \
  X(DatTypeEnum, WeaponD, "6", "", = 7)     \
  X(DatTypeEnum, Background, "bg", "", = 8) \
  X(DatTypeEnum, Stage, "stage", "", = 9)   \
  X(DatTypeEnum, Bot, "bot", "", = 10)

enum class DatTypeEnum : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(DatTypeStringMap, ENUM_ITEMS, DatTypeEnum)
GEN_ENUM_NAME_MAP(DatTypeNameMap, ENUM_ITEMS, DatTypeEnum)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(dat_type_to_string, dat_type_from_string, DatTypeEnum, DatTypeStringMap)
DEFINE_ENUM_STR_CONVERTERS(dat_type_to_name, dat_type_from_name, DatTypeEnum, DatTypeNameMap)

/// suffix_map — 根据 DatTypeEnum 返回文件后缀
inline std::string_view dat_type_suffix(DatTypeEnum v)
{
  switch (v)
  {
  case DatTypeEnum::Background:
    return "bg";
  case DatTypeEnum::Stage:
    return "stage";
  case DatTypeEnum::Bot:
    return "bot";
  default:
    return "obj";
  }
}

#endif // LFW_CORE_DEFINES_DATTYPEENUM_HPP
