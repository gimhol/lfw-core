#ifndef LFW_CORE_DEFINES_CHEATTYPE_HPP
#define LFW_CORE_DEFINES_CHEATTYPE_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class CheatType : uint8_t
{
  LF2_NET,
  HERO_FT,
  GIM_INK
};

inline std::string_view cheat_type_to_string(CheatType v)
{
  switch (v)
  {
  case CheatType::LF2_NET:
    return "LF2_NET";
  case CheatType::HERO_FT:
    return "HERO_FT";
  case CheatType::GIM_INK:
    return "GIM_INK";
  }
  return "";
}

inline std::optional<CheatType> cheat_type_from_string(std::string_view s)
{
  static const auto m = std::unordered_map<std::string_view, CheatType>{
      {"LF2_NET", CheatType::LF2_NET},
      {"HERO_FT", CheatType::HERO_FT},
      {"GIM_INK", CheatType::GIM_INK},
  };
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_CHEATTYPE_HPP
