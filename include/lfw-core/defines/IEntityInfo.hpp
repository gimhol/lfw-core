#ifndef LFW_CORE_DEFINES_IENTITY_INFO_HPP
#define LFW_CORE_DEFINES_IENTITY_INFO_HPP

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#include <optional>
#include <string>
#include <vector>

/// IEntityInfo — 实体配置信息
/// 对应 TS IEntityInfo extends Partial<IWorldDataset>
/// TODO: 完整 IWorldDataset 97 字段待补充
struct IEntityInfo
{
  std::optional<std::string> id;
  std::string name; // TS 唯一必填字段
  std::optional<std::string> oid;
  std::optional<std::string> head;  // 头像
  std::optional<std::string> small; // 缩略图
  std::optional<int> type;          // EntityEnum
  std::optional<int> team;
  std::optional<double> hp;
  std::optional<double> mp;

  // === 数值属性 ===
  std::optional<double> x, y, z;
  std::optional<int> facing;
  std::optional<double> strength; // 角色力气
  std::optional<double> weight;   // 武器重量
  std::optional<double> ce;       // 强度

  // === 属性 ===
  std::optional<double> hp_max;
  std::optional<double> mp_max;
  std::optional<double> resting_max;
  std::optional<double> gravity;
  std::optional<double> gravity_d;
  std::optional<double> defend_ratio;
  std::optional<double> fall_value_max;
  std::optional<double> defend_value_max;
  std::optional<double> catch_time_max;

  // === 数据集数值 ===
  std::optional<double> itr_motionless;
  std::optional<double> ball_itr_motionless;
  std::optional<double> itr_fall;
  std::optional<double> itr_arest;
  std::optional<double> bounce_x, bounce_y, bounce_z;
  std::optional<double> bounce_min_x, bounce_min_y, bounce_min_z;

  // === 数组 ===
  std::optional<std::string> state;
  std::optional<std::vector<std::string>> weapons;
  std::optional<std::vector<std::string>> group;
  std::optional<std::vector<std::string>> hit_sounds;
  std::optional<std::vector<std::string>> dead_sounds;
  std::optional<std::vector<std::string>> drop_sounds;

  // === 其他 ===
  std::optional<bool> is_bot;
  std::optional<std::string> bot_id;
  std::optional<double> drop_hurt;
  std::optional<double> begin_blink_time;
  std::optional<double> lying_blink_time;
  std::optional<double> gone_blink_time;
};


LFW_NS_END

#endif
