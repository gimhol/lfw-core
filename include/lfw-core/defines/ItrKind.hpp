#ifndef LFW_CORE_DEFINES_ITRKIND_HPP
#define LFW_CORE_DEFINES_ITRKIND_HPP

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#include <cstdint>

enum class ItrKind : int32_t
{
  Normal = 0,
  Catch = 1,
  Pick = 2,
  ForceCatch = 3,
  CharacterThrew = 4,
  WeaponSwing = 5,
  SuperPunchMe = 6,
  PickSecretly = 7,
  Heal = 8,
  JohnShield = 9,
  MagicFlute = 10,
  MagicFlute2 = 11,
  Block = 14,
};


LFW_NS_END

#endif // LFW_CORE_DEFINES_ITRKIND_HPP
