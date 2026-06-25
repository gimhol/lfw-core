#ifndef LFW_CORE_DEFINES_IWORLD_DATASET_HPP
#define LFW_CORE_DEFINES_IWORLD_DATASET_HPP

#include <string>

#include "CheatType.hpp"
#include "Difficulty.hpp"
#include "SyncRender.hpp"
#include "lfw-core/base/Fields.hpp"

/// IWorldDataset — 世界数据集（全局物理/战斗参数）
struct IWorldDataset
{
  // === ITR 相关 ===
  double itr_fall = 0;
  double itr_shaking = 0;         ///< 被击中的对象晃动多少帧
  double itr_motionless = 0;      ///< 角色击中敌人的对象停顿多少帧
  double ball_itr_motionless = 0; ///< 波击中敌人的对象停顿多少帧
  double itr_arest = 0;

  // === 速度缩放系数 ===
  double fvx_f = 0; ///< frame.dvx 缩放系数
  double fvy_f = 0; ///< frame.dvy 缩放系数
  double fvz_f = 0; ///< frame.dvz 缩放系数
  double ivx_f = 0; ///< itr.dvx 缩放系数
  double ivy_f = 0; ///< itr.dvy 缩放系数
  double ivz_f = 0; ///< itr.dvz 缩放系数

  // === 默认速度 ===
  double ivx_d = 0; ///< 默认 itr.dvx（击飞速度 X）
  double ivy_d = 0; ///< 默认 itr.dvy（击飞速度 Y）
  double cvx_d = 0; ///< 停抓后 VX
  double cvy_d = 0; ///< 停抓后 VY

  // === 丢人初速度缩放系数 ===
  double tvx_f = 0;
  double tvy_f = 0;
  double tvz_f = 0;

  // === 闪烁无敌时间 ===
  double begin_blink_time = 0; ///< 角色进入场地时的闪烁无敌时间
  double lying_blink_time = 0; ///< 倒地起身后的闪烁无敌时间
  double gone_blink_time = 0;  ///< 「非玩家角色」死亡后的闪烁时间

  // === VREST / AREST ===
  double vrest_offset = 0;
  double min_vrest = 0;
  double arest_offset = 0;
  double min_arest = 0;

  // === 帧等待偏移 ===
  double wait_offset = 0;

  // === 角色反弹 ===
  double cha_bc_spd = 0;
  double cha_bc_tst_spd_x = 0; ///< 角色倒地反弹判定速度 X
  double cha_bc_tst_spd_y = 0; ///< 角色倒地反弹判定速度 Y

  // === HP / MP 恢复 ===
  double hp_recoverability = 0;
  double hp_r_ticks = 0; ///< 暗血恢复周期（每几帧回一次血）
  double hp_r_value = 0; ///< 暗血恢复量（每次回血的回血量）
  double hp_healing_ticks = 0;
  double hp_healing_value = 0;
  double mp_r_ticks = 0;
  double mp_r_ratio = 0;

  // === 按键判定 ===
  double double_click_interval = 0; ///< 按键「双击」判定间隔（帧）
  double key_hit_duration = 0;      ///< 按键「按下」/「双击」判定持续帧

  // === 摩擦力 ===
  double friction_factor = 0;      ///< 地面摩擦因子（每帧速度乘以此值）
  double friction_x = 0;           ///< 地面摩擦 X（每帧速度 X 向 0 靠近）
  double friction_z = 0;           ///< 地面摩擦 Z（每帧速度 Z 向 0 靠近）
  double land_friction_factor = 0; ///< 落地摩擦因子
  double land_friction_x = 0;
  double land_friction_z = 0;

  // === 屏幕 / 重力 ===
  double screen_w = 0;
  double screen_h = 0;
  double gravity = 0;   ///< 重力加速度
  double gravity_d = 0; ///< 重力加速度（防御时）
  double weapon_throwing_gravity = 0;

  // === 同步渲染 / 难度 ===
  double sync_render = 0; ///< 0=无限制, 见 SyncRender
  Difficulty difficulty = Difficulty::Normal;

  // === 开关类 ===
  double infinity_mp = 0; ///< 是否无限蓝

  // === 摔落值 / 防御值 ===
  double fall_r_ticks = 0;   ///< 摔落值恢复周期
  double fall_r_value = 0;   ///< 摔落值恢复量
  double defend_r_ticks = 0; ///< 防御值恢复周期
  double defend_r_value = 0; ///< 防御值恢复量
  double fall_value_max = 0;
  double catch_time_max = 0; ///< 角色抓人能抓多久
  double defend_value_max = 0;
  double defend_ratio = 0; ///< 防御生效时仍扣除多少比例的血

  // === 最大值 ===
  double mp_max = 0;
  double hp_max = 0;
  double resting_max = 0;

