#ifndef LFW_CORE_DEFINES_ITREFFECT_HPP
#define LFW_CORE_DEFINES_ITREFFECT_HPP

#include "lfw-core/core.hpp"


#include <cstdint>

LFW_NS_BEGIN

enum class ItrEffect : int32_t
{
  Normal = 0,
  Sharp = 1,
  Fire = 2,
  Ice = 3,
  Through = 4,
  None = 5,
  MFire1 = 20,
  MFire2 = 21,
  FireExplosion = 22,
  Explosion = 23,
  Ice2 = 30,
  Ignore = 10000,
};


LFW_NS_END

#endif // LFW_CORE_DEFINES_ITREFFECT_HPP
