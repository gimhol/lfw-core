#ifndef LFW_CORE_DEFINES_IBOT_DATA_SET_HPP
#define LFW_CORE_DEFINES_IBOT_DATA_SET_HPP

#include <optional>

#include "lfw-core/base/Fields.hpp"

/// IBotDataSet — Bot 数据集（AI 参数配置，默认值来自 BotDataSet.Default）
struct IBotDataSet
{
  // 走攻
  std::optional<double> w_atk_x = 50;
  std::optional<double> w_atk_b_x = 40;
  std::optional<double> w_atk_m_x = -1;
  std::optional<double> w_atk_r_x = -1;
  std::optional<double> w_atk_min_z = -15;
  std::optional<double> w_atk_max_z = 15;

  // 跑攻
  std::optional<double> r_atk_desire = 10000;
  std::optional<double> r_atk_x = 100;
  std::optional<double> r_atk_min_z = -15;
  std::optional<double> r_atk_max_z = 15;

  // 冲跳攻
  std::optional<double> d_atk_min_x = 0;
  std::optional<double> d_atk_max_x = 100;
  std::optional<double> d_atk_min_z = -60;
  std::optional<double> d_atk_max_z = 60;

  // 跳攻
  std::optional<double> j_atk_x = 80;
  std::optional<double> j_atk_min_z = -60;
  std::optional<double> j_atk_max_z = 60;
  std::optional<double> j_atk_min_y = -260;
  std::optional<double> j_atk_max_y = 260;
  std::optional<double> j_atk_desire = 10000;

  // 跳跃 / 冲刺
  std::optional<double> jump_desire = 50;
  std::optional<double> dash_desire = 100;

  // 跑步
  std::optional<double> r_desire_min = 0;
  std::optional<double> r_desire_max = 2000;
  std::optional<double> r_x_min = 100;
  std::optional<double> r_x_max = 1200;
  std::optional<double> r_stop_desire = 10;

  // 防御
  std::optional<double> defend_desire_base = 2000;
  std::optional<double> defend_desire_step = 2000;

  // 闪避
  std::optional<double> avoid_in_x = 180;
  std::optional<double> avoid_in_z = 100;
  std::optional<double> avoid_out_x = 200;
  std::optional<double> avoid_out_z = 200;

  // 武器拾取
  std::optional<double> pick_weapon_f_x = 25;
  std::optional<double> pick_weapon_b_x = -25;
  std::optional<double> pick_weapon_z = 25;
};

inline const auto &bot_data_set_fields()
{
  static const auto fs = fields<IBotDataSet>(
      field("w_atk_x", FieldKind::Float, &IBotDataSet::w_atk_x, "走攻X"),
      field("w_atk_b_x", FieldKind::Float, &IBotDataSet::w_atk_b_x, "走攻背X"),
      field("w_atk_m_x", FieldKind::Float, &IBotDataSet::w_atk_m_x, "走攻盲区X"),
      field("w_atk_r_x", FieldKind::Float, &IBotDataSet::w_atk_r_x, "走攻反向X"),
      field("w_atk_min_z", FieldKind::Float, &IBotDataSet::w_atk_min_z, "走攻最小Z"),
      field("w_atk_max_z", FieldKind::Float, &IBotDataSet::w_atk_max_z, "走攻最大Z"),
      field("r_atk_desire", FieldKind::Float, &IBotDataSet::r_atk_desire, "跑攻欲望"),
      field("r_atk_x", FieldKind::Float, &IBotDataSet::r_atk_x, "跑攻X"),
      field("r_atk_min_z", FieldKind::Float, &IBotDataSet::r_atk_min_z, "跑攻最小Z"),
      field("r_atk_max_z", FieldKind::Float, &IBotDataSet::r_atk_max_z, "跑攻最大Z"),
      field("d_atk_min_x", FieldKind::Float, &IBotDataSet::d_atk_min_x, "冲跳攻最小X"),
      field("d_atk_max_x", FieldKind::Float, &IBotDataSet::d_atk_max_x, "冲跳攻最大X"),
      field("d_atk_min_z", FieldKind::Float, &IBotDataSet::d_atk_min_z, "冲跳攻最小Z"),
      field("d_atk_max_z", FieldKind::Float, &IBotDataSet::d_atk_max_z, "冲跳攻最大Z"),
      field("j_atk_x", FieldKind::Float, &IBotDataSet::j_atk_x, "跳攻X"),
      field("j_atk_min_z", FieldKind::Float, &IBotDataSet::j_atk_min_z, "跳攻最小Z"),
      field("j_atk_max_z", FieldKind::Float, &IBotDataSet::j_atk_max_z, "跳攻最大Z"),
      field("j_atk_min_y", FieldKind::Float, &IBotDataSet::j_atk_min_y, "跳攻最小Y"),
      field("j_atk_max_y", FieldKind::Float, &IBotDataSet::j_atk_max_y, "跳攻最大Y"),
      field("j_atk_desire", FieldKind::Float, &IBotDataSet::j_atk_desire, "跳攻欲望"),
      field("jump_desire", FieldKind::Float, &IBotDataSet::jump_desire, "跳跃欲望"),
      field("dash_desire", FieldKind::Float, &IBotDataSet::dash_desire, "冲刺欲望"),
      field("r_desire_min", FieldKind::Float, &IBotDataSet::r_desire_min, "跑步最小欲望"),
      field("r_desire_max", FieldKind::Float, &IBotDataSet::r_desire_max, "跑步最大欲望"),
      field("r_x_min", FieldKind::Float, &IBotDataSet::r_x_min, "起跑最小X"),
      field("r_x_max", FieldKind::Float, &IBotDataSet::r_x_max, "起跑最大X"),
      field("r_stop_desire", FieldKind::Float, &IBotDataSet::r_stop_desire, "停止跑步欲望"),
      field("defend_desire_base", FieldKind::Float, &IBotDataSet::defend_desire_base, "防御基础欲望"),
      field("defend_desire_step", FieldKind::Float, &IBotDataSet::defend_desire_step, "防御步进欲望"),
      field("avoid_in_x", FieldKind::Float, &IBotDataSet::avoid_in_x, "闪避近X"),
      field("avoid_in_z", FieldKind::Float, &IBotDataSet::avoid_in_z, "闪避近Z"),
      field("avoid_out_x", FieldKind::Float, &IBotDataSet::avoid_out_x, "闪避远X"),
      field("avoid_out_z", FieldKind::Float, &IBotDataSet::avoid_out_z, "闪避远Z"),
      field("pick_weapon_f_x", FieldKind::Float, &IBotDataSet::pick_weapon_f_x, "拾武前X"),
      field("pick_weapon_b_x", FieldKind::Float, &IBotDataSet::pick_weapon_b_x, "拾武后X"),
      field("pick_weapon_z", FieldKind::Float, &IBotDataSet::pick_weapon_z, "拾武Z"));
  return fs;
}

#endif