  // === VREST / AREST 行为 ===
  double vrest_after_shaking = 0;
  double arest_after_motionless = 0;
  double invisible_blinking = 0; ///< 隐身结束后的闪烁时长

  // === 跳跃 / 冲刺 ===
  double jump_x_f = 0;
  double jump_z_f = 0;
  double jump_h_f = 0;
  double dash_x_f = 0;
  double dash_z_f = 0;
  double dash_h_f = 0;
  double bfall_x_f = 0;
  double bfall_h_f = 0;
  double jump_height = 0;
  double jump_distance = 0;
  double jump_distancez = 0;
  double dash_height = 0;
  double dash_distance = 0;
  double dash_distancez = 0;

  // === 受身 ===
  double rowing_height = 0;   ///< 默认受身速度 Y
  double rowing_distance = 0; ///< 默认受身速度 X

  // === 武器投掷 ===
  double wvx_f = 0;
  double wvy_f = 0;
  double wvz_f = 0;

  // === 旋风 ===
  double whirlwind_vy_max = 0;
  double whirlwind_acc_y = 0;
  double whirlwind_acc_x = 0;
  double whirlwind_acc_z = 0;

  // === 渲染 / 指示器 ===
  double outline_enabled = 0;
  double indicator_flags = 0;

  // === 时间 ===
  double UPS = 30;
  double playrate = 1;
  double atom_time = 0;

  // === 作弊码 ===
  double lf2_net = 0; ///< CheatEnum::LF2_NET
  double hero_ft = 0; ///< CheatEnum::HERO_FT
  double gim_ink = 0; ///< CheatEnum::GIM_INK
};

