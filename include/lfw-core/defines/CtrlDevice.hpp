#ifndef LFW_CORE_DEFINES_CTRLDEVICE_HPP
#define LFW_CORE_DEFINES_CTRLDEVICE_HPP

#include <cstdint>

enum class CtrlDevice : uint8_t
{
  Keyboard = 0,
  Gamepad1 = 1,
  Gamepad2 = 2,
  Gamepad3 = 3,
  Gamepad4 = 4,
  TouchScreen = 5
};

#endif // LFW_CORE_DEFINES_CTRLDEVICE_HPP
