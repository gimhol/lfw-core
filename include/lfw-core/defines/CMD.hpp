#ifndef LFW_CORE_DEFINES_CMD_HPP
#define LFW_CORE_DEFINES_CMD_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class CMD : uint8_t
{
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  LF2_NET,
  HERO_FT,
  GIM_INK,
  KILL_ENEMIES,
  KILL_BOSS,
  KILL_SOLIDERS,
  KILL_OTHERS,
  DEL_PUPPET,
  SET_DIFFICULTY,
  DIST_CAM,
  LOCK_CAM,
  CHANGE_BG,
  CHANGE_STAGE,
  PAUSE
};

inline std::string_view cmd_to_string(CMD v)
{
  switch (v)
  {
  case CMD::F1:
    return "f1";
  case CMD::F2:
    return "f2";
  case CMD::F3:
    return "f3";
  case CMD::F4:
    return "f4";
  case CMD::F5:
    return "f5";
  case CMD::F6:
    return "f6";
  case CMD::F7:
    return "f7";
  case CMD::F8:
    return "f8";
  case CMD::F9:
    return "f9";
  case CMD::F10:
    return "f10";
  case CMD::LF2_NET:
    return "LF2_NET";
  case CMD::HERO_FT:
    return "HERO_FT";
  case CMD::GIM_INK:
    return "GIM_INK";
  case CMD::KILL_ENEMIES:
    return "KILL_ENEMIES";
  case CMD::KILL_BOSS:
    return "KILL_BOSS";
  case CMD::KILL_SOLIDERS:
    return "KILL_SOLIDERS";
  case CMD::KILL_OTHERS:
    return "KILL_OTHERS";
  case CMD::DEL_PUPPET:
    return "DEL_PUPPET";
  case CMD::SET_DIFFICULTY:
    return "SET_DIFFICULTY";
  case CMD::DIST_CAM:
    return "DIST_CAM";
  case CMD::LOCK_CAM:
    return "LOCK_CAM";
  case CMD::CHANGE_BG:
    return "CHANGE_BG";
  case CMD::CHANGE_STAGE:
    return "CHANGE_STAGE";
  case CMD::PAUSE:
    return "PAUSE";
  }
  return "";
}

inline std::optional<CMD> cmd_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, CMD> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(CMD::PAUSE); ++i)
    {
      auto v = static_cast<CMD>(i);
      r[cmd_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_CMD_HPP
