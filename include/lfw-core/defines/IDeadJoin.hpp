#ifndef LFW_CORE_DEFINES_IDEAD_JOIN_HPP
#define LFW_CORE_DEFINES_IDEAD_JOIN_HPP

#include <optional>
#include <string>

/// IDeadJoin — 死亡后加入队伍信息
struct IDeadJoin
{
  std::optional<double> hp;
  std::optional<std::string> team;
};

#endif