inline const auto &world_dataset_fields()
{
  static const auto fs = fields<IWorldDataset>(
      field("gravity", FieldKind::Float, &IWorldDataset::gravity, "重力"),
      field("gravity_d", FieldKind::Float, &IWorldDataset::gravity_d, "重力D"),
      field("jump_x_f", FieldKind::Float, &IWorldDataset::jump_x_f, "跳跃速度系数X"),
      field("jump_h_f", FieldKind::Float, &IWorldDataset::jump_h_f, "跳跃速度系数Y"),
      field("jump_z_f", FieldKind::Float, &IWorldDataset::jump_z_f, "跳跃速度系数Z"),
      field("dash_x_f", FieldKind::Float, &IWorldDataset::dash_x_f, "跑跳速度系数X"),
      field("dash_h_f", FieldKind::Float, &IWorldDataset::dash_h_f, "跑跳速度系数Y"),
      field("dash_z_f", FieldKind::Float, &IWorldDataset::dash_z_f, "跑跳速度系数Z"),
      field("bfall_x_f", FieldKind::Float, &IWorldDataset::bfall_x_f, "受身速度系数X"),
      field("bfall_h_f", FieldKind::Float, &IWorldDataset::bfall_h_f, "受身速度系数Y"),
      field("weapon_throwing_gravity", FieldKind::Float, &IWorldDataset::weapon_throwing_gravity, "投掷武器重力"),
      field("begin_blink_time", FieldKind::Float, &IWorldDataset::begin_blink_time, "入场闪烁时长"),
      field("gone_blink_time", FieldKind::Float, &IWorldDataset::gone_blink_time, "消失闪烁时长"),
      field("lying_blink_time", FieldKind::Float, &IWorldDataset::lying_blink_time, "起身闪烁时长"),
      field("double_click_interval", FieldKind::Float, &IWorldDataset::double_click_interval, "双击判定时长"),
      field("key_hit_duration", FieldKind::Float, &IWorldDataset::key_hit_duration, "按键判定时长"),
      field("itr_shaking", FieldKind::Float, &IWorldDataset::itr_shaking, "受伤摇晃时长"),
      field("itr_motionless", FieldKind::Float, &IWorldDataset::itr_motionless, "角色命中停顿时长"),
      field("ball_itr_motionless", FieldKind::Float, &IWorldDataset::ball_itr_motionless, "波命中停顿时长"),
      field("hp_healing_ticks", FieldKind::Float, &IWorldDataset::hp_healing_ticks, "治疗回血周期"),
      field("hp_healing_value", FieldKind::Float, &IWorldDataset::hp_healing_value, "治疗回血量"),
      field("fvx_f", FieldKind::Float, &IWorldDataset::fvx_f, "frame.dvx缩放系数"),
      field("fvy_f", FieldKind::Float, &IWorldDataset::fvy_f, "frame.dvy缩放系数"),
      field("fvz_f", FieldKind::Float, &IWorldDataset::fvz_f, "frame.dvz缩放系数"),
      field("ivx_f", FieldKind::Float, &IWorldDataset::ivx_f, "itr.dvx缩放系数"),
      field("ivy_f", FieldKind::Float, &IWorldDataset::ivy_f, "itr.dvy缩放系数"),
      field("ivz_f", FieldKind::Float, &IWorldDataset::ivz_f, "itr.dvz缩放系数"),
      field("ivy_d", FieldKind::Float, &IWorldDataset::ivy_d, "itr.dvy默认值"),
      field("ivx_d", FieldKind::Float, &IWorldDataset::ivx_d, "itr.dvx默认值"),
      field("cvx_d", FieldKind::Float, &IWorldDataset::cvx_d, "停抓vx"),
      field("cvy_d", FieldKind::Float, &IWorldDataset::cvy_d, "停抓vy"),
      field("tvx_f", FieldKind::Float, &IWorldDataset::tvx_f, "丢人速度系数X"),
      field("tvy_f", FieldKind::Float, &IWorldDataset::tvy_f, "丢人速度系数Y"),
      field("tvz_f", FieldKind::Float, &IWorldDataset::tvz_f, "丢人速度系数Z"),
      field("wvx_f", FieldKind::Float, &IWorldDataset::wvx_f, "丢武器速度系数X"),
      field("wvy_f", FieldKind::Float, &IWorldDataset::wvy_f, "丢武器速度系数Y"),
      field("wvz_f", FieldKind::Float, &IWorldDataset::wvz_f, "丢武器速度系数Z"),
      field("friction_factor", FieldKind::Float, &IWorldDataset::friction_factor, "地速衰减系数"),
      field("friction_x", FieldKind::Float, &IWorldDataset::friction_x, "地面摩擦X"),
      field("friction_z", FieldKind::Float, &IWorldDataset::friction_z, "地面摩擦Z"),
      field("land_friction_factor", FieldKind::Float, &IWorldDataset::land_friction_factor, "落地摩擦因子"),
      field("land_friction_x", FieldKind::Float, &IWorldDataset::land_friction_x, "落地摩擦X"),
      field("land_friction_z", FieldKind::Float, &IWorldDataset::land_friction_z, "落地摩擦Z"),
      field("hp_recoverability", FieldKind::Float, &IWorldDataset::hp_recoverability, "可回血比例"),
      field("hp_r_ticks", FieldKind::Float, &IWorldDataset::hp_r_ticks, "回血周期"),
      field("hp_r_value", FieldKind::Float, &IWorldDataset::hp_r_value, "回血量"),
      field("mp_r_ticks", FieldKind::Float, &IWorldDataset::mp_r_ticks, "回蓝周期"),
      field("mp_r_ratio", FieldKind::Float, &IWorldDataset::mp_r_ratio, "回蓝速率系数"),
      field("infinity_mp", FieldKind::Float, &IWorldDataset::infinity_mp, "无限MP"),
      field("fall_r_ticks", FieldKind::Float, &IWorldDataset::fall_r_ticks, "摔落值恢复周期"),
      field("fall_r_value", FieldKind::Float, &IWorldDataset::fall_r_value, "摔落值恢复量"),
      field("defend_r_ticks", FieldKind::Float, &IWorldDataset::defend_r_ticks, "防御值恢复周期"),
      field("defend_r_value", FieldKind::Float, &IWorldDataset::defend_r_value, "防御值恢复量"),
      field("jump_height", FieldKind::Float, &IWorldDataset::jump_height, "跳跃速度Y"),
      field("jump_distance", FieldKind::Float, &IWorldDataset::jump_distance, "跳跃速度X"),
      field("jump_distancez", FieldKind::Float, &IWorldDataset::jump_distancez, "跳跃速度Z"),
      field("dash_height", FieldKind::Float, &IWorldDataset::dash_height, "冲跳速度Y"),
      field("dash_distance", FieldKind::Float, &IWorldDataset::dash_distance, "冲跳速度X"),
      field("dash_distancez", FieldKind::Float, &IWorldDataset::dash_distancez, "冲跳速度Z"),
      field("rowing_height", FieldKind::Float, &IWorldDataset::rowing_height, "受身速度Y"),
      field("rowing_distance", FieldKind::Float, &IWorldDataset::rowing_distance, "受身速度X"),
      field("whirlwind_vy_max", FieldKind::Float, &IWorldDataset::whirlwind_vy_max, "旋风最大速度Y"),
      field("whirlwind_acc_y", FieldKind::Float, &IWorldDataset::whirlwind_acc_y, "旋风加速度Y"),
      field("whirlwind_acc_x", FieldKind::Float, &IWorldDataset::whirlwind_acc_x, "旋风加速度X"),
      field("whirlwind_acc_z", FieldKind::Float, &IWorldDataset::whirlwind_acc_z, "旋风加速度Z"));
  return fs;
}

#endif // LFW_CORE_DEFINES_IWORLD_DATASET_HPP
