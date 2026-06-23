#ifndef LFW_CORE_DEFINES_SPEEDMODE_HPP
#define LFW_CORE_DEFINES_SPEEDMODE_HPP

#include <cstdint>

enum class SpeedMode : uint8_t
{
  Default = 0,
  Acc = 1,
  FixedLF2 = 2,
  FixedAcc = 3,
  AccTo = 4,
  Extra = 5,
  Fixed = 6,
  FixedAccTo = 7
};

#endif // LFW_CORE_DEFINES_SPEEDMODE_HPP
