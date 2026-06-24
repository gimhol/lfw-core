#ifndef LFW_CORE_DEFINES_IPURE_PLAYER_INFO_HPP
#define LFW_CORE_DEFINES_IPURE_PLAYER_INFO_HPP

#include <optional>
#include <string>
#include <vector>

/// IPurePlayerInfo — 纯玩家信息（不含运行时状态）
struct IPurePlayerInfo
{
  std::string name;
  std::optional<std::string> id;
  std::optional<int> team;
  std::optional<bool> is_bot;
  std::optional<std::vector<std::string>> keys;
};

#endif
