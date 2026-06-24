#ifndef LFW_CORE_DEFINES_IFRAME_INFO_HPP
#define LFW_CORE_DEFINES_IFRAME_INFO_HPP

#include <optional>
#include <string>
#include <vector>

#include "IVelocityInfo.hpp"

/// IFrameInfo — 帧信息
struct IFrameInfo : IVelocityInfo
{
  std::optional<std::string> id;
  std::optional<double> wait;
  std::optional<std::string> pic;
  std::optional<std::string> next;
  std::optional<std::string> state;
  std::optional<int> facing;
};

#endif
