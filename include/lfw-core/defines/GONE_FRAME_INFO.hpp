#ifndef LFW_CORE_DEFINES_GONE_FRAME_INFO_HPP
#define LFW_CORE_DEFINES_GONE_FRAME_INFO_HPP

#include "Builtin_FrameId.hpp"
#include "IFrameInfo.hpp"

/// GONE_FRAME_INFO — 消失帧常量
/// 对应 TS 的 GONE_FRAME_INFO，用于标记实体已消失
/// 注意：C++ IFrameInfo 为简化版本，部分 TS 字段（name, pic, width, height, centerx/y, no_shadow 等）暂缺
inline const IFrameInfo GONE_FRAME_INFO = []
{
  IFrameInfo f;
  f.id = builtin_frame_id_to_string(Builtin_FrameId::Gone);
  f.state.reset();
  f.wait = 0;
  f.next = "gone";
  f.facing.reset();
  return f;
}();

#endif
