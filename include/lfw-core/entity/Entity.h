#ifndef LFW_CORE_ENTITY_ENTITY_H
#define LFW_CORE_ENTITY_ENTITY_H

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "lfw-core/base/Signal.h"
#include "lfw-core/core.hpp"
#include "lfw-core/defines/EntityGroup.hpp"
#include "lfw-core/defines/EntityType.hpp"
#include "lfw-core/defines/IEntityData.hpp"
#include "lfw-core/defines/IFrameInfo.hpp"
#include "lfw-core/defines/INextFrame.hpp"
#include "lfw-core/defines/StateType.hpp"
#include "lfw-core/ditto/Ditto.h"
#include "lfw-core/entity/EnterFrameResult.h"
#include "lfw-core/entity/EntityCallbacks.h"
#include "lfw-core/entity/StatBarType.h"

LFW_NS_BEGIN

struct IOpointInfo;
class LFW;
class World;

class Entity
{
public:
  static const char *TAG;

  // === 构造/析构 ===
  Entity();
  ~Entity();

  // === 游戏上下文 ===
  LFW *lfw() const;
  World *world = nullptr;
  std::string id;
  int wait = 0;
  int variant = 0;

  // === 渲染 ===
  int render_effect_time() const;
  const std::string &outline_color() const;
  void set_outline_color(const std::string &v);
  double outline_alpha() const;
  void set_outline_alpha(double v);
  double outline_width() const;
  void set_outline_width(double v);
  std::optional<int> outline_enabled() const;
  void set_outline_enabled(std::optional<int> v);
  const std::string &mix_color() const;
  void set_mix_color(const std::string &v);
  double mix_strength() const;
  void set_mix_strength(double v);
  double greyscale() const;
  void set_greyscale(double v);

  // === 位置 / 速度 ===
  const IVector3 &position() const;
  const IVector3 &prev_position() const;
  const IVector3 &velocity() const;
  double ground_y() const;
  double prev_ground_y() const;
  double velocity_x() const;
  double velocity_y() const;
  double velocity_z() const;
  void set_velocity_x(double v);
  void set_velocity_y(double v);
  void set_velocity_z(double v);
  void set_velocity(double x, double y, double z);
  void set_position_x(double v);
  void set_position_y(double v);
  void set_position_z(double v);
  void set_position(double x, double y, double z);
  void handle_velocity_decay(double factor);

  // === 数据 ===
  const IEntityData &data() const;
  EntityType type() const;
  const std::vector<std::string> *group() const;
  const std::vector<struct IItrInfo> *itr() const;
  const std::vector<struct IBdyInfo> *bdy() const;

  /// 属性查找链: frame.data → data.base → world.dataset → 0
  double dataset(const std::string &name) const;

  // === HP / MP ===
  double hp() const;
  void set_hp(double v);
  double hp_r() const;
  void set_hp_r(double v);
  double hp_max() const;
  void set_hp_max(double v);
  double mp() const;
  void set_mp(double v);
  double mp_max() const;
  void set_mp_max(double v);

  // === 韧性 / 防御 / 坠落 ===
  double toughness() const;
  void set_toughness(double v);
  double toughness_max() const;
  void set_toughness_max(double v);
  double fall_value() const;
  void set_fall_value(double v);
  double defend_value() const;
  void set_defend_value(double v);
  double healing() const;
  void set_healing(double v);
  double fallinjury = 0;
  double throwinjury = 0;

  // === 队伍 ===
  const std::string &team() const;
  void set_team(const std::string &v);

  // === 状态 ===
  StateType state() const;
  double lifetime() const;
  void set_lifetime(double v);
  bool is_ghosted() const;
  bool is_mounted() const;

  // === 朝向 ===
  int facing() const;
  void set_facing(int v);

  // === 帧 ===
  const IFrameInfo &current_frame() const;
  const IFrameInfo &prev_frame() const;
  double dvx() const;
  double dvy() const;
  double dvz() const;
  const IFrameInfo *get_sudden_death_frame();
  const IFrameInfo *get_caught_end_frame();
  const IFrameInfo *get_auto_frame();
  const IFrameInfo *find_frame_by_id(const std::string *id);

  // === 帧操作 ===
  void apply_opoints(const std::vector<IOpointInfo> &opoints);
  void enter_frame_by_id(const std::string &frame_id);
  EnterFrameResult enter_frame(const INextFrame &which, bool fallback = false);
  void set_frame(const INextFrame &nf);
  void set_state(StateType s);

  // === 物理 ===
  double itr_fall(const struct IItrInfo *itr) const;
  void handle_gravity();
  void handle_ground_velocity_decay();

  // === 阵营判定 ===
  bool is_ally(const Entity *other) const;

  // === 抓取 ===
  Entity *catching() const;
  Entity *catcher() const;
  Entity *bearer() const;
  Entity *holding() const;
  void set_bearer(Entity *e);
  void set_holding(Entity *e);

  // === Buff ===
  std::map<std::string, class Buff *> buffs;

  // === 回调 ===
  SignalGroup<EntityCallbacks> callbacks;

  // === 实体类型 ===
  EntityType entity_type() const;

  // === 杂项 ===
  StatBarType stat_bar_type() const;
  void set_stat_bar_type(StatBarType v);
  double resting() const;
  void set_resting(double v);
  double resting_max() const;
  void set_resting_max(double v);
  double toughness_resting() const;
  void set_toughness_resting(double v);
  double toughness_resting_max() const;
  void set_toughness_resting_max(double v);
  double catch_time_max() const;
  void set_catch_time_max(double v);
  double fall_value_max() const;
  void set_fall_value_max(double v);
  double defend_value_max() const;
  void set_defend_value_max(double v);
  double defend_ratio() const;
  void set_defend_ratio(double v);
  int blinking() const;
  void set_blinking(int v);
  int invisible() const;
  void set_invisible(int v);
  int invulnerable() const;
  void set_invulnerable(int v);
  const std::string &name() const;
  void set_name(const std::string &v);
  double reserve() const;
  void set_reserve(double v);
  int mounted() const;
  void set_mounted(int v);
  int ghosted() const;
  void set_ghosted(int v);
  double arest() const;
  void set_arest(double v);
  int strength() const;
  int weight() const;
  int base_type() const;
  double gravity() const;
  double itr_motionless() const;
  bool key_role() const;
  void set_key_role(bool v);
  bool name_visible() const;
  void set_name_visible(bool v);
  bool wakeup_invuln() const;
  void set_wakeup_invuln(bool v);
  bool dead_gone() const;
  void set_dead_gone(bool v);
  bool ctrl_visible() const;
  void set_ctrl_visible(bool v);
  double spawn_time() const;
  const std::vector<std::string> &emitters() const;
  Entity *get_emitter(int idx) const;
  Entity *src_emitter() const;
  Entity *pre_emitter() const;

private:
  struct Private;
  std::unique_ptr<Private> _;
};

inline bool is_fighter(const Entity *e) { return e && e->entity_type() == EntityType::Fighter; }
inline bool is_weapon(const Entity *e) { return e && e->entity_type() == EntityType::Weapon; }
inline bool is_ball(const Entity *e) { return e && e->entity_type() == EntityType::Ball; }
inline void apply_damage_summary(Entity *, double, Entity *, double) {}

LFW_NS_END

#endif
