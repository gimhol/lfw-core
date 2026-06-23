#ifndef LFW_CORE_DEFINES_BDYKIND_HPP
#define LFW_CORE_DEFINES_BDYKIND_HPP

#include <cstdint>

enum class BdyKind : int32_t
{
  Normal = 0,
  Criminal = 1,
  Defend = 2000,
  Ignore = 10000
};

#endif // LFW_CORE_DEFINES_BDYKIND_HPP
