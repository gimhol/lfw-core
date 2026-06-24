#ifndef LFW_CORE_DEFINES_GAMEKEY_HPP
#define LFW_CORE_DEFINES_GAMEKEY_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)      \
  X(GameKey, L, "L", "", ) \
  X(GameKey, R, "R", "", ) \
  X(GameKey, U, "U", "", ) \
  X(GameKey, D, "D", "", ) \
  X(GameKey, A, "a", "", ) \
  X(GameKey, J, "j", "", ) \
  X(GameKey, Z, "d", "", )

#define ENUM_ITEM(ENUM, NAME, STR, DESC, VAL) NAME VAL,
enum class GameKey : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto GameKey_Left = GameKey::L;
constexpr auto GameKey_Right = GameKey::R;
constexpr auto GameKey_Up = GameKey::U;
constexpr auto GameKey_Down = GameKey::D;
constexpr auto GameKey_Attack = GameKey::A;
constexpr auto GameKey_Jump = GameKey::J;
constexpr auto GameKey_Defend = GameKey::Z;
GEN_ENUM_STR_MAP(GameKeyStringMap, ENUM_ITEMS, GameKey)
GEN_ENUM_NAME_MAP(GameKeyNameMap, ENUM_ITEMS, GameKey)
GEN_ENUM_DESC_MAP(GameKeyDescMap, ENUM_ITEMS, GameKey)
#undef ENUM_ITEM
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(game_key_to_string, game_key_from_string, GameKey, GameKeyStringMap)
DEFINE_ENUM_STR_CONVERTERS(game_key_to_name, game_key_from_name, GameKey, GameKeyNameMap)
DEFINE_ENUM_TO_STR(game_key_to_desc, GameKey, GameKeyDescMap)

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
