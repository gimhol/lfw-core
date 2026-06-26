#ifndef LFW_CORE_DEFINES_CTRLDEVICE_HPP
#define LFW_CORE_DEFINES_CTRLDEVICE_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#define ENUM_ITEMS(X)                          \
  X(CtrlDevice, Keyboard, "keyboard", "", = 0) \
  X(CtrlDevice, Gamepad1, "gamepad1", "", = 1) \
  X(CtrlDevice, Gamepad2, "gamepad2", "", = 2) \
  X(CtrlDevice, Gamepad3, "gamepad3", "", = 3) \
  X(CtrlDevice, Gamepad4, "gamepad4", "", = 4) \
  X(CtrlDevice, TouchScreen, "touchscreen", "", = 5)

enum class CtrlDevice : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(CtrlDeviceStringMap, ENUM_ITEMS, CtrlDevice)
GEN_ENUM_NAME_MAP(CtrlDeviceNameMap, ENUM_ITEMS, CtrlDevice)
GEN_ENUM_DESC_MAP(CtrlDeviceDescMap, ENUM_ITEMS, CtrlDevice)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(ctrl_device_to_string, ctrl_device_from_string, CtrlDevice, CtrlDeviceStringMap)
DEFINE_ENUM_STR_CONVERTERS(ctrl_device_to_name, ctrl_device_from_name, CtrlDevice, CtrlDeviceNameMap)
DEFINE_ENUM_TO_STR(ctrl_device_to_desc, CtrlDevice, CtrlDeviceDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_CTRLDEVICE_HPP
