#ifndef LFW_CORE_DEFINES_EMPTY_FRAME_INFO_HPP
#define LFW_CORE_DEFINES_EMPTY_FRAME_INFO_HPP

#include "Builtin_FrameId.hpp"
#include "IFrameInfo.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// EMPTY_FRAME_INFO — 空帧常量
/// 对应 TS 的 EMPTY_FRAME_INFO，用于占位/默认帧
/// 注意：C++ IFrameInfo 为简化版本，部分 TS 字段（name, pic, width, height, centerx/y, no_shadow 等）暂缺
inline const IFrameInfo EMPTY_FRAME_INFO = []
{
  IFrameInfo f;
  f.id = builtin_frame_id_to_string(Builtin_FrameId::None);
  f.state.reset();
  f.wait = 0;
  f.next = "auto";
  f.facing.reset();
  return f;
}();

LFW_NS_END

#endif
