#ifndef LFW_CORE_DEFINES_DIFFICULTY_HPP
#define LFW_CORE_DEFINES_DIFFICULTY_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                            \
  X(Difficulty, Easy, "easy", "", = 1)           \
  X(Difficulty, Normal, "normal", "", = 2)       \
  X(Difficulty, Difficult, "difficult", "", = 3) \
  X(Difficulty, Crazy, "crazy", "", = 4)

enum class Difficulty : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto Difficulty_MIN = Difficulty::Easy;
constexpr auto Difficulty_MAX = Difficulty::Crazy;
GEN_ENUM_STR_MAP(DifficultyStringMap, ENUM_ITEMS, Difficulty)
GEN_ENUM_NAME_MAP(DifficultyNameMap, ENUM_ITEMS, Difficulty)
GEN_ENUM_DESC_MAP(DifficultyDescMap, ENUM_ITEMS, Difficulty)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(difficulty_to_string, difficulty_from_string, Difficulty, DifficultyStringMap)
DEFINE_ENUM_STR_CONVERTERS(difficulty_to_name, difficulty_from_name, Difficulty, DifficultyNameMap)
DEFINE_ENUM_TO_STR(difficulty_to_desc, Difficulty, DifficultyDescMap)
#endif // LFW_CORE_DEFINES_DIFFICULTY_HPP
