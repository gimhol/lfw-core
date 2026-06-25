#ifndef LFW_CORE_DEFINES_DEFINES_HPP
#define LFW_CORE_DEFINES_DEFINES_HPP

#include <array>
#include <cstdint>

#include "lfw-core/core.hpp"
#include "lfw-core/defines/WeaponType.hpp"

LFW_NS_BEGIN

/// Defines — 全局常量，对应 TS Defines 命名空间
namespace Defines
{

// === 版本 / 屏幕 ===
inline constexpr int DATA_VERSION = 20;
inline constexpr double CLASSIC_SCREEN_WIDTH = 794;
inline constexpr double CLASSIC_SCREEN_HEIGHT = 550;
inline constexpr double MODERN_SCREEN_WIDTH = 794;
inline constexpr double MODERN_SCREEN_HEIGHT = 450;

// === 默认速度 ===
inline constexpr double DEFAULT_OPOINT_SPEED_Z = 3.5;
inline constexpr double DEFAULT_FIREN_FLAME_SPEED_Z = 0.5;

// === 武器反弹阈值 ===
inline constexpr double WT_BOUNCE_MIN_Y[] = {2, 2, 2, 2, 2, 2};
inline constexpr double WT_BOUNCE_MIN_X[] = {99, 99, 2, 99, 2, 2};
inline constexpr double WT_BOUNCE_MIN_Z[] = {99, 99, 99, 99, 99, 99};

// === 武器反弹系数 ===
inline constexpr double WT_BOUNCE_Y[] = {0.5, 0.2, 0.3, 0.2, 0.45, 0.45};
inline constexpr double WT_BOUNCE_X[] = {0.5, 0.5, 0.75, 0.5, 0.75, 0.75};
inline constexpr double WT_BOUNCE_Z[] = {0.5, 0.5, 0.75, 0.5, 0.75, 0.75};

// === 武器快速度 ===
inline constexpr double WT_FAST_Y[] = {99, 99, 1, 99, 99, 99};
inline constexpr double WT_FAST_X[] = {99, 99, 1, 99, 4, 4};
inline constexpr double WT_FAST_Z[] = {99, 99, 1, 99, 99, 99};

// === 摔落值 ===
inline constexpr double DEFAULT_FALL_VALUE_DIZZY = 40;
inline constexpr double DEFAULT_FALL_VALUE_CRITICAL = 100; // 140 - 40

// === 碰撞 ===
inline constexpr double DEFAULT_QUBE_LENGTH = 24;
inline constexpr double DEFAULT_QUBE_LENGTH_POW2 = 576; // 24²

// === 韧性 ===
inline constexpr double DEFAULT_TOUGHNESS_RESTING_MAX = 60;

// === 防御 ===
inline constexpr double DEFAULT_FORCE_BREAK_DEFEND_VALUE = 200;
inline constexpr double DEFAULT_BREAK_DEFEND_VALUE = 32;

// === 治疗 ===
inline constexpr double STATE_HEAL_SELF_HP = 104;

// === 盔甲 ===
inline constexpr double DEFAULT_ARMOR_INJURY_RATIO = 0.1;
inline constexpr double DEFAULT_ARMOR_MOTIONLESS_RATIO = 1.5;
inline constexpr double DEFAULT_ARMOR_SHAKING_RATIO = 2.0;

// === 武器重量 ===
inline constexpr double WEAPON_WEIGHT_HEAVY = 1.1;
inline constexpr double WEAPON_WEIGHT_ARROW = 0.74;
inline constexpr double WEAPON_WEIGHT_HOE = 1.0;
inline constexpr double WEAPON_WEIGHT_NORMAL = 0.9;
inline constexpr double WEAPON_WEIGHT_LIGHT = 0.74;
inline constexpr double WEAPON_WEIGHT_BASEBALL = 0.6;

// === 角色力量 ===
inline constexpr double FIGHTER_STRENGTH_STRONG = 1.5;
inline constexpr double FIGHTER_STRENGTH_NORMAL = 1.0;
inline constexpr double FIGHTER_STRENGTH_WEAK = 0.8;

// === AI 常量 ===
inline constexpr int MAX_AI_DESIRE = 10000;
inline constexpr double AI_STAY_CHASING_RANGE = 200;
inline constexpr double AI_COME_RANGE_IN_X = 75;
inline constexpr double AI_COME_RANGE_IN_Z = 76;
inline constexpr double AI_COME_RANGE_OUT_X = 120;
inline constexpr double AI_COME_RANGE_OUT_Z = 120;
inline constexpr double AI_FOLLOWING_RANGE_IN_X = 100;
inline constexpr double AI_FOLLOWING_RANGE_IN_Z = 100;
inline constexpr double AI_FOLLOWING_RANGE_OUT_X = 250;
inline constexpr double AI_FOLLOWING_RANGE_OUT_Z = 250;
inline constexpr int AI_MAX_CHASING_ENEMIES = 1;
inline constexpr int AI_MAX_AVOIDING_ENEMIES = 1;
inline constexpr int AI_MAX_DEFENDS_ENEMIES = 3;

// === 扩散数组 ===
inline const std::array<double, 13> BAT_CHASE_SPREADING_VX = {
    -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
inline const std::array<double, 5> BAT_CHASE_SPREADING_VZ = {
    -2, -1, 0, 1, 2};
inline const std::array<double, 11> DISATER_SPREADING_VX = {
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
inline const std::array<double, 13> DISATER_SPREADING_VY = {
    2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0};
inline const std::array<double, 11> DEVIL_JUDGEMENT_SPREADING_VX = {
    -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
inline const std::array<double, 13> DEVIL_JUDGEMENT_SPREADING_VY = {
    2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0};

// === 音效路径 ===
namespace Sounds
{
inline constexpr const char *StagePass = "data/m_pass.wav.mp3";
inline constexpr const char *BattleEnd = "data/m_end.wav.mp3";
} // namespace Sounds

// === 内置资源路径 ===
namespace BuiltIn_Imgs
{
inline constexpr const char *RFACE = "!sprite/RFACE@4x.png";
inline constexpr const char *CHARACTER_THUMB = "sprite/CHARACTER_THUMB.png";
} // namespace BuiltIn_Imgs

namespace BuiltIn_Dats
{
inline constexpr const char *Spark = "data/spark.obj.json5";
} // namespace BuiltIn_Dats

namespace BuiltIn_Broadcast
{
inline constexpr const char *ResetGPL = "reset_gpl";
inline constexpr const char *UpdateRandom = "update_random";
inline constexpr const char *StartGame = "start_game";
inline constexpr const char *SwitchStage = "switch_stage";
inline constexpr const char *SwitchBackground = "switch_background";
} // namespace BuiltIn_Broadcast

namespace BuiltIn_Sounds
{
inline constexpr const char *Cancel = "cancel";
inline constexpr const char *End = "end";
inline constexpr const char *Join = "join";
inline constexpr const char *Ok = "ok";
inline constexpr const char *Pass = "pass";
} // namespace BuiltIn_Sounds

// === 工具函数 ===

/** 计算 AI 意愿值 */
inline int desire(double ratio)
{
  return static_cast<int>(MAX_AI_DESIRE * ratio + 0.5);
}

} // namespace Defines

LFW_NS_END

#endif // LFW_CORE_DEFINES_DEFINES_HPP
