#ifndef LFW_CORE_DEFINES_COLLISIONVAL_HPP
#define LFW_CORE_DEFINES_COLLISIONVAL_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// 碰撞判定值 — CollisionVal.ts
#define ENUM_ITEMS(X)                                                       \
  X(CollisionVal, AttackerType, "attacker_type", "", )                      \
  X(CollisionVal, VictimType, "victim_type", "", )                          \
  X(CollisionVal, VictimIsChasing, "victim_is_chasing", "", )               \
  X(CollisionVal, ItrEffect, "itr_effect", "", )                            \
  X(CollisionVal, ItrKind, "itr_kind", "", )                                \
  X(CollisionVal, SameFacing, "same_facing", "", )                          \
  X(CollisionVal, AttackerState, "attacker_state", "", )                    \
  X(CollisionVal, VictimState, "victim_state", "", )                        \
  X(CollisionVal, AttackerHasHolder, "attacker_has_holder", "", )           \
  X(CollisionVal, VictimHasHolder, "victim_has_holder", "", )               \
  X(CollisionVal, AttackerHasHolding, "attacker_has_holding", "", )         \
  X(CollisionVal, VictimHasHolding, "victim_has_holding", "", )             \
  X(CollisionVal, SameTeam, "same_team", "", )                              \
  X(CollisionVal, AttackerOID, "attacker_oid", "", )                        \
  X(CollisionVal, VictimOID, "victim_oid", "", )                            \
  X(CollisionVal, BdyKind, "bdy_kind", "", )                                \
  X(CollisionVal, VictimFrameId, "victim_frame_id", "", )                   \
  X(CollisionVal, VictimFrameIndexIce, "victim_frame_index_ice", "", )      \
  X(CollisionVal, ItrFall, "itr_fall", "", )                                \
  X(CollisionVal, AttackerThrew, "attacker_threw", "", )                    \
  X(CollisionVal, VictimThrew, "victim_threw", "", )                        \
  X(CollisionVal, VictimIsFreezableBall, "victim_freezable_ball", "", )     \
  X(CollisionVal, AttackerIsFreezableBall, "attacker_freezable_ball", "", ) \
  X(CollisionVal, ArmorWork, "armor_work", "", )                            \
  X(CollisionVal, VFrameBehavior, "v_frame_behavior", "", )                 \
  X(CollisionVal, NoItrEffect, "no_itr_effect", "", )                       \
  X(CollisionVal, A_HP_P, "a_hp_p", "", )                                   \
  X(CollisionVal, V_HP_P, "v_hp_p", "", )                                   \
  X(CollisionVal, LF2_NET_ON, "lf2_net_on", "", )                           \
  X(CollisionVal, BdyHitFlag, "bdy_hit_flag", "", )                         \
  X(CollisionVal, ItrHitFlag, "itr_hit_flag", "", )                         \
  X(CollisionVal, BdyCode, "bdy_code", "", )                                \
  X(CollisionVal, ItrCode, "itr_code", "", )                                \
  X(CollisionVal, VToughness, "v_toughness", "", )                          \
  X(CollisionVal, AToughness, "a_toughness", "", )

enum class CollisionVal : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(CollisionValStringMap, ENUM_ITEMS, CollisionVal)
GEN_ENUM_NAME_MAP(CollisionValNameMap, ENUM_ITEMS, CollisionVal)
GEN_ENUM_DESC_MAP(CollisionValDescMap, ENUM_ITEMS, CollisionVal)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(collision_val_to_string, collision_val_from_string, CollisionVal, CollisionValStringMap)
DEFINE_ENUM_STR_CONVERTERS(collision_val_to_name, collision_val_from_name, CollisionVal, CollisionValNameMap)
DEFINE_ENUM_TO_STR(collision_val_to_desc, CollisionVal, CollisionValDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_COLLISIONVAL_HPP
