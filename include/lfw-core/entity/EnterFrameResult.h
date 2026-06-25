#ifndef LFW_CORE_ENTITY_ENTER_FRAME_RESULT_H
#define LFW_CORE_ENTITY_ENTER_FRAME_RESULT_H

#include <cstdint>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// enter_frame() 返回值 — 对应 TS EnterFrameResult
enum class EnterFrameResult : uint8_t
{
  Gone = 0,     // 实体已消失
  NotFound = 1, // 未找到目标帧
  Entered = 2,  // 成功进入目标帧
  Fallback = 3  // 回退到自动帧
};

LFW_NS_END

#endif
