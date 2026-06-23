#ifndef LFW_CORE_DEFINES_WPOINTKIND_HPP
#define LFW_CORE_DEFINES_WPOINTKIND_HPP

#include <cstdint>

enum class WpointKind : uint8_t
{
  None = 0,
  Bearer = 1,
  Holded = 2,
  Drop = 3
};

#endif // LFW_CORE_DEFINES_WPOINTKIND_HPP
