#ifndef LFW_CORE_DEFINES_GAMEKEY_HPP
#define LFW_CORE_DEFINES_GAMEKEY_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class GameKey : uint8_t
{
  L,
  Left = L,
  R,
  Right = R,
  U,
  Up = U,
  D,
  Down = D,
  A,
  Attack = A,
  J,
  Jump = J,
  Z,
  Defend = Z
};

inline std::string_view game_key_to_string(GameKey v)
{
  switch (v)
  {
  case GameKey::L:
    // case GameKey::Left:
    return "L";
  case GameKey::R:
    // case GameKey::Right:
    return "R";
  case GameKey::U:
    // case GameKey::Up:
    return "U";
  case GameKey::D:
    // case GameKey::Down:
    return "D";
  case GameKey::A:
    // case GameKey::Attack:
    return "a";
  case GameKey::J:
    // case GameKey::Jump:
    return "j";
  case GameKey::Z:
    // case GameKey::Defend:
    return "d";
  }
  return "";
}

inline std::optional<GameKey> game_key_from_string(std::string_view s)
{
  static const auto m = std::unordered_map<std::string_view, GameKey>{
      {"L", GameKey::L},
      {"R", GameKey::R},
      {"U", GameKey::U},
      {"D", GameKey::D},
      {"a", GameKey::A},
      {"j", GameKey::J},
      {"d", GameKey::Z},
  };
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

inline std::optional<GameKey> conflict_key(GameKey k)
{
  switch (k)
  {
  case GameKey::L:
    return GameKey::R;
  case GameKey::R:
    return GameKey::L;
  case GameKey::U:
    return GameKey::D;
  case GameKey::D:
    return GameKey::U;
  default:
    return std::nullopt;
  }
}

inline std::string_view game_key_symbol(GameKey k)
{
  switch (k)
  {
  case GameKey::L:
    return "<";
  case GameKey::R:
    return ">";
  case GameKey::U:
    return "^";
  case GameKey::D:
    return "v";
  case GameKey::A:
    return "A";
  case GameKey::J:
    return "J";
  case GameKey::Z:
    return "D";
  }
  return "?";
}

#endif // LFW_CORE_DEFINES_GAMEKEY_HPP
