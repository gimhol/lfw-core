#ifndef LFW_CORE_DEFINES_SPEEDCTRL_HPP
#define LFW_CORE_DEFINES_SPEEDCTRL_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                                \
  X(SpeedCtrl, None, "none", "无", = 0)               \
  X(SpeedCtrl, Control, "control", "控制", = 1)        \
  X(SpeedCtrl, Enable, "enable", "启用", = 2)          \
  X(SpeedCtrl, Disable, "disable", "禁用", = 3)

enum class SpeedCtrl : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto SpeedCtrl_MIN = SpeedCtrl::None;
constexpr auto SpeedCtrl_MAX = SpeedCtrl::Disable;
GEN_ENUM_STR_MAP(SpeedCtrlStringMap, ENUM_ITEMS, SpeedCtrl)
GEN_ENUM_NAME_MAP(SpeedCtrlNameMap, ENUM_ITEMS, SpeedCtrl)
GEN_ENUM_DESC_MAP(SpeedCtrlDescMap, ENUM_ITEMS, SpeedCtrl)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(speed_ctrl_to_string, speed_ctrl_from_string, SpeedCtrl, SpeedCtrlStringMap)
DEFINE_ENUM_STR_CONVERTERS(speed_ctrl_to_name, speed_ctrl_from_name, SpeedCtrl, SpeedCtrlNameMap)
DEFINE_ENUM_TO_STR(speed_ctrl_to_desc, SpeedCtrl, SpeedCtrlDescMap)
#endif // LFW_CORE_DEFINES_SPEEDCTRL_HPP
