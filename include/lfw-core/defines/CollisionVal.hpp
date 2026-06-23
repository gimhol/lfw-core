#ifndef LFW_CORE_DEFINES_COLLISIONVAL_HPP
#define LFW_CORE_DEFINES_COLLISIONVAL_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

/// 碰撞判定值 — CollisionVal.ts
enum class CollisionVal : uint8_t
{
  AttackerType,
  VictimType,
  VictimIsChasing,
  ItrEffect,
  ItrKind,
  SameFacing,
  AttackerState,
  VictimState,
  AttackerHasHolder,
  VictimHasHolder,
  AttackerHasHolding,
  VictimHasHolding,
  SameTeam,
  AttackerOID,
  VictimOID,
  BdyKind,
  VictimFrameId,
  VictimFrameIndexIce,
  ItrFall,
  AttackerThrew,
  VictimThrew,
  VictimIsFreezableBall,
  AttackerIsFreezableBall,
  ArmorWork,
  VFrameBehavior,
  NoItrEffect,
  A_HP_P,
  V_HP_P,
  LF2_NET_ON,
  BdyHitFlag,
  ItrHitFlag,
  BdyCode,
  ItrCode,
  VToughness,
  AToughness,
};

inline std::string_view collision_val_to_string(CollisionVal v)
{
  switch (v)
  {
  case CollisionVal::AttackerType:
    return "attacker_type";
  case CollisionVal::VictimType:
    return "victim_type";
  case CollisionVal::VictimIsChasing:
    return "victim_is_chasing";
  case CollisionVal::ItrEffect:
    return "itr_effect";
  case CollisionVal::ItrKind:
    return "itr_kind";
  case CollisionVal::SameFacing:
    return "same_facing";
  case CollisionVal::AttackerState:
    return "attacker_state";
  case CollisionVal::VictimState:
    return "victim_state";
  case CollisionVal::AttackerHasHolder:
    return "attacker_has_holder";
  case CollisionVal::VictimHasHolder:
    return "victim_has_holder";
  case CollisionVal::AttackerHasHolding:
    return "attacker_has_holding";
  case CollisionVal::VictimHasHolding:
    return "victim_has_holding";
  case CollisionVal::SameTeam:
    return "same_team";
  case CollisionVal::AttackerOID:
    return "attacker_oid";
  case CollisionVal::VictimOID:
    return "victim_oid";
  case CollisionVal::BdyKind:
    return "bdy_kind";
  case CollisionVal::VictimFrameId:
    return "victim_frame_id";
  case CollisionVal::VictimFrameIndexIce:
    return "victim_frame_index_ice";
  case CollisionVal::ItrFall:
    return "itr_fall";
  case CollisionVal::AttackerThrew:
    return "attacker_threw";
  case CollisionVal::VictimThrew:
    return "victim_threw";
  case CollisionVal::VictimIsFreezableBall:
    return "victim_freezable_ball";
  case CollisionVal::AttackerIsFreezableBall:
    return "attacker_freezable_ball";
  case CollisionVal::ArmorWork:
    return "armor_work";
  case CollisionVal::VFrameBehavior:
    return "v_frame_behavior";
  case CollisionVal::NoItrEffect:
    return "no_itr_effect";
  case CollisionVal::A_HP_P:
    return "a_hp_p";
  case CollisionVal::V_HP_P:
    return "v_hp_p";
  case CollisionVal::LF2_NET_ON:
    return "lf2_net_on";
  case CollisionVal::BdyHitFlag:
    return "bdy_hit_flag";
  case CollisionVal::ItrHitFlag:
    return "itr_hit_flag";
  case CollisionVal::BdyCode:
    return "bdy_code";
  case CollisionVal::ItrCode:
    return "itr_code";
  case CollisionVal::VToughness:
    return "v_toughness";
  case CollisionVal::AToughness:
    return "a_toughness";
  }
  return "";
}

inline std::optional<CollisionVal> collision_val_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, CollisionVal> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(CollisionVal::AToughness); ++i)
    {
      auto v = static_cast<CollisionVal>(i);
      r[collision_val_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_COLLISIONVAL_HPP
