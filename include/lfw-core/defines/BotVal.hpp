#ifndef LFW_CORE_DEFINES_BOTVAL_HPP
#define LFW_CORE_DEFINES_BOTVAL_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class BotVal : uint8_t
{
  Desire,
  BotStatus,
  EnemyY,
  EnemyDiffY,
  EnemyX,
  EnemyDiffX,
  EnemyState,
  Safe,
  EnemyOutOfRange
};

inline std::string_view bot_val_to_string(BotVal v)
{
  switch (v)
  {
  case BotVal::Desire:
    return "desire";
  case BotVal::BotStatus:
    return "bot_status";
  case BotVal::EnemyY:
    return "enemy_y";
  case BotVal::EnemyDiffY:
    return "enemy_diff_y";
  case BotVal::EnemyX:
    return "enemy_x";
  case BotVal::EnemyDiffX:
    return "enemy_diff_x";
  case BotVal::EnemyState:
    return "enemy_state";
  case BotVal::Safe:
    return "safe";
  case BotVal::EnemyOutOfRange:
    return "en_oor";
  }
  return "";
}

inline std::optional<BotVal> bot_val_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, BotVal> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(BotVal::EnemyOutOfRange); ++i)
    {
      auto v = static_cast<BotVal>(i);
      r[bot_val_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_BOTVAL_HPP
