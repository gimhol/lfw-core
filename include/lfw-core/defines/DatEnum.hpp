#ifndef LFW_CORE_DEFINES_DATENUM_HPP
#define LFW_CORE_DEFINES_DATENUM_HPP

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

/* 格式: X(枚举类型, 枚举名, "字符串值", "描述", 值) */
#define ENUM_ITEMS(X)                   \
  X(DatEnum, Invalid, "", "", = 0)      \
  X(DatEnum, Fighter, "0", "", = 1)     \
  X(DatEnum, WeaponA, "1", "", = 2)     \
  X(DatEnum, WeaponB, "2", "", = 3)     \
  X(DatEnum, Ball, "3", "", = 4)        \
  X(DatEnum, WeaponC, "4", "", = 5)     \
  X(DatEnum, Criminal, "5", "", = 6)    \
  X(DatEnum, WeaponD, "6", "", = 7)     \
  X(DatEnum, Background, "bg", "", = 8) \
  X(DatEnum, Stage, "stage", "", = 9)   \
  X(DatEnum, Bot, "bot", "", = 10)

enum class DatEnum : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(DatStringMap, ENUM_ITEMS, DatEnum)
GEN_ENUM_NAME_MAP(DatNameMap, ENUM_ITEMS, DatEnum)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(dat_to_string, dat_from_string, DatEnum, DatStringMap)
DEFINE_ENUM_STR_CONVERTERS(dat_to_name, dat_from_name, DatEnum, DatNameMap)

/// 根据 DatEnum 返回文件后缀
inline std::string_view dat_suffix(DatEnum v)
{
  switch (v)
  {
  case DatEnum::Background:
    return "bg";
  case DatEnum::Stage:
    return "stage";
  case DatEnum::Bot:
    return "bot";
  default:
    return "obj";
  }
}

#endif
