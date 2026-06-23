#ifndef LFW_CORE_DEFINES_ENTITYVAL_HPP
#define LFW_CORE_DEFINES_ENTITYVAL_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

/// EntityVal.ts
enum class EntityVal : uint8_t
{
  TrendX,
  PressFB,
  PressUD,
  PressLR,
  HoldingWType,
  HP_P,
  LF2_NET_ON,
  HERO_FT_ON,
  GIM_INK_ON,
  HasTransformData,
  Catching,
  Caught,
  RequireSuperPunch,
  HitByCharacter,
  HitByWeapon,
  HitByBall,
  HitByState,
  HitByItrKind,
  HitByItrEffect,
  HitOnCharacter,
  HitOnWeapon,
  HitOnBall,
  HitOnState,
  HitOnSomething,
  HP,
  MP,
  VX,
  VY,
  VZ,
  FrameState,
  Shaking,
  Holding,
  HoldingHeavy,
  HoldingOID,
  HpRecoverable,
  HitByMagicFlute,
};

inline std::string_view entity_val_to_string(EntityVal v)
{
  switch (v)
  {
  case EntityVal::TrendX:
    return "trend_x";
  case EntityVal::PressFB:
    return "press_F_B";
  case EntityVal::PressUD:
    return "press_U_D";
  case EntityVal::PressLR:
    return "press_L_R";
  case EntityVal::HoldingWType:
    return "holding_w_type";
  case EntityVal::HP_P:
    return "hp_p";
  case EntityVal::LF2_NET_ON:
    return "lf2_net_on";
  case EntityVal::HERO_FT_ON:
    return "hero_ft_on";
  case EntityVal::GIM_INK_ON:
    return "gim_ink_on";
  case EntityVal::HasTransformData:
    return "has_transform_data";
  case EntityVal::Catching:
    return "catching";
  case EntityVal::Caught:
    return "caught";
  case EntityVal::RequireSuperPunch:
    return "super_punch";
  case EntityVal::HitByCharacter:
    return "hit_by_character";
  case EntityVal::HitByWeapon:
    return "hit_by_weapon";
  case EntityVal::HitByBall:
    return "hit_by_ball";
  case EntityVal::HitByState:
    return "hit_by_state";
  case EntityVal::HitByItrKind:
    return "hit_by_itr_kind";
  case EntityVal::HitByItrEffect:
    return "hit_by_itr_effect";
  case EntityVal::HitOnCharacter:
    return "hit_on_character";
  case EntityVal::HitOnWeapon:
    return "hit_on_weapon";
  case EntityVal::HitOnBall:
    return "hit_on_ball";
  case EntityVal::HitOnState:
    return "hit_on_state";
  case EntityVal::HitOnSomething:
    return "hit_on_something";
  case EntityVal::HP:
    return "hp";
  case EntityVal::MP:
    return "mp";
  case EntityVal::VX:
    return "vx";
  case EntityVal::VY:
    return "vy";
  case EntityVal::VZ:
    return "vz";
  case EntityVal::FrameState:
    return "frame_state";
  case EntityVal::Shaking:
    return "shaking";
  case EntityVal::Holding:
    return "holding";
  case EntityVal::HoldingHeavy:
    return "holdingHeavy";
  case EntityVal::HoldingOID:
    return "holdingOID";
  case EntityVal::HpRecoverable:
    return "hp_recoverable";
  case EntityVal::HitByMagicFlute:
    return "hit_by_magic_flute";
  }
  return "";
}

inline std::optional<EntityVal> entity_val_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, EntityVal> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(EntityVal::HitByMagicFlute); ++i)
    {
      auto v = static_cast<EntityVal>(i);
      r[entity_val_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_ENTITYVAL_HPP
