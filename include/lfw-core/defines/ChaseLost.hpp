#ifndef LFW_CORE_DEFINES_CHASELOST_HPP
#define LFW_CORE_DEFINES_CHASELOST_HPP

#include <cstdint>

enum class ChaseLost : uint8_t
{
  Hover = 1,
  Leave = 2,
  End = 4
};

enum class ChaseStrategy : uint8_t
{
  Default = 0,
  TillLost = 1
};

#endif // LFW_CORE_DEFINES_CHASELOST_HPP
