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
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS_EXACT(game_key_to_string, game_key_from_string, GameKey, GameKeyStringMap)
DEFINE_ENUM_STR_CONVERTERS(game_key_to_name, game_key_from_name, GameKey, GameKeyNameMap)
DEFINE_ENUM_TO_STR(game_key_to_desc, GameKey, GameKeyDescMap)

inline auto GameKeyConflictMap = std::unordered_map<GameKey, GameKey>{
    {GameKey::L, GameKey::R},
    {GameKey::R, GameKey::L},
    {GameKey::U, GameKey::D},
    {GameKey::D, GameKey::U},
};
inline auto GameKeyLabelMap = std::unordered_map<GameKey, std::string>{
    {GameKey::L, "<"},
    {GameKey::R, ">"},
    {GameKey::U, "^"},
    {GameKey::D, "v"},
    {GameKey::A, "A"},
    {GameKey::J, "J"},
    {GameKey::Z, "D"},
};

DEFINE_ENUM_TO_STR(game_key_to_label, GameKey, GameKeyLabelMap)

inline std::optional<GameKey> conflict_key(GameKey k)
{
  auto iter = GameKeyConflictMap.find(k);
  if (iter == GameKeyConflictMap.end())
    return std::nullopt;
  return iter->second;
}

#endif // LFW_CORE_DEFINES_GAMEKEY_HPP
