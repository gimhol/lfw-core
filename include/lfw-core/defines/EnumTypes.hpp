#ifndef LFW_CORE_DEFINES_ENUMTYPES_HPP
#define LFW_CORE_DEFINES_ENUMTYPES_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>

// ========================================================================
// 实体/状态
// ========================================================================

/// EntityEnum.ts — 使用 HitFlag 位值
enum class EntityType : uint8_t
{
  Entity = 4,
  Fighter = 8,
  Weapon = 16,
  Ball = 32
};

/// EntityGroup.ts
enum class EntityGroup : uint8_t
{
  Hidden,
  Boss,
  Giant,
  Regular,
  _3000,
  VsWeapon,
  StageWeapon,
  FreezableBall,
  Freezer,
  Dev
};

inline std::string_view entity_group_to_string(EntityGroup v)
{
  switch (v)
  {
  case EntityGroup::Hidden:
    return "hidden";
  case EntityGroup::Boss:
    return "Boss";
  case EntityGroup::Giant:
    return "Giant";
  case EntityGroup::Regular:
    return "1000";
  case EntityGroup::_3000:
    return "3000";
  case EntityGroup::VsWeapon:
    return "VsWeapon";
  case EntityGroup::StageWeapon:
    return "StageWeapon";
  case EntityGroup::FreezableBall:
    return "FreezableBall";
  case EntityGroup::Freezer:
    return "Freezer";
  case EntityGroup::Dev:
    return "Dev";
  }
  return "";
}

