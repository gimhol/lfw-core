#ifndef LFW_CORE_DEFINES_ENTITYVAL_HPP
#define LFW_CORE_DEFINES_ENTITYVAL_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// EntityVal.ts
#define ENUM_ITEMS(X)                                        \
  X(EntityVal, TrendX, "trend_x", "", )                      \
  X(EntityVal, PressFB, "press_F_B", "", )                   \
  X(EntityVal, PressUD, "press_U_D", "", )                   \
  X(EntityVal, PressLR, "press_L_R", "", )                   \
  X(EntityVal, HoldingWType, "holding_w_type", "", )         \
  X(EntityVal, HP_P, "hp_p", "", )                           \
  X(EntityVal, LF2_NET_ON, "lf2_net_on", "", )               \
  X(EntityVal, HERO_FT_ON, "hero_ft_on", "", )               \
  X(EntityVal, GIM_INK_ON, "gim_ink_on", "", )               \
  X(EntityVal, HasTransformData, "has_transform_data", "", ) \
  X(EntityVal, Catching, "catching", "", )                   \
  X(EntityVal, Caught, "caught", "", )                       \
  X(EntityVal, RequireSuperPunch, "super_punch", "", )       \
  X(EntityVal, HitByCharacter, "hit_by_character", "", )     \
  X(EntityVal, HitByWeapon, "hit_by_weapon", "", )           \
  X(EntityVal, HitByBall, "hit_by_ball", "", )               \
  X(EntityVal, HitByState, "hit_by_state", "", )             \
  X(EntityVal, HitByItrKind, "hit_by_itr_kind", "", )        \
  X(EntityVal, HitByItrEffect, "hit_by_itr_effect", "", )    \
  X(EntityVal, HitOnCharacter, "hit_on_character", "", )     \
  X(EntityVal, HitOnWeapon, "hit_on_weapon", "", )           \
  X(EntityVal, HitOnBall, "hit_on_ball", "", )               \
  X(EntityVal, HitOnState, "hit_on_state", "", )             \
  X(EntityVal, HitOnSomething, "hit_on_something", "", )     \
  X(EntityVal, HP, "hp", "", )                               \
  X(EntityVal, MP, "mp", "", )                               \
  X(EntityVal, VX, "vx", "", )                               \
  X(EntityVal, VY, "vy", "", )                               \
  X(EntityVal, VZ, "vz", "", )                               \
  X(EntityVal, FrameState, "frame_state", "", )              \
  X(EntityVal, Shaking, "shaking", "", )                     \
  X(EntityVal, Holding, "holding", "", )                     \
  X(EntityVal, HoldingHeavy, "holdingHeavy", "", )           \
  X(EntityVal, HoldingOID, "holdingOID", "", )               \
  X(EntityVal, HpRecoverable, "hp_recoverable", "", )        \
  X(EntityVal, HitByMagicFlute, "hit_by_magic_flute", "", )

enum class EntityVal : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(EntityValStringMap, ENUM_ITEMS, EntityVal)
GEN_ENUM_NAME_MAP(EntityValNameMap, ENUM_ITEMS, EntityVal)
GEN_ENUM_DESC_MAP(EntityValDescMap, ENUM_ITEMS, EntityVal)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(entity_val_to_string, entity_val_from_string, EntityVal, EntityValStringMap)
DEFINE_ENUM_STR_CONVERTERS(entity_val_to_name, entity_val_from_name, EntityVal, EntityValNameMap)
DEFINE_ENUM_TO_STR(entity_val_to_desc, EntityVal, EntityValDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_ENTITYVAL_HPP
