#ifndef LFW_CORE_DEFINES_FACINGFLAG_HPP
#define LFW_CORE_DEFINES_FACINGFLAG_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// FacingFlag.ts
#define ENUM_ITEMS(X)                                         \
  X(FacingFlag, None, "none", "", = 0)                        \
  X(FacingFlag, L, "l", "", = -1)                             \
  X(FacingFlag, R, "r", "", = 1)                              \
  X(FacingFlag, B, "b", "", = 2)                              \
  X(FacingFlag, Ctrl, "ctrl", "", = 3)                        \
  X(FacingFlag, SameAsCatcher, "same_as_catcher", "", = 4)    \
  X(FacingFlag, OpposingCatcher, "opposing_catcher", "", = 5) \
  X(FacingFlag, AntiCtrl, "anti_ctrl", "", = 6)               \
  X(FacingFlag, VX, "vx", "", = 7)                            \
  X(FacingFlag, AntiVX, "anti_vx", "", = 8)                   \
  X(FacingFlag, Trend, "trend", "", = 9)

enum class FacingFlag : int8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto FacingFlag_Left = FacingFlag::L;
constexpr auto FacingFlag_Right = FacingFlag::R;
constexpr auto FacingFlag_Backward = FacingFlag::B;
constexpr auto FacingFlag_SameAsBearer = FacingFlag::SameAsCatcher;
constexpr auto FacingFlag_OpposingBearer = FacingFlag::OpposingCatcher;
GEN_ENUM_STR_MAP(FacingFlagStringMap, ENUM_ITEMS, FacingFlag)
GEN_ENUM_NAME_MAP(FacingFlagNameMap, ENUM_ITEMS, FacingFlag)
GEN_ENUM_DESC_MAP(FacingFlagDescMap, ENUM_ITEMS, FacingFlag)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(facing_flag_to_string, facing_flag_from_string, FacingFlag, FacingFlagStringMap)
DEFINE_ENUM_STR_CONVERTERS(facing_flag_to_name, facing_flag_from_name, FacingFlag, FacingFlagNameMap)
DEFINE_ENUM_TO_STR(facing_flag_to_desc, FacingFlag, FacingFlagDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_FACINGFLAG_HPP
