#ifndef LFW_CORE_DEFINES_IDEAD_JOIN_HPP
#define LFW_CORE_DEFINES_IDEAD_JOIN_HPP

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#include <optional>
#include <string>

/// IDeadJoin — 死亡后加入队伍信息
struct IDeadJoin
{
  std::optional<double> hp;
  std::optional<std::string> team;
};


LFW_NS_END

#endif
