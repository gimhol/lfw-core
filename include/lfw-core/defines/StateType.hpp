#ifndef LFW_CORE_DEFINES_STATETYPE_HPP
#define LFW_CORE_DEFINES_STATETYPE_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "EnumHelper.hpp"

/// StateEnum.ts
#define ENUM_ITEMS(X)                                                                            \
  X(StateType, EntityBase, "entity_base", "实体基类", = -1)                                      \
  X(StateType, CharacterBase, "character_base", "角色基类", = -2)                                \
  X(StateType, WeaponBase, "weapon_base", "武器基类", = -3)                                      \
  X(StateType, BallBase, "ball_base", "球基类", = -4)                                            \
  X(StateType, Standing, "standing", "站立", = 0)                                                \
  X(StateType, Walking, "walking", "行走", = 1)                                                  \
  X(StateType, Running, "running", "跑步", = 2)                                                  \
  X(StateType, Attacking, "attacking", "攻击", = 3)                                              \
  X(StateType, Jump, "jump", "跳跃", = 4)                                                        \
  X(StateType, Dash, "dash", "冲刺", = 5)                                                        \
  X(StateType, Rowing, "rowing", "受身", = 6)                                                    \
  X(StateType, Defend, "defend", "防御", = 7)                                                    \
  X(StateType, BrokenDefend, "broken_defend", "破防", = 8)                                       \
  X(StateType, Catching, "catching", "抓人", = 9)                                                \
  X(StateType, Caught, "caught", "被抓", = 10)                                                   \
  X(StateType, Injured, "injured", "受伤", = 11)                                                 \
  X(StateType, Falling, "falling", "坠落", = 12)                                                 \
  X(StateType, Frozen, "frozen", "冰冻", = 13)                                                   \
  X(StateType, Lying, "lying", "倒地", = 14)                                                     \
  X(StateType, Normal, "normal", "普通", = 15)                                                   \
  X(StateType, Tired, "tired", "疲劳", = 16)                                                     \
  X(StateType, Drink, "drink", "喝饮料", = 17)                                                   \
  X(StateType, Burning, "burning", "燃烧", = 18)                                                 \
  X(StateType, BurnRun, "burn_run", "燃烧奔跑", = 19)                                            \
  X(StateType, LandGoto94, "land_goto_94", "落地跳转94", = 100)                                  \
  X(StateType, ZMoveable, "z_moveable", "Z轴可移动", = 301)                                      \
  X(StateType, TeleportToNearestEnemy, "teleport_to_nearest_enemy", "传送至最近敌人", = 400)     \
  X(StateType, TeleportToFarthestAlly, "teleport_to_farthest_ally", "传送至最远队友", = 401)     \
  X(StateType, TransformToCatchingBegin, "transform_to_catching_begin", "变身为抓人开始", = 500) \
  X(StateType, TransformToCatchingEnd, "transform_to_catching_end", "变身为抓人结束", = 501)     \
  X(StateType, WeaponInTheSky, "weapon_in_the_sky", "武器空中", = 1000)                          \
  X(StateType, WeaponOnHand, "weapon_on_hand", "武器手持", = 1001)                               \
  X(StateType, WeaponThrowing, "weapon_throwing", "武器投掷", = 1002)                            \
  X(StateType, WeaponRebounding, "weapon_rebounding", "武器反弹", = 1003)                        \
  X(StateType, WeaponOnGround, "weapon_on_ground", "武器地面", = 1004)                           \
  X(StateType, HealSelf, "heal_self", "自愈", = 1700)                                            \
  X(StateType, HeavyWeaponInTheSky, "heavy_weapon_in_the_sky", "重武器空中", = 2000)             \
  X(StateType, HeavyWeaponOnHand, "heavy_weapon_on_hand", "重武器手持", = 2001)                  \
  X(StateType, HeavyWeaponJustOnGround, "heavy_weapon_just_on_ground", "重武器刚落地", = 2002)   \
  X(StateType, HeavyWeaponOnGround, "heavy_weapon_on_ground", "重武器地面", = 2004)              \
  X(StateType, BallFlying, "ball_flying", "波飞行", = 3000)                                      \
  X(StateType, BallHitting, "ball_hitting", "波命中", = 3001)                                    \
  X(StateType, BallHit, "ball_hit", "波被命中", = 3002)                                          \
  X(StateType, BallRebounding, "ball_rebounding", "波反弹", = 3003)                              \
  X(StateType, BallDisappear, "ball_disappear", "波消失", = 3004)                                \
  X(StateType, Ball3005, "ball_3005", "波3005", = 3005)                                          \
  X(StateType, Ball3006, "ball_3006", "波3006", = 3006)                                          \
  X(StateType, TransformToMin, "transform_to_min", "变身最小", = 8001)                           \
  X(StateType, TransformToMax, "transform_to_max", "变身最大", = 8999)                           \
  X(StateType, TurnIntoLouisEX, "turn_into_louis_ex", "变身为LouisEX", = 9995)                   \
  X(StateType, OLD_LouisCastOff, "old_louis_cast_off", "旧版Louis脱甲", = 9996)                  \
  X(StateType, Message, "message", "消息", = 9997)                                               \
  X(StateType, Gone, "gone", "消失", = 9998)                                                     \
  X(StateType, WeaponBrokens, "weapon_brokens", "武器破碎", = 9999)

enum class StateType : int32_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto StateType_MIN = StateType::EntityBase;
constexpr auto StateType_MAX = StateType::WeaponBrokens;
GEN_ENUM_STR_MAP(StateTypeStringMap, ENUM_ITEMS, StateType)
GEN_ENUM_NAME_MAP(StateTypeNameMap, ENUM_ITEMS, StateType)
GEN_ENUM_DESC_MAP(StateTypeDescMap, ENUM_ITEMS, StateType)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(state_type_to_string, state_type_from_string, StateType, StateTypeStringMap)
DEFINE_ENUM_STR_CONVERTERS(state_type_to_name, state_type_from_name, StateType, StateTypeNameMap)
DEFINE_ENUM_TO_STR(state_type_to_desc, StateType, StateTypeDescMap)

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
