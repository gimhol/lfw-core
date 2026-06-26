#ifndef LFW_CORE_DEFINES_HITFLAG_HPP
#define LFW_CORE_DEFINES_HITFLAG_HPP

#include "lfw-core/core.hpp"


#include <cstdint>
#include <unordered_map>

LFW_NS_BEGIN

/// HitFlag.ts — 位域
enum class HitFlag : uint8_t
{
  Enemy = 0b00000001,
  Ally = 0b00000010,
  Others = 0b00000100,
  Fighter = 0b00001000,
  Weapon = 0b00010000,
  Ball = 0b00100000,
  Dead = 0b10000000,
  Both = Ally | Enemy,
  AllType = Others | Fighter | Weapon | Ball,
  AllEnemy = AllType | Enemy,
  AllAlly = AllType | Ally,
  AllBoth = AllType | Both,
  EnemyFighter = Enemy | Fighter,
  EnemyWeapon = Enemy | Weapon,
  AllyFighter = Ally | Fighter,
  AllyWeapon = Ally | Weapon,
  AllyBall = Ally | Ball,
};

inline HitFlag operator|(HitFlag a, HitFlag b) { return static_cast<HitFlag>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b)); }
inline HitFlag operator&(HitFlag a, HitFlag b) { return static_cast<HitFlag>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b)); }

inline const auto &hit_flag_names()
{
  static const auto m = std::unordered_map<HitFlag, const char *>{
      {HitFlag::Enemy, "Enemy"},
      {HitFlag::Ally, "Ally"},
      {HitFlag::Others, "Others"},
      {HitFlag::Fighter, "Fighter"},
      {HitFlag::Weapon, "Weapon"},
      {HitFlag::Ball, "Ball"},
      {HitFlag::Dead, "Dead"},
      {HitFlag::Both, "Both"},
      {HitFlag::AllType, "AllType"},
      {HitFlag::AllEnemy, "AllEnemy"},
      {HitFlag::AllAlly, "AllAlly"},
      {HitFlag::AllBoth, "AllBoth"},
      {HitFlag::EnemyFighter, "EnemyFighter"},
      {HitFlag::EnemyWeapon, "EnemyWeapon"},
      {HitFlag::AllyFighter, "AllyFighter"},
      {HitFlag::AllyWeapon, "AllyWeapon"},
      {HitFlag::AllyBall, "AllyBall"},
  };
  return m;
}


LFW_NS_END

#endif // LFW_CORE_DEFINES_HITFLAG_HPP
