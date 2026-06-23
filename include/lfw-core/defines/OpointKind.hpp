#ifndef LFW_CORE_DEFINES_OPOINTKIND_HPP
#define LFW_CORE_DEFINES_OPOINTKIND_HPP

#include <cstdint>

enum class OpointKind : uint8_t
{
  Normal = 1,
  Pick = 2
};

enum class OpointSpreading : uint8_t
{
  Normal = 0,
  Spreading = 1,
  FloatRange = 2,
  AngelBlessing = 4
};

enum class OpointMulti : uint8_t
{
  AccordingEnemies = 0,
  AccordingAllies = 1
};

#endif // LFW_CORE_DEFINES_OPOINTKIND_HPP
