#ifndef LFW_CORE_DEFINES_DIFFICULTY_HPP
#define LFW_CORE_DEFINES_DIFFICULTY_HPP

#include <cstdint>

enum class Difficulty : uint8_t
{
  Easy = 1,
  Normal = 2,
  Difficult = 3,
  Crazy = 4,
  MIN = 1,
  MAX = 4
};

#endif // LFW_CORE_DEFINES_DIFFICULTY_HPP
