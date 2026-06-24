#include <cassert>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string_view>

#include "lfw-core/defines/EnumTypes.hpp"

/// 设置环境变量 LFW_TEST_VERBOSE=1 则输出 PASS，否则默认只输出 FAIL
inline bool g_verbose = []
{
  const char *v = std::getenv("LFW_TEST_VERBOSE");
  return v && (v[0] == '1' || v[0] == 'y' || v[0] == 'Y');
}();

#define CHECK(cond, msg)                           \
  do                                               \
  {                                                \
    if (!(cond))                                   \
    {                                              \
      std::cerr << "  FAIL: " << msg << std::endl; \
      std::abort();                                \
    }                                              \
    else if (g_verbose)                            \
      std::cout << "  PASS: " << msg << std::endl; \
  } while (0)

// 辅助宏：测试 to_string + from_string 往返
#define T_ROUND(ET, V, S, PFX)                       \
  do                                                 \
  {                                                  \
    auto _str = PFX##_to_string(ET::V);              \
    CHECK(_str == S, #PFX "_to_string(" #V ")");     \
    auto _opt = PFX##_from_string(_str);             \
    CHECK(_opt.has_value() && _opt.value() == ET::V, \
          #PFX "_from_string(" #V ") roundtrip");    \
  } while (0)

// 辅助宏：测试 from_string 对非法输入返回 nullopt
#define T_INVALID(PFX) \
  CHECK(!PFX##_from_string("__invalid__").has_value(), #PFX "_from_string(invalid)")

// ========================================================================
// ActionType
// ========================================================================
static void test_action_type()
{
  T_ROUND(ActionType, A_SOUND, "A_SOUND", action_type);
  T_ROUND(ActionType, A_NEXT_FRAME, "A_NEXT_FRAME", action_type);
  T_ROUND(ActionType, A_SET_PROP, "A_SET_PROP", action_type);
  T_ROUND(ActionType, A_DEFEND, "A_DEFEND", action_type);
  T_ROUND(ActionType, A_BROKEN_DEFEND, "A_BROKEN_DEFEND", action_type);
  T_ROUND(ActionType, V_SOUND, "V_SOUND", action_type);
  T_ROUND(ActionType, V_NEXT_FRAME, "V_NEXT_FRAME", action_type);
  T_ROUND(ActionType, V_SET_PROP, "V_SET_PROP", action_type);
  T_ROUND(ActionType, V_DEFEND, "V_DEFEND", action_type);
  T_ROUND(ActionType, V_BROKEN_DEFEND, "V_BROKEN_DEFEND", action_type);
  T_ROUND(ActionType, A_REBOUND_VX, "A_REBOUND_VX", action_type);
  T_ROUND(ActionType, V_REBOUND_VX, "V_REBOUND_VX", action_type);
  T_ROUND(ActionType, V_TURN_FACE, "V_TURN_FACE", action_type);
  T_ROUND(ActionType, V_TURN_TEAM, "V_TURN_TEAM", action_type);
  T_ROUND(ActionType, FUSION, "FUSION", action_type);
  T_ROUND(ActionType, BROADCAST, "BROADCAST", action_type);
  T_ROUND(ActionType, VALUE_STEAL, "VALUE_STEAL", action_type);
  T_ROUND(ActionType, A_BUFF, "A_BUFF", action_type);
  T_ROUND(ActionType, V_BUFF, "V_BUFF", action_type);
  T_INVALID(action_type);

  // 不区分大小写
  CHECK(action_type_from_string("a_sound").value() == ActionType::A_SOUND,
        "action_type_from_string(\"a_sound\") case-insensitive");
  CHECK(action_type_from_string("fusion").value() == ActionType::FUSION,
        "action_type_from_string(\"fusion\") case-insensitive");
  CHECK(action_type_from_string("A_REBOUND_VX").value() == ActionType::A_REBOUND_VX,
        "action_type_from_string(\"A_REBOUND_VX\") case-insensitive");

  std::cout << "  PASS: ActionType (19 values, case-insensitive)\n";
}

// ========================================================================
// BinOp
// ========================================================================
static void test_bin_op()
{
  T_ROUND(BinOp, LESS, "<", bin_op);
  T_ROUND(BinOp, LESS_OR_EQUAL, "<=", bin_op);
  T_ROUND(BinOp, EQUAL, "==", bin_op);
  T_ROUND(BinOp, GREATER_OR_EQUAL, ">=", bin_op);
  T_ROUND(BinOp, GREATER, ">", bin_op);
  T_ROUND(BinOp, NOT_EQUAL, "!=", bin_op);
  T_ROUND(BinOp, IncludedBy, "}}", bin_op);
  T_ROUND(BinOp, Include, "{{", bin_op);
  T_ROUND(BinOp, NotIncludedBy, "!}", bin_op);
  T_ROUND(BinOp, NotInclude, "!{", bin_op);
  T_INVALID(bin_op);
  std::cout << "  PASS: BinOp (10 values)\n";
}

// ========================================================================
// BackgroundGroup
// ========================================================================
static void test_background_group()
{
  T_ROUND(BackgroundGroup, Regular, "regular", background_group);
  T_ROUND(BackgroundGroup, Hidden, "hidden", background_group);
  T_INVALID(background_group);
  std::cout << "  PASS: BackgroundGroup (2 values)\n";
}

// ========================================================================
// BotState
// ========================================================================
static void test_bot_state()
{
  T_ROUND(BotState, Idle, "Idle", bot_state);
  T_ROUND(BotState, Avoiding, "Avoiding", bot_state);
  T_ROUND(BotState, Chasing, "Chasing", bot_state);
  T_ROUND(BotState, Following, "Following", bot_state);
  T_ROUND(BotState, StageEnd, "StageEnd", bot_state);
  T_ROUND(BotState, Dead, "Dead", bot_state);
  T_INVALID(bot_state);
  std::cout << "  PASS: BotState (6 values)\n";
}

// ========================================================================
// BotVal
// ========================================================================
static void test_bot_val()
{
  T_ROUND(BotVal, Desire, "desire", bot_val);
  T_ROUND(BotVal, BotStatus, "bot_status", bot_val);
  T_ROUND(BotVal, EnemyY, "enemy_y", bot_val);
  T_ROUND(BotVal, EnemyDiffY, "enemy_diff_y", bot_val);
  T_ROUND(BotVal, EnemyX, "enemy_x", bot_val);
  T_ROUND(BotVal, EnemyDiffX, "enemy_diff_x", bot_val);
  T_ROUND(BotVal, EnemyState, "enemy_state", bot_val);
  T_ROUND(BotVal, Safe, "safe", bot_val);
  T_ROUND(BotVal, EnemyOutOfRange, "en_oor", bot_val);
  T_INVALID(bot_val);
  std::cout << "  PASS: BotVal (9 values)\n";
}

// ========================================================================
// CheatType
// ========================================================================
static void test_cheat_type()
{
  T_ROUND(CheatType, LF2_NET, "LF2_NET", cheat_type);
  T_ROUND(CheatType, HERO_FT, "HERO_FT", cheat_type);
  T_ROUND(CheatType, GIM_INK, "GIM_INK", cheat_type);
  T_INVALID(cheat_type);
  std::cout << "  PASS: CheatType (3 values)\n";
}

// ========================================================================
// CMD
// ========================================================================
static void test_cmd()
{
  T_ROUND(CMD, F1, "f1", cmd);
  T_ROUND(CMD, F2, "f2", cmd);
  T_ROUND(CMD, F3, "f3", cmd);
  T_ROUND(CMD, F4, "f4", cmd);
  T_ROUND(CMD, F5, "f5", cmd);
  T_ROUND(CMD, F6, "f6", cmd);
  T_ROUND(CMD, F7, "f7", cmd);
  T_ROUND(CMD, F8, "f8", cmd);
  T_ROUND(CMD, F9, "f9", cmd);
  T_ROUND(CMD, F10, "f10", cmd);
  T_ROUND(CMD, LF2_NET, "LF2_NET", cmd);
  T_ROUND(CMD, HERO_FT, "HERO_FT", cmd);
  T_ROUND(CMD, GIM_INK, "GIM_INK", cmd);
  T_ROUND(CMD, KILL_ENEMIES, "KILL_ENEMIES", cmd);
  T_ROUND(CMD, KILL_BOSS, "KILL_BOSS", cmd);
  T_ROUND(CMD, KILL_SOLIDERS, "KILL_SOLIDERS", cmd);
  T_ROUND(CMD, KILL_OTHERS, "KILL_OTHERS", cmd);
  T_ROUND(CMD, DEL_PUPPET, "DEL_PUPPET", cmd);
  T_ROUND(CMD, SET_DIFFICULTY, "SET_DIFFICULTY", cmd);
  T_ROUND(CMD, DIST_CAM, "DIST_CAM", cmd);
  T_ROUND(CMD, LOCK_CAM, "LOCK_CAM", cmd);
  T_ROUND(CMD, CHANGE_BG, "CHANGE_BG", cmd);
  T_ROUND(CMD, CHANGE_STAGE, "CHANGE_STAGE", cmd);
  T_ROUND(CMD, PAUSE, "PAUSE", cmd);
  T_INVALID(cmd);
  std::cout << "  PASS: CMD (24 values)\n";
}

// ========================================================================
// CollisionVal
// ========================================================================
static void test_collision_val()
{
  T_ROUND(CollisionVal, AttackerType, "attacker_type", collision_val);
  T_ROUND(CollisionVal, VictimType, "victim_type", collision_val);
  T_ROUND(CollisionVal, VictimIsChasing, "victim_is_chasing", collision_val);
  T_ROUND(CollisionVal, ItrEffect, "itr_effect", collision_val);
  T_ROUND(CollisionVal, ItrKind, "itr_kind", collision_val);
  T_ROUND(CollisionVal, SameFacing, "same_facing", collision_val);
  T_ROUND(CollisionVal, AttackerState, "attacker_state", collision_val);
  T_ROUND(CollisionVal, VictimState, "victim_state", collision_val);
  T_ROUND(CollisionVal, AttackerHasHolder, "attacker_has_holder", collision_val);
  T_ROUND(CollisionVal, VictimHasHolder, "victim_has_holder", collision_val);
  T_ROUND(CollisionVal, AttackerHasHolding, "attacker_has_holding", collision_val);
  T_ROUND(CollisionVal, VictimHasHolding, "victim_has_holding", collision_val);
  T_ROUND(CollisionVal, SameTeam, "same_team", collision_val);
  T_ROUND(CollisionVal, AttackerOID, "attacker_oid", collision_val);
  T_ROUND(CollisionVal, VictimOID, "victim_oid", collision_val);
  T_ROUND(CollisionVal, BdyKind, "bdy_kind", collision_val);
  T_ROUND(CollisionVal, VictimFrameId, "victim_frame_id", collision_val);
  T_ROUND(CollisionVal, VictimFrameIndexIce, "victim_frame_index_ice", collision_val);
  T_ROUND(CollisionVal, ItrFall, "itr_fall", collision_val);
  T_ROUND(CollisionVal, AttackerThrew, "attacker_threw", collision_val);
  T_ROUND(CollisionVal, VictimThrew, "victim_threw", collision_val);
  T_ROUND(CollisionVal, VictimIsFreezableBall, "victim_freezable_ball", collision_val);
  T_ROUND(CollisionVal, AttackerIsFreezableBall, "attacker_freezable_ball", collision_val);
  T_ROUND(CollisionVal, ArmorWork, "armor_work", collision_val);
  T_ROUND(CollisionVal, VFrameBehavior, "v_frame_behavior", collision_val);
  T_ROUND(CollisionVal, NoItrEffect, "no_itr_effect", collision_val);
  T_ROUND(CollisionVal, A_HP_P, "a_hp_p", collision_val);
  T_ROUND(CollisionVal, V_HP_P, "v_hp_p", collision_val);
  T_ROUND(CollisionVal, LF2_NET_ON, "lf2_net_on", collision_val);
  T_ROUND(CollisionVal, BdyHitFlag, "bdy_hit_flag", collision_val);
  T_ROUND(CollisionVal, ItrHitFlag, "itr_hit_flag", collision_val);
  T_ROUND(CollisionVal, BdyCode, "bdy_code", collision_val);
  T_ROUND(CollisionVal, ItrCode, "itr_code", collision_val);
  T_ROUND(CollisionVal, VToughness, "v_toughness", collision_val);
  T_ROUND(CollisionVal, AToughness, "a_toughness", collision_val);
  T_INVALID(collision_val);
  std::cout << "  PASS: CollisionVal (35 values)\n";
}

// ========================================================================
// EntityGroup
// ========================================================================
static void test_entity_group()
{
  T_ROUND(EntityGroup, Hidden, "hidden", entity_group);
  T_ROUND(EntityGroup, Boss, "Boss", entity_group);
  T_ROUND(EntityGroup, Giant, "Giant", entity_group);
  T_ROUND(EntityGroup, Regular, "1000", entity_group);
  T_ROUND(EntityGroup, _3000, "3000", entity_group);
  T_ROUND(EntityGroup, VsWeapon, "VsWeapon", entity_group);
  T_ROUND(EntityGroup, StageWeapon, "StageWeapon", entity_group);
  T_ROUND(EntityGroup, FreezableBall, "FreezableBall", entity_group);
  T_ROUND(EntityGroup, Freezer, "Freezer", entity_group);
  T_ROUND(EntityGroup, Dev, "Dev", entity_group);
  T_INVALID(entity_group);
  std::cout << "  PASS: EntityGroup (10 values)\n";
}

// ========================================================================
// EntityVal
// ========================================================================
static void test_entity_val()
{
  T_ROUND(EntityVal, TrendX, "trend_x", entity_val);
  T_ROUND(EntityVal, PressFB, "press_F_B", entity_val);
  T_ROUND(EntityVal, PressUD, "press_U_D", entity_val);
  T_ROUND(EntityVal, PressLR, "press_L_R", entity_val);
  T_ROUND(EntityVal, HoldingWType, "holding_w_type", entity_val);
  T_ROUND(EntityVal, HP_P, "hp_p", entity_val);
  T_ROUND(EntityVal, LF2_NET_ON, "lf2_net_on", entity_val);
  T_ROUND(EntityVal, HERO_FT_ON, "hero_ft_on", entity_val);
  T_ROUND(EntityVal, GIM_INK_ON, "gim_ink_on", entity_val);
  T_ROUND(EntityVal, HasTransformData, "has_transform_data", entity_val);
  T_ROUND(EntityVal, Catching, "catching", entity_val);
  T_ROUND(EntityVal, Caught, "caught", entity_val);
  T_ROUND(EntityVal, RequireSuperPunch, "super_punch", entity_val);
  T_ROUND(EntityVal, HitByCharacter, "hit_by_character", entity_val);
  T_ROUND(EntityVal, HitByWeapon, "hit_by_weapon", entity_val);
  T_ROUND(EntityVal, HitByBall, "hit_by_ball", entity_val);
  T_ROUND(EntityVal, HitByState, "hit_by_state", entity_val);
  T_ROUND(EntityVal, HitByItrKind, "hit_by_itr_kind", entity_val);
  T_ROUND(EntityVal, HitByItrEffect, "hit_by_itr_effect", entity_val);
  T_ROUND(EntityVal, HitOnCharacter, "hit_on_character", entity_val);
  T_ROUND(EntityVal, HitOnWeapon, "hit_on_weapon", entity_val);
  T_ROUND(EntityVal, HitOnBall, "hit_on_ball", entity_val);
  T_ROUND(EntityVal, HitOnState, "hit_on_state", entity_val);
  T_ROUND(EntityVal, HitOnSomething, "hit_on_something", entity_val);
  T_ROUND(EntityVal, HP, "hp", entity_val);
  T_ROUND(EntityVal, MP, "mp", entity_val);
  T_ROUND(EntityVal, VX, "vx", entity_val);
  T_ROUND(EntityVal, VY, "vy", entity_val);
  T_ROUND(EntityVal, VZ, "vz", entity_val);
  T_ROUND(EntityVal, FrameState, "frame_state", entity_val);
  T_ROUND(EntityVal, Shaking, "shaking", entity_val);
  T_ROUND(EntityVal, Holding, "holding", entity_val);
  T_ROUND(EntityVal, HoldingHeavy, "holdingHeavy", entity_val);
  T_ROUND(EntityVal, HoldingOID, "holdingOID", entity_val);
  T_ROUND(EntityVal, HpRecoverable, "hp_recoverable", entity_val);
  T_ROUND(EntityVal, HitByMagicFlute, "hit_by_magic_flute", entity_val);
  T_INVALID(entity_val);
  std::cout << "  PASS: EntityVal (36 values)\n";
}

// ========================================================================
// GameKey
// ========================================================================
static void test_game_key()
{
  T_ROUND(GameKey, L, "L", game_key);
  T_ROUND(GameKey, R, "R", game_key);
  T_ROUND(GameKey, U, "U", game_key);
  T_ROUND(GameKey, D, "D", game_key);
  T_ROUND(GameKey, A, "a", game_key);
  T_ROUND(GameKey, J, "j", game_key);
  T_ROUND(GameKey, Z, "d", game_key);
  T_INVALID(game_key);
  std::cout << "  PASS: GameKey (7 values)\n";
}

// ========================================================================
// OID
// ========================================================================
static void test_oid()
{
  T_ROUND(OID, Template, "0", oid);
  T_ROUND(OID, Deep, "1", oid);
  T_ROUND(OID, John, "2", oid);
  T_ROUND(OID, Henry, "4", oid);
  T_ROUND(OID, Rudolf, "5", oid);
  T_ROUND(OID, Louis, "6", oid);
  T_ROUND(OID, Firen, "7", oid);
  T_ROUND(OID, Freeze, "8", oid);
  T_ROUND(OID, Dennis, "9", oid);
  T_ROUND(OID, Woody, "10", oid);
  T_ROUND(OID, Davis, "11", oid);
  T_ROUND(OID, Bandit, "30", oid);
  T_ROUND(OID, Hunter, "31", oid);
  T_ROUND(OID, Mark, "32", oid);
  T_ROUND(OID, Jack, "33", oid);
  T_ROUND(OID, Sorcerer, "34", oid);
  T_ROUND(OID, Monk, "35", oid);
  T_ROUND(OID, Jan, "36", oid);
  T_ROUND(OID, Knight, "37", oid);
  T_ROUND(OID, Bat, "38", oid);
  T_ROUND(OID, Justin, "39", oid);
  T_ROUND(OID, LouisEX, "50", oid);
  T_ROUND(OID, Firzen, "51", oid);
  T_ROUND(OID, Julian, "52", oid);
  T_ROUND(OID, Weapon0_Stick, "100", oid);
  T_ROUND(OID, Weapon2_Hoe, "101", oid);
  T_ROUND(OID, Weapon4_Knife, "120", oid);
  T_ROUND(OID, Weapon5_Baseball, "121", oid);
  T_ROUND(OID, Weapon6_Milk, "122", oid);
  T_ROUND(OID, Weapon8_Beer, "123", oid);
  T_ROUND(OID, Weapon9_Boomerang, "124", oid);
  T_ROUND(OID, Weapon1_Stone, "150", oid);
  T_ROUND(OID, Weapon3_WoodenBox, "151", oid);
  T_ROUND(OID, JohnBall, "200", oid);
  T_ROUND(OID, HenryArrow1, "201", oid);
  T_ROUND(OID, RudolfWeapon, "202", oid);
  T_ROUND(OID, DeepBall, "203", oid);
  T_ROUND(OID, HenryWind, "204", oid);
  T_ROUND(OID, DennisBall, "205", oid);
  T_ROUND(OID, WoodyBall, "206", oid);
  T_ROUND(OID, DavisBall, "207", oid);
  T_ROUND(OID, HenryArrow2, "208", oid);
  T_ROUND(OID, FreezeBall, "209", oid);
  T_ROUND(OID, FirenBall, "210", oid);
  T_ROUND(OID, FirenFlame, "211", oid);
  T_ROUND(OID, FreezeColumn, "212", oid);
  T_ROUND(OID, Weapon7_IceSword, "213", oid);
  T_ROUND(OID, JohnBiscuit, "214", oid);
  T_ROUND(OID, DennisChase, "215", oid);
  T_ROUND(OID, JackBall, "216", oid);
  T_ROUND(OID, Weapon10_LouisArmourA, "217", oid);
  T_ROUND(OID, Weapon11_LouisArmourB, "218", oid);
  T_ROUND(OID, JanChaseh, "219", oid);
  T_ROUND(OID, JanChase, "220", oid);
  T_ROUND(OID, FirzenChasef, "221", oid);
  T_ROUND(OID, FirzenChasei, "222", oid);
  T_ROUND(OID, FirzenBall, "223", oid);
  T_ROUND(OID, BatBall, "224", oid);
  T_ROUND(OID, BatChase, "225", oid);
  T_ROUND(OID, JustinBall, "226", oid);
  T_ROUND(OID, JulianBall, "228", oid);
  T_ROUND(OID, JulianBall2, "229", oid);
  T_ROUND(OID, Criminal, "300", oid);
  T_ROUND(OID, Etc, "998", oid);
  T_ROUND(OID, BrokenWeapon, "999", oid);
  T_INVALID(oid);
  std::cout << "  PASS: OID (65 values)\n";
}

// ========================================================================
// SparkType
// ========================================================================
static void test_spark_type()
{
  T_ROUND(SparkType, BrokenDefend, "broken_defend", spark_type);
  T_ROUND(SparkType, CriticalHit, "critical_hit", spark_type);
  T_ROUND(SparkType, SilentCriticalHit, "silent_critical_hit", spark_type);
  T_ROUND(SparkType, DefendHit, "defend_hit", spark_type);
  T_ROUND(SparkType, Hit, "hit", spark_type);
  T_ROUND(SparkType, HitFall, "hit_fall", spark_type);
  T_ROUND(SparkType, SilentHit, "silent_hit", spark_type);
  T_ROUND(SparkType, Bleed, "bleed", spark_type);
  T_ROUND(SparkType, BleedFall, "bleed_fall", spark_type);
  T_ROUND(SparkType, CriticalBleed, "critical_bleed", spark_type);
  T_INVALID(spark_type);
  std::cout << "  PASS: SparkType (10 values)\n";
}

// ========================================================================
// StageAction
// ========================================================================
static void test_stage_action()
{
  T_ROUND(StageAction, GoGoGoRight, "gogogo_right", stage_action);
  T_ROUND(StageAction, EnterNextPhase, "enter_next_phase", stage_action);
  T_ROUND(StageAction, LoopGoGoGoRight, "loop_gogogo_right", stage_action);
  T_INVALID(stage_action);
  std::cout << "  PASS: StageAction (3 values)\n";
}

// ========================================================================
// StageGroup
// ========================================================================
static void test_stage_group()
{
  T_ROUND(StageGroup, Hidden, "hidden", stage_group);
  T_ROUND(StageGroup, Dev, "Dev", stage_group);
  T_INVALID(stage_group);
  std::cout << "  PASS: StageGroup (2 values)\n";
}

// ========================================================================
// StageVal
// ========================================================================
static void test_stage_val()
{
  T_ROUND(StageVal, EnemiesCleared, "enemies_cleared", stage_val);
  T_ROUND(StageVal, DialogCleared, "dialog_cleared", stage_val);
  T_ROUND(StageVal, CurPhaseTime, "cur_phase_time", stage_val);
  T_ROUND(StageVal, CurDialogTime, "cur_dialog_time", stage_val);
  T_ROUND(StageVal, PressAttack, "press_attack", stage_val);
  T_ROUND(StageVal, PressJump, "press_jump", stage_val);
  T_ROUND(StageVal, PressDefend, "press_defend", stage_val);
  T_ROUND(StageVal, PressUp, "press_up", stage_val);
  T_ROUND(StageVal, PressDown, "press_down", stage_val);
  T_ROUND(StageVal, PressLeft, "press_left", stage_val);
  T_ROUND(StageVal, PressRight, "press_right", stage_val);
  T_ROUND(StageVal, Broadcast, "broadcast", stage_val);
  T_INVALID(stage_val);
  std::cout << "  PASS: StageVal (12 values)\n";
}

// ========================================================================
// TeamEnum (Independent 映射为空字符串，跳过 from_string 往返)
// ========================================================================
static void test_team_enum()
{
  // Independent → ""
  CHECK(team_enum_to_string(TeamEnum::Independent) == "",
        "team_enum_to_string(Independent) == \"\"");

  T_ROUND(TeamEnum, Team_1, "1", team_enum);
  T_ROUND(TeamEnum, Team_2, "2", team_enum);
  T_ROUND(TeamEnum, Team_3, "3", team_enum);
  T_ROUND(TeamEnum, Team_4, "4", team_enum);
  T_ROUND(TeamEnum, Team_5, "5", team_enum);
  T_ROUND(TeamEnum, Team_6, "6", team_enum);
  T_ROUND(TeamEnum, Team_7, "7", team_enum);
  T_ROUND(TeamEnum, Team_8, "8", team_enum);
  T_INVALID(team_enum);
  std::cout << "  PASS: TeamEnum (9 values, Independent uses empty string)\n";
}

// ========================================================================
// WorldVal
// ========================================================================
static void test_world_val()
{
  T_ROUND(WorldVal, test, "test", world_val);
  T_INVALID(world_val);
  std::cout << "  PASS: WorldVal (1 value)\n";
}

// ========================================================================
// Builtin_FrameId (None 映射为空字符串)
// ========================================================================
static void test_builtin_frame_id()
{
  CHECK(builtin_frame_id_to_string(Builtin_FrameId::None) == "",
        "builtin_frame_id_to_string(None) == \"\"");

  T_ROUND(Builtin_FrameId, Auto, "auto", builtin_frame_id);
  T_ROUND(Builtin_FrameId, Self, "self", builtin_frame_id);
  T_ROUND(Builtin_FrameId, Gone, "gone", builtin_frame_id);
  T_ROUND(Builtin_FrameId, Invisible_Min, "1100", builtin_frame_id);
  T_ROUND(Builtin_FrameId, Invisible_Max, "1299", builtin_frame_id);
  T_ROUND(Builtin_FrameId, Respawn, "respawn", builtin_frame_id);
  T_INVALID(builtin_frame_id);
  std::cout << "  PASS: Builtin_FrameId (7 values, None uses empty string)\n";
}

// ========================================================================
void run_enum_string_tests()
{
  std::cout << "  --- enum to_string/from_string ---\n";

  test_action_type();
  test_bin_op();
  test_background_group();
  test_bot_state();
  test_bot_val();
  test_cheat_type();
  test_cmd();
  test_collision_val();
  test_entity_group();
  test_entity_val();
  test_game_key();
  test_oid();
  test_spark_type();
  test_stage_action();
  test_stage_group();
  test_stage_val();
  test_team_enum();
  test_world_val();
  test_builtin_frame_id();
}
