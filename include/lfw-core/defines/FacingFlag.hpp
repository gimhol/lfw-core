#ifndef LFW_CORE_DEFINES_FACINGFLAG_HPP
#define LFW_CORE_DEFINES_FACINGFLAG_HPP

#include <cstdint>

/// FacingFlag.ts
enum class FacingFlag : int8_t
{
  None = 0,
  L = -1,
  Left = -1,
  R = 1,
  Right = 1,
  B = 2,
  Backward = 2,
  Ctrl = 3,
  SameAsCatcher = 4,
  SameAsBearer = 4,
  OpposingCatcher = 5,
  OpposingBearer = 5,
  AntiCtrl = 6,
  VX = 7,
  AntiVX = 8,
  Trend = 9,
};

#endif // LFW_CORE_DEFINES_FACINGFLAG_HPP
