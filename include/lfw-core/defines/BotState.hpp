#ifndef LFW_CORE_DEFINES_BOTSTATE_HPP
#define LFW_CORE_DEFINES_BOTSTATE_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class BotState : uint8_t
{
  Idle,
  Avoiding,
  Chasing,
  Following,
  StageEnd,
  Dead
};

inline std::string_view bot_state_to_string(BotState v)
{
  switch (v)
  {
  case BotState::Idle:
    return "Idle";
  case BotState::Avoiding:
    return "Avoiding";
  case BotState::Chasing:
    return "Chasing";
  case BotState::Following:
    return "Following";
  case BotState::StageEnd:
    return "StageEnd";
  case BotState::Dead:
    return "Dead";
  }
  return "";
}

inline std::optional<BotState> bot_state_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, BotState> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(BotState::Dead); ++i)
    {
      auto v = static_cast<BotState>(i);
      r[bot_state_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_BOTSTATE_HPP
