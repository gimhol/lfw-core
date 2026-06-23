#ifndef LFW_CORE_DEFINES_SPEEDCTRL_HPP
#define LFW_CORE_DEFINES_SPEEDCTRL_HPP

#include <cstdint>

enum class SpeedCtrl : uint8_t
{
  None = 0,
  Control = 1,
  Enable = 2,
  Disable = 3
};

#endif // LFW_CORE_DEFINES_SPEEDCTRL_HPP
