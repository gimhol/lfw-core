#ifndef LFW_CORE_DEFINES_FRAMEBEHAVIOR_HPP
#define LFW_CORE_DEFINES_FRAMEBEHAVIOR_HPP

#include <cstdint>

enum class FrameBehavior : int32_t
{
  JohnChase = 1,
  DennisChase = 2,
  Boomerang = 3,
  AngelBlessing = 4,
  AngelBlessingStart = 5,
  DevilJudgementStart = 6,
  ChasingSameEnemy = 7,
  BatStart = 8,
  FirzenDisasterStart = 9,
};

#endif // LFW_CORE_DEFINES_FRAMEBEHAVIOR_HPP
