#ifndef LFW_CORE_DEFINES_STATETYPE_HPP
#define LFW_CORE_DEFINES_STATETYPE_HPP

#include <cstdint>
#include <vector>

/// StateEnum.ts
enum class StateType : int32_t
{
  EntityBase = -1,
  CharacterBase = -2,
  WeaponBase = -3,
  BallBase = -4,
  Standing = 0,
  Walking = 1,
  Running = 2,
  Attacking = 3,
  Jump = 4,
  Dash = 5,
  Rowing = 6,
  Defend = 7,
  BrokenDefend = 8,
  Catching = 9,
  Caught = 10,
  Injured = 11,
  Falling = 12,
  Frozen = 13,
  Lying = 14,
  Normal = 15,
  Tired = 16,
  Drink = 17,
  Burning = 18,
  BurnRun = 19,
  LandGoto94 = 100,
  ZMoveable = 301,
  TeleportToNearestEnemy = 400,
  TeleportToFarthestAlly = 401,
  WeaponInTheSky = 1000,
  WeaponOnHand = 1001,
  WeaponThrowing = 1002,
  WeaponRebounding = 1003,
  WeaponOnGround = 1004,
  HealSelf = 1700,
  HeavyWeaponInTheSky = 2000,
  HeavyWeaponOnHand = 2001,
  HeavyWeaponJustOnGround = 2002,
  HeavyWeaponOnGround = 2004,
  BallFlying = 3000,
  BallHitting = 3001,
  BallHit = 3002,
  BallRebounding = 3003,
  BallDisappear = 3004,
  Ball3005 = 3005,
  Ball3006 = 3006,
  TransformToMin = 8001,
  TransformToMax = 8999,
  TurnIntoLouisEX = 9995,
  OLD_LouisCastOff = 9996,
  Message = 9997,
  Gone = 9998,
  WeaponBrokens = 9999,
  TransformToCatchingBegin = 500,
  TransformToCatchingEnd = 501,
};

inline const std::vector<StateType> &attacking_states()
{
  static const auto v = std::vector<StateType>{
      StateType::Attacking,
      StateType::Ball3005,
      StateType::Ball3006,
      StateType::BallFlying,
      StateType::BallHitting,
      StateType::BallHit,
      StateType::BurnRun,
      StateType::ZMoveable,
      StateType::HeavyWeaponJustOnGround,
      StateType::WeaponThrowing,
      StateType::Burning,
  };
  return v;
}

#endif // LFW_CORE_DEFINES_STATETYPE_HPP
