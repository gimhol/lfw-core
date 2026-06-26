#ifndef LFW_CORE_DEFINES_INEXT_FRAME_RESULT_HPP
#define LFW_CORE_DEFINES_INEXT_FRAME_RESULT_HPP

#include <optional>

#include "IFrameInfo.hpp"
#include "INextFrame.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// INextFrameResult — 下一帧判定结果
struct INextFrameResult
{
  std::optional<IFrameInfo> frame;
  INextFrame which;
};

LFW_NS_END

#endif
