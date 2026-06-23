#ifndef LFW_CORE_DEFINES_TEAMENUM_HPP
#define LFW_CORE_DEFINES_TEAMENUM_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

/// TeamEnum.ts
enum class TeamEnum : uint8_t
{
  Independent,
  Team_1,
  Team_2,
  Team_3,
  Team_4,
  Team_5,
  Team_6,
  Team_7,
  Team_8,
  Max = Team_8
};

inline std::string_view team_enum_to_string(TeamEnum v)
{
  switch (v)
  {
  case TeamEnum::Independent:
    return "";
  case TeamEnum::Team_1:
    return "1";
  case TeamEnum::Team_2:
    return "2";
  case TeamEnum::Team_3:
    return "3";
  case TeamEnum::Team_4:
    return "4";
  case TeamEnum::Team_5:
    return "5";
  case TeamEnum::Team_6:
    return "6";
  case TeamEnum::Team_7:
    return "7";
  case TeamEnum::Team_8:
    // case TeamEnum::Max:
    return "8";
  }
  return "";
}

inline std::optional<TeamEnum> team_enum_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, TeamEnum> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(TeamEnum::Max); ++i)
    {
      auto v = static_cast<TeamEnum>(i);
      r[team_enum_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_TEAMENUM_HPP
