#ifndef LFW_CORE_DEFINES_ISTAGE_INFO_HPP
#define LFW_CORE_DEFINES_ISTAGE_INFO_HPP

#include <optional>
#include <string>
#include <vector>

/// IStageInfo — 关卡信息
struct IStageInfo
{
  std::string name;
  std::optional<std::string> bg;
  std::optional<std::string> music;
  std::optional<int> difficulty;
  // phases — 待完善
};

#endif
