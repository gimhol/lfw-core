#ifndef LFW_CORE_DEFINES_SYNCRENDER_HPP
#define LFW_CORE_DEFINES_SYNCRENDER_HPP

#include <cstdint>

enum class SyncRender : uint8_t
{
  Unlimited = 0,
  Half = 1,
  Sync = 2,
  FPS_60 = 3,
  FPS_120 = 4
};

#endif // LFW_CORE_DEFINES_SYNCRENDER_HPP
