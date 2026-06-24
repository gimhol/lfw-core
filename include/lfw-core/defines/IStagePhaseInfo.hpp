#ifndef LFW_CORE_DEFINES_ISTAGE_PHASE_INFO_HPP
#define LFW_CORE_DEFINES_ISTAGE_PHASE_INFO_HPP

#include <optional>
#include <string>
#include <vector>

/// IStagePhaseInfo — 关卡阶段信息
struct IStagePhaseInfo
{
  std::optional<std::string> title;
  double bound = 0;
  std::optional<double> player_l, player_r;
  std::optional<double> camera_l, camera_r;
  // objects, dialogs — 待完善
};

#endif