inline std::optional<EntityGroup> entity_group_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, EntityGroup> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(EntityGroup::Dev); ++i)
    {
      auto v = static_cast<EntityGroup>(i);
      r[entity_group_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

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

// ========================================================================
// 队伍/朝向
// ========================================================================

/// TeamEnum.ts
enum class TeamEnum : uint8_t
{
  Independent,
  Team_1,
  Team_2,
  Team_3,
  Team_4,
  Team_5,
  Team_6,
  Team_7,
  Team_8,
  Max = Team_8
};

inline std::string_view team_enum_to_string(TeamEnum v)
{
  switch (v)
  {
  case TeamEnum::Independent:
    return "";
  case TeamEnum::Team_1:
    return "1";
  case TeamEnum::Team_2:
    return "2";
  case TeamEnum::Team_3:
    return "3";
  case TeamEnum::Team_4:
    return "4";
  case TeamEnum::Team_5:
    return "5";
  case TeamEnum::Team_6:
    return "6";
  case TeamEnum::Team_7:
    return "7";
  case TeamEnum::Team_8:
    // case TeamEnum::Max:
    return "8";
  }
  return "";
}

inline std::optional<TeamEnum> team_enum_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, TeamEnum> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(TeamEnum::Max); ++i)
    {
      auto v = static_cast<TeamEnum>(i);
      r[team_enum_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

/// FacingFlag.ts
enum class FacingFlag : int8_t
{
  None = 0,
  L = -1,
  Left = -1,
  R = 1,
  Right = 1,
  B = 2,
  Backward = 2,
  Ctrl = 3,
  SameAsCatcher = 4,
  SameAsBearer = 4,
  OpposingCatcher = 5,
  OpposingBearer = 5,
  AntiCtrl = 6,
  VX = 7,
  AntiVX = 8,
  Trend = 9,
};

// ========================================================================
// 碰撞
// ========================================================================

enum class BdyKind : int32_t
{
  Normal = 0,
  Criminal = 1,
  Defend = 2000,
  Ignore = 10000
};
enum class CPointKind : uint8_t
{
  Attacker = 1,
  Victim = 2
};
enum class OpointKind : uint8_t
{
  Normal = 1,
  Pick = 2
};
enum class OpointSpreading : uint8_t
{
  Normal = 0,
  Spreading = 1,
  FloatRange = 2,
  AngelBlessing = 4
};
enum class OpointMulti : uint8_t
{
  AccordingEnemies = 0,
  AccordingAllies = 1
};
enum class WpointKind : uint8_t
{
  None = 0,
  Bearer = 1,
  Holded = 2,
  Drop = 3
};

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

// ========================================================================
// Itr
// ========================================================================
enum class ItrKind : int32_t
{
  Normal = 0,
  Catch = 1,
  Pick = 2,
  ForceCatch = 3,
  CharacterThrew = 4,
  WeaponSwing = 5,
  SuperPunchMe = 6,
  PickSecretly = 7,
  Heal = 8,
  JohnShield = 9,
  MagicFlute = 10,
  MagicFlute2 = 11,
  Block = 14,
};
enum class ItrEffect : int32_t
{
  Normal = 0,
  Sharp = 1,
  Fire = 2,
  Ice = 3,
  Through = 4,
  None = 5,
  MFire1 = 20,
  MFire2 = 21,
  FireExplosion = 22,
  Explosion = 23,
  Ice2 = 30,
  Ignore = 10000,
};

// ========================================================================
// 行为/动作
// ========================================================================
enum class FrameBehavior : int32_t
{
  JohnChase = 1,
  DennisChase = 2,
  Boomerang = 3,
  AngelBlessing = 4,
  AngelBlessingStart = 5,
  DevilJudgementStart = 6,
  ChasingSameEnemy = 7,
  BatStart = 8,
  FirzenDisasterStart = 9,
};
enum class ArmorType : uint8_t
{
  Defend = 1,
  Fall = 2,
  Times = 3,
  Injury = 4
};

// ========================================================================
// 速度/控制
// ========================================================================
enum class SpeedMode : uint8_t
{
  Default = 0,
  Acc = 1,
  FixedLF2 = 2,
  FixedAcc = 3,
  AccTo = 4,
  Extra = 5,
  Fixed = 6,
  FixedAccTo = 7
};
enum class SpeedCtrl : uint8_t
{
  None = 0,
  Control = 1,
  Enable = 2,
  Disable = 3
};
enum class CtrlDevice : uint8_t
{
  Keyboard = 0,
  Gamepad1 = 1,
  Gamepad2 = 2,
  Gamepad3 = 3,
  Gamepad4 = 4,
  TouchScreen = 5
};

// ========================================================================
// 按键
// ========================================================================
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

// ========================================================================
// 世界/关卡
// ========================================================================
enum class Difficulty : uint8_t
{
  Easy = 1,
  Normal = 2,
  Difficult = 3,
  Crazy = 4,
  MIN = 1,
  MAX = 4
};
enum class SyncRender : uint8_t
{
  Unlimited = 0,
  Half = 1,
  Sync = 2,
  FPS_60 = 3,
  FPS_120 = 4
};
enum class StageGroup : uint8_t
{
  Hidden,
  Dev
};

inline std::string_view stage_group_to_string(StageGroup v)
{
  switch (v)
  {
  case StageGroup::Hidden:
    return "hidden";
  case StageGroup::Dev:
    return "Dev";
  }
  return "";
}

inline std::optional<StageGroup> stage_group_from_string(std::string_view s)
{
  static const auto m = std::unordered_map<std::string_view, StageGroup>{
      {"hidden", StageGroup::Hidden},
      {"Dev", StageGroup::Dev},
  };
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

enum class StageVal : uint8_t
{
  EnemiesCleared,
  DialogCleared,
  CurPhaseTime,
  CurDialogTime,
  PressAttack,
  PressJump,
  PressDefend,
  PressUp,
  PressDown,
  PressLeft,
  PressRight,
  Broadcast
};

inline std::string_view stage_val_to_string(StageVal v)
{
  switch (v)
  {
  case StageVal::EnemiesCleared:
    return "enemies_cleared";
  case StageVal::DialogCleared:
    return "dialog_cleared";
  case StageVal::CurPhaseTime:
    return "cur_phase_time";
  case StageVal::CurDialogTime:
    return "cur_dialog_time";
  case StageVal::PressAttack:
    return "press_attack";
  case StageVal::PressJump:
    return "press_jump";
  case StageVal::PressDefend:
    return "press_defend";
  case StageVal::PressUp:
    return "press_up";
  case StageVal::PressDown:
    return "press_down";
  case StageVal::PressLeft:
    return "press_left";
  case StageVal::PressRight:
    return "press_right";
  case StageVal::Broadcast:
    return "broadcast";
  }
  return "";
}

inline std::optional<StageVal> stage_val_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, StageVal> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(StageVal::Broadcast); ++i)
    {
      auto v = static_cast<StageVal>(i);
      r[stage_val_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

enum class WorldVal : uint8_t
{
  test
};

inline std::string_view world_val_to_string(WorldVal v)
{
  switch (v)
  {
  case WorldVal::test:
    return "test";
  }
  return "";
}

inline std::optional<WorldVal> world_val_from_string(std::string_view s)
{
  if (s == "test")
    return WorldVal::test;
  return std::nullopt;
}

enum class BackgroundGroup : uint8_t
{
  Regular,
  Hidden
};

inline std::string_view background_group_to_string(BackgroundGroup v)
{
  switch (v)
  {
  case BackgroundGroup::Regular:
    return "regular";
  case BackgroundGroup::Hidden:
    return "hidden";
  }
  return "";
}

inline std::optional<BackgroundGroup> background_group_from_string(std::string_view s)
{
  static const auto m = std::unordered_map<std::string_view, BackgroundGroup>{
      {"regular", BackgroundGroup::Regular},
      {"hidden", BackgroundGroup::Hidden},
  };
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

// ========================================================================
// 武器
// ========================================================================
enum class WeaponType : uint8_t
{
  None = 0,
  Stick = 1,
  Heavy = 2,
  Knife = 3,
  Baseball = 4,
  Drink = 5
};

// ========================================================================
// 动作/回调
// ========================================================================
enum class ActionType : uint8_t
{
  A_Sound,
  A_NextFrame,
  A_SetProp,
  A_Defend,
  A_BrokenDefend,
  V_Sound,
  V_NextFrame,
  V_SetProp,
  V_Defend,
  V_BrokenDefend,
  A_REBOUND_VX,
  V_REBOUND_VX,
  V_TURN_FACE,
  V_TURN_TEAM,
  FUSION,
  BROADCAST,
  VALUE_STEAL,
  A_BUFF,
  V_BUFF,
};
inline std::string_view action_type_to_string(ActionType v)
{
  switch (v)
  {
  case ActionType::A_Sound:
    return "a_sound";
  case ActionType::A_NextFrame:
    return "a_next_frame";
  case ActionType::A_SetProp:
    return "a_set_prop";
  case ActionType::A_Defend:
    return "a_defend";
  case ActionType::A_BrokenDefend:
    return "a_broken_defend";
  case ActionType::V_Sound:
    return "v_sound";
  case ActionType::V_NextFrame:
    return "v_next_frame";
  case ActionType::V_SetProp:
    return "v_set_prop";
  case ActionType::V_Defend:
    return "v_defend";
  case ActionType::V_BrokenDefend:
    return "v_broken_defend";
  case ActionType::A_REBOUND_VX:
    return "a_rebound_vx";
  case ActionType::V_REBOUND_VX:
    return "v_rebound_vx";
  case ActionType::V_TURN_FACE:
    return "v_turn_face";
  case ActionType::V_TURN_TEAM:
    return "v_turn_team";
  case ActionType::FUSION:
    return "fusion";
  case ActionType::BROADCAST:
    return "broadcast";
  case ActionType::VALUE_STEAL:
    return "VALUE_STEAL";
  case ActionType::A_BUFF:
    return "abuff";
  case ActionType::V_BUFF:
    return "vbuff";
  }
  return "";
}

inline std::optional<ActionType> action_type_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, ActionType> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(ActionType::V_BUFF); ++i)
    {
      auto v = static_cast<ActionType>(i);
      r[action_type_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

enum class BinOp : uint8_t
{
  LESS,
  LESS_OR_EQUAL,
  EQUAL,
  GREATER_OR_EQUAL,
  GREATER,
  NOT_EQUAL,
  IncludedBy,
  Include,
  NotIncludedBy,
  NotInclude,
};
inline std::string_view bin_op_to_string(BinOp v)
{
  switch (v)
  {
  case BinOp::LESS:
    return "<";
  case BinOp::LESS_OR_EQUAL:
    return "<=";
  case BinOp::EQUAL:
    return "==";
  case BinOp::GREATER_OR_EQUAL:
    return ">=";
  case BinOp::GREATER:
    return ">";
  case BinOp::NOT_EQUAL:
    return "!=";
  case BinOp::IncludedBy:
    return "}}";
  case BinOp::Include:
    return "{{";
  case BinOp::NotIncludedBy:
    return "!}";
  case BinOp::NotInclude:
    return "!{";
  }
  return "";
}

inline std::optional<BinOp> bin_op_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, BinOp> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(BinOp::NotInclude); ++i)
    {
      auto v = static_cast<BinOp>(i);
      r[bin_op_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

// ========================================================================
// OID.ts — 内置对象 ID
// ========================================================================
enum class OID : uint8_t
{
  Template,
  Julian,
  Firzen,
  LouisEX,
  Bat,
  Justin,
  Knight,
  Jan,
  Monk,
  Sorcerer,
  Jack,
  Mark,
  Hunter,
  Bandit,
  Deep,
  John,
  Henry,
  Rudolf,
  Louis,
  Firen,
  Freeze,
  Dennis,
  Woody,
  Davis,
  Weapon0_Stick,
  Weapon2_Hoe,
  Weapon4_Knife,
  Weapon5_Baseball,
  Weapon6_Milk,
  Weapon1_Stone,
  Weapon3_WoodenBox,
  Weapon8_Beer,
  Weapon9_Boomerang,
  Weapon10_LouisArmourA,
  Weapon11_LouisArmourB,
  Criminal,
  JohnBall,
  HenryArrow1,
  RudolfWeapon,
  DeepBall,
  HenryWind,
  DennisBall,
  WoodyBall,
  DavisBall,
  HenryArrow2,
  FreezeBall,
  FirenBall,
  FirenFlame,
  FreezeColumn,
  Weapon7_IceSword,
  JohnBiscuit,
  DennisChase,
  JackBall,
  JanChaseh,
  JanChase,
  FirzenChasef,
  FirzenChasei,
  FirzenBall,
  BatBall,
  BatChase,
  JustinBall,
  JulianBall,
  JulianBall2,
  Etc,
  BrokenWeapon,
};
inline std::string_view oid_to_string(OID v)
{
  switch (v)
  {
  case OID::Template:
    return "0";
  case OID::Julian:
    return "52";
  case OID::Firzen:
    return "51";
  case OID::LouisEX:
    return "50";
  case OID::Bat:
    return "38";
  case OID::Justin:
    return "39";
  case OID::Knight:
    return "37";
  case OID::Jan:
    return "36";
  case OID::Monk:
    return "35";
  case OID::Sorcerer:
    return "34";
  case OID::Jack:
    return "33";
  case OID::Mark:
    return "32";
  case OID::Hunter:
    return "31";
  case OID::Bandit:
    return "30";
  case OID::Deep:
    return "1";
  case OID::John:
    return "2";
  case OID::Henry:
    return "4";
  case OID::Rudolf:
    return "5";
  case OID::Louis:
    return "6";
  case OID::Firen:
    return "7";
  case OID::Freeze:
    return "8";
  case OID::Dennis:
    return "9";
  case OID::Woody:
    return "10";
  case OID::Davis:
    return "11";
  case OID::Weapon0_Stick:
    return "100";
  case OID::Weapon2_Hoe:
    return "101";
  case OID::Weapon4_Knife:
    return "120";
  case OID::Weapon5_Baseball:
    return "121";
  case OID::Weapon6_Milk:
    return "122";
  case OID::Weapon1_Stone:
    return "150";
  case OID::Weapon3_WoodenBox:
    return "151";
  case OID::Weapon8_Beer:
    return "123";
  case OID::Weapon9_Boomerang:
    return "124";
  case OID::Weapon10_LouisArmourA:
    return "217";
  case OID::Weapon11_LouisArmourB:
    return "218";
  case OID::Criminal:
    return "300";
  case OID::JohnBall:
    return "200";
  case OID::HenryArrow1:
    return "201";
  case OID::RudolfWeapon:
    return "202";
  case OID::DeepBall:
    return "203";
  case OID::HenryWind:
    return "204";
  case OID::DennisBall:
    return "205";
  case OID::WoodyBall:
    return "206";
  case OID::DavisBall:
    return "207";
  case OID::HenryArrow2:
    return "208";
  case OID::FreezeBall:
    return "209";
  case OID::FirenBall:
    return "210";
  case OID::FirenFlame:
    return "211";
  case OID::FreezeColumn:
    return "212";
  case OID::Weapon7_IceSword:
    return "213";
  case OID::JohnBiscuit:
    return "214";
  case OID::DennisChase:
    return "215";
  case OID::JackBall:
    return "216";
  case OID::JanChaseh:
    return "219";
  case OID::JanChase:
    return "220";
  case OID::FirzenChasef:
    return "221";
  case OID::FirzenChasei:
    return "222";
  case OID::FirzenBall:
    return "223";
  case OID::BatBall:
    return "224";
  case OID::BatChase:
    return "225";
  case OID::JustinBall:
    return "226";
  case OID::JulianBall:
    return "228";
  case OID::JulianBall2:
    return "229";
  case OID::Etc:
    return "998";
  case OID::BrokenWeapon:
    return "999";
  }
  return "";
}

inline std::optional<OID> oid_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, OID> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(OID::BrokenWeapon); ++i)
    {
      auto v = static_cast<OID>(i);
      r[oid_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

// ========================================================================
// AI
// ========================================================================
enum class BotState : uint8_t
{
  Idle,
  Avoiding,
  Chasing,
  Following,
  StageEnd,
  Dead
};

inline std::string_view bot_state_to_string(BotState v)
{
  switch (v)
  {
  case BotState::Idle:
    return "Idle";
  case BotState::Avoiding:
    return "Avoiding";
  case BotState::Chasing:
    return "Chasing";
  case BotState::Following:
    return "Following";
  case BotState::StageEnd:
    return "StageEnd";
  case BotState::Dead:
    return "Dead";
  }
  return "";
}

inline std::optional<BotState> bot_state_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, BotState> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(BotState::Dead); ++i)
    {
      auto v = static_cast<BotState>(i);
      r[bot_state_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

enum class BotVal : uint8_t
{
  Desire,
  BotStatus,
  EnemyY,
  EnemyDiffY,
  EnemyX,
  EnemyDiffX,
  EnemyState,
  Safe,
  EnemyOutOfRange
};

inline std::string_view bot_val_to_string(BotVal v)
{
  switch (v)
  {
  case BotVal::Desire:
    return "desire";
  case BotVal::BotStatus:
    return "bot_status";
  case BotVal::EnemyY:
    return "enemy_y";
  case BotVal::EnemyDiffY:
    return "enemy_diff_y";
  case BotVal::EnemyX:
    return "enemy_x";
  case BotVal::EnemyDiffX:
    return "enemy_diff_x";
  case BotVal::EnemyState:
    return "enemy_state";
  case BotVal::Safe:
    return "safe";
  case BotVal::EnemyOutOfRange:
    return "en_oor";
  }
  return "";
}

inline std::optional<BotVal> bot_val_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, BotVal> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(BotVal::EnemyOutOfRange); ++i)
    {
      auto v = static_cast<BotVal>(i);
      r[bot_val_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

enum class ChaseLost : uint8_t
{
  Hover = 1,
  Leave = 2,
  End = 4
};
enum class ChaseStrategy : uint8_t
{
  Default = 0,
  TillLost = 1
};

// ========================================================================
// 纹理
// ========================================================================
enum class TextureWrapping : uint8_t
{
  Repeat = 0,
  ClampToEdge = 1
};
enum class MagnFilter : uint8_t
{
  Linear = 0,
  Nearest = 1
};
enum class MinFilter : uint8_t
{
  LinearMipmapLinear = 0,
  LinearMipmapNearest = 1,
  NearestMipmapLinear = 2,
  NearestMipmapNearest = 3,
  Linear = 4,
  Nearest = 5
};

// ========================================================================
// 火花/关卡动作
// ========================================================================
enum class SparkType : uint8_t
{
  BrokenDefend,
  CriticalHit,
  SilentCriticalHit,
  DefendHit,
  Hit,
  HitFall,
  SilentHit,
  Bleed,
  BleedFall,
  CriticalBleed
};

inline std::string_view spark_type_to_string(SparkType v)
{
  switch (v)
  {
  case SparkType::BrokenDefend:
    return "broken_defend";
  case SparkType::CriticalHit:
    return "critical_hit";
  case SparkType::SilentCriticalHit:
    return "silent_critical_hit";
  case SparkType::DefendHit:
    return "defend_hit";
  case SparkType::Hit:
    return "hit";
  case SparkType::HitFall:
    return "hit_fall";
  case SparkType::SilentHit:
    return "silent_hit";
  case SparkType::Bleed:
    return "bleed";
  case SparkType::BleedFall:
    return "bleed_fall";
  case SparkType::CriticalBleed:
    return "critical_bleed";
  }
  return "";
}

inline std::optional<SparkType> spark_type_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, SparkType> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(SparkType::CriticalBleed); ++i)
    {
      auto v = static_cast<SparkType>(i);
      r[spark_type_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

enum class StageAction : uint8_t
{
  GoGoGoRight,
  EnterNextPhase,
  LoopGoGoGoRight
};

inline std::string_view stage_action_to_string(StageAction v)
{
  switch (v)
  {
  case StageAction::GoGoGoRight:
    return "gogogo_right";
  case StageAction::EnterNextPhase:
    return "enter_next_phase";
  case StageAction::LoopGoGoGoRight:
    return "loop_gogogo_right";
  }
  return "";
}

inline std::optional<StageAction> stage_action_from_string(std::string_view s)
{
  static const auto m = std::unordered_map<std::string_view, StageAction>{
      {"gogogo_right", StageAction::GoGoGoRight},
      {"enter_next_phase", StageAction::EnterNextPhase},
      {"loop_gogogo_right", StageAction::LoopGoGoGoRight},
  };
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

// ========================================================================
// 作弊/指令
// ========================================================================
enum class CheatType : uint8_t
{
  LF2_NET,
  HERO_FT,
  GIM_INK
};

inline std::string_view cheat_type_to_string(CheatType v)
{
  switch (v)
  {
  case CheatType::LF2_NET:
    return "LF2_NET";
  case CheatType::HERO_FT:
    return "HERO_FT";
  case CheatType::GIM_INK:
    return "GIM_INK";
  }
  return "";
}

inline std::optional<CheatType> cheat_type_from_string(std::string_view s)
{
  static const auto m = std::unordered_map<std::string_view, CheatType>{
      {"LF2_NET", CheatType::LF2_NET},
      {"HERO_FT", CheatType::HERO_FT},
      {"GIM_INK", CheatType::GIM_INK},
  };
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

enum class CMD : uint8_t
{
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  LF2_NET,
  HERO_FT,
  GIM_INK,
  KILL_ENEMIES,
  KILL_BOSS,
  KILL_SOLIDERS,
  KILL_OTHERS,
  DEL_PUPPET,
  SET_DIFFICULTY,
  DIST_CAM,
  LOCK_CAM,
  CHANGE_BG,
  CHANGE_STAGE,
  PAUSE
};

inline std::string_view cmd_to_string(CMD v)
{
  switch (v)
  {
  case CMD::F1:
    return "f1";
  case CMD::F2:
    return "f2";
  case CMD::F3:
    return "f3";
  case CMD::F4:
    return "f4";
  case CMD::F5:
    return "f5";
  case CMD::F6:
    return "f6";
  case CMD::F7:
    return "f7";
  case CMD::F8:
    return "f8";
  case CMD::F9:
    return "f9";
  case CMD::F10:
    return "f10";
  case CMD::LF2_NET:
    return "LF2_NET";
  case CMD::HERO_FT:
    return "HERO_FT";
  case CMD::GIM_INK:
    return "GIM_INK";
  case CMD::KILL_ENEMIES:
    return "KILL_ENEMIES";
  case CMD::KILL_BOSS:
    return "KILL_BOSS";
  case CMD::KILL_SOLIDERS:
    return "KILL_SOLIDERS";
  case CMD::KILL_OTHERS:
    return "KILL_OTHERS";
  case CMD::DEL_PUPPET:
    return "DEL_PUPPET";
  case CMD::SET_DIFFICULTY:
    return "SET_DIFFICULTY";
  case CMD::DIST_CAM:
    return "DIST_CAM";
  case CMD::LOCK_CAM:
    return "LOCK_CAM";
  case CMD::CHANGE_BG:
    return "CHANGE_BG";
  case CMD::CHANGE_STAGE:
    return "CHANGE_STAGE";
  case CMD::PAUSE:
    return "PAUSE";
  }
  return "";
}

inline std::optional<CMD> cmd_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, CMD> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(CMD::PAUSE); ++i)
    {
      auto v = static_cast<CMD>(i);
      r[cmd_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

// ========================================================================
// 碰撞判定值 — CollisionVal.ts
// ========================================================================
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

// ========================================================================
// 辅助
// ========================================================================
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

#endif // LFW_CORE_DEFINES_ENUMTYPES_HPP
