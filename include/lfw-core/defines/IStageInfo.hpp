#ifndef LFW_CORE_DEFINES_ISTAGE_INFO_HPP
#define LFW_CORE_DEFINES_ISTAGE_INFO_HPP

#include <optional>
#include <string>
#include <vector>

#include "lfw-core/defines/IStagePhaseInfo.hpp"

/// IStageInfo — 关卡信息，对应 TS IStageInfo
struct IStageInfo
{
  std::string id;
  std::string bg;
  std::string name;
  std::vector<IStagePhaseInfo> phases;

  std::optional<std::string> chapter;
  std::optional<std::string> next;
  std::optional<std::string> cond_end;         ///< 关卡结束判定
  std::optional<std::string> act_of_goto_next; ///< 通过动作
  std::optional<bool> is_starting;             ///< 是否为首个小关
  std::optional<std::string> starting_name;    ///< 起点名称
  std::optional<std::string> title;            ///< 大标题
  std::optional<std::vector<std::string>> group;
};

#endif
