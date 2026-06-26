#ifndef LFW_CORE_ENTITY_ENTITY_H
#define LFW_CORE_ENTITY_ENTITY_H

#include <algorithm>
#include <cstdint>
#include <map>
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
#include "lfw-core/entity/EnterFrameResult.h"
#include "lfw-core/entity/EntityCallbacks.h"
#include "lfw-core/entity/StatBarType.h"
#include "lfw-core/utils/math/Times.hpp"

LFW_NS_BEGIN

struct IOpointInfo;
struct IArmorInfo;
struct IBdyInfo;
struct IBounding;
struct IItrInfo;
struct IEntityData;
struct IVector3;
class LFW;
class World;

// ============================================================
// Entity — 实体基类，对应 TS Entity
// 渐进式转换：逐步添加成员和方法
// ============================================================
class Entity
{
public:
  static const char *TAG;

  // === 游戏上下文 ===
  virtual LFW *lfw() const { return _lfw; }
  World *world = nullptr;
  std::string id;
  int wait = 0;
  int variant = 0;

  // === 渲染 ===
  int render_effect_time() const { return _render_effect_time; }
  const std::string &outline_color() const { return _outline_color; }
  void set_outline_color(const std::string &v)
  {
    _outline_color = v;
    ++_render_effect_time;
  }
  double outline_alpha() const { return _outline_alpha; }
  void set_outline_alpha(double v)
  {
    _outline_alpha = v;
    ++_render_effect_time;
  }
  double outline_width() const { return _outline_width; }
  void set_outline_width(double v)
  {
    _outline_width = v;
    ++_render_effect_time;
  }
  std::optional<int> outline_enabled() const { return _outline_enabled; }
  void set_outline_enabled(std::optional<int> v)
  {
    _outline_enabled = v;
    ++_render_effect_time;
  }
  const std::string &mix_color() const { return _mix_color; }
  void set_mix_color(const std::string &v)
  {
    _mix_color = v;
    ++_render_effect_time;
  }
  double mix_strength() const { return _mix_strength; }
  void set_mix_strength(double v)
  {
    _mix_strength = v;
    ++_render_effect_time;
  }
  double greyscale() const { return _greyscale; }
  void set_greyscale(double v)
  {
    _greyscale = v;
    ++_render_effect_time;
  }

  // === 位置 / 速度 ===
  virtual const IVector3 &position() const = 0;
  virtual const IVector3 &prev_position() const = 0;
  virtual const IVector3 &velocity() const = 0;
  virtual double ground_y() const { return 0; }
  virtual double velocity_x() const = 0;
  virtual double velocity_y() const = 0;
  virtual double velocity_z() const = 0;
  virtual void set_velocity_x(double v) = 0;
  virtual void set_velocity_y(double v) = 0;
  virtual void set_velocity_z(double v) = 0;
  virtual void set_position_x(double v) = 0;
  virtual void set_position_y(double v) = 0;
  virtual void set_position_z(double v) = 0;
  virtual void handle_velocity_decay(double factor) = 0;

  // === 数据 ===
  virtual const IEntityData &data() const = 0;
  virtual EntityType type() const = 0;

  // === HP / MP ===
  double hp() const { return _hp; }
  void set_hp(double v)
  {
    v = std::max(0.0, v);
    double o = _hp;
    if (o == v)
      return;
    _hp = v;
    callbacks.signals.on_hp_changed.emit(this, v, o);
    if (o > 0 && v <= 0)
      callbacks.signals.on_dead.emit(this);
    if (v > _hp_r)
      _hp_r = v;
  }
  double hp_r() const { return _hp_r; }
  void set_hp_r(double v)
  {
    v = std::max(0.0, v);
    double o = _hp_r;
    if (o == v)
      return;
    callbacks.signals.on_hp_r_changed.emit(this, (_hp_r = v), o);
  }
  double hp_max() const { return _hp_max; }
  void set_hp_max(double v)
  {
    auto o = _hp_max;
    v = std::max(0.0, v);
    if (o == v)
      return;
    _hp_max = v;
    callbacks.signals.on_hp_max_changed.emit(this, v, o);
  }
  double mp() const { return _mp; }
  void set_mp(double v)
  {
    v = std::max(0.0, v);
    double o = _mp;
    if (o == v)
      return;
    _mp = v;
    callbacks.signals.on_mp_changed.emit(this, v, o);
  }
  double mp_max() const { return _mp_max; }
  void set_mp_max(double v)
  {
    auto o = _mp_max;
    v = std::max(0.0, v);
    if (o == v)
      return;
    _mp_max = v;
    callbacks.signals.on_mp_max_changed.emit(this, v, o);
  }

  // === 韧性 / 防御 / 坠落 ===
  double toughness() const { return _toughness; }
  void set_toughness(double v)
  {
    if (v < 0)
      v = 0;
    double o = _toughness;
    if (o == v)
      return;
    _toughness = v;
    if (v < o)
      _toughness_resting = _toughness_resting_max;
    callbacks.signals.on_toughness_changed.emit(this, v, o);
  }
  double toughness_max() const { return _toughness_max; }
  void set_toughness_max(double v)
  {
    auto o = _toughness_max;
    if (v < 0)
      v = 0;
    if (o == v)
      return;
    _toughness_max = v;
    callbacks.signals.on_toughness_max_changed.emit(this, v, o);
  }
  double fall_value() const { return _fall_value; }
  void set_fall_value(double v)
  {
    double o = _fall_value;
    if (o == v)
      return;
    _fall_value = v;
    if (v < o)
    {
      _resting = _resting_max;
      _toughness_resting = _toughness_resting_max;
    }
    callbacks.signals.on_fall_value_changed.emit(this, v, o);
  }
  double defend_value() const { return _defend_value; }
  void set_defend_value(double v)
  {
    double o = _defend_value;
    if (o == v)
      return;
    _defend_value = v;
    if (v < o)
    {
      _resting = _resting_max;
      _toughness_resting = _toughness_resting_max;
    }
    callbacks.signals.on_defend_value_changed.emit(this, v, o);
  }
  double healing() const { return _healing; }
  void set_healing(double v)
  {
    if (_hp_r == _hp)
      v = 0;
    double o = _healing;
    if (o == v)
      return;
    _healing = v;
    callbacks.signals.on_healing_changed.emit(this, v, o);
  }
  double fallinjury = 0;
  double throwinjury = 0;

  // === 队伍 ===
  const std::string &team() const { return _team; }
  void set_team(const std::string &v)
  {
    std::string o = _team;
    _team = v;
    try
    {
      variant = std::stoi(v);
    }
    catch (...)
    {
      variant = 0;
    }
    callbacks.signals.on_team_changed.emit(this, v, o);
    ++_render_effect_time;
  }

  // === 状态 ===
  double lifetime() const { return _lifetime; }
  void set_lifetime(double v) { _lifetime = v; }
  virtual StateType state() const = 0; // 依赖 current_frame()
  virtual bool is_ghosted() const { return false; }
  virtual bool is_mounted() const { return false; }

  // === 朝向 ===
  int facing() const { return _facing; }
  void set_facing(int v) { _facing = v; }

  // === 帧 ===
  virtual const IFrameInfo &current_frame() const = 0;
  virtual const IFrameInfo *get_sudden_death_frame() { return nullptr; }
  virtual const IFrameInfo *get_caught_end_frame() { return nullptr; }
  virtual const IFrameInfo *get_auto_frame() { return nullptr; }
  virtual const IFrameInfo *find_frame_by_id(const std::string * /*id*/) { return nullptr; }

  // === 帧操作 ===
  virtual void apply_opoints(const std::vector<IOpointInfo> &opoints) = 0;
  virtual void enter_frame_by_id(const std::string &frame_id) = 0;
  virtual EnterFrameResult enter_frame(const INextFrame &which, bool fallback = false) = 0;

  // === 抓取 ===
  virtual Entity *catching() const { return nullptr; }
  virtual Entity *catcher() const { return nullptr; }
  virtual Entity *bearer() const { return nullptr; }
  virtual Entity *holding() const { return nullptr; }
  virtual void set_bearer(Entity *) {}
  virtual void set_holding(Entity *) {}

  // === Buff ===
  std::map<std::string, class Buff *> buffs;

  // === 回调（Signal 系统替代 TS Callbacks） ===
  SignalGroup<EntityCallbacks> callbacks;

  // === 实体类型 ===
  virtual EntityType entity_type() const { return EntityType::Entity; }

  // === 杂项 getter/setter ===
  StatBarType stat_bar_type() const { return _stat_bar_type.value_or(key_role() ? StatBarType::Float : StatBarType::None); }
  void set_stat_bar_type(StatBarType v) { _stat_bar_type = v; }

  double resting() const { return _resting; }
  void set_resting(double v)
  {
    auto o = _resting;
    if (o == v)
      return;
    _resting = v;
    callbacks.signals.on_resting_changed.emit(this, v, o);
  }
  double resting_max() const { return _resting_max; }
  void set_resting_max(double v)
  {
    auto o = _resting_max;
    if (o == v)
      return;
    _resting_max = v;
    callbacks.signals.on_resting_max_changed.emit(this, v, o);
  }

  double toughness_resting() const { return _toughness_resting; }
  void set_toughness_resting(double v) { _toughness_resting = v; }
  double toughness_resting_max() const { return _toughness_resting_max; }
  void set_toughness_resting_max(double v) { _toughness_resting_max = v; }

  double catch_time_max() const { return _catch_time_max; }
  void set_catch_time_max(double v)
  {
    auto o = _catch_time_max;
    if (o == v)
      return;
    _catch_time_max = v;
    callbacks.signals.on_catch_time_max_changed.emit(this, v, o);
  }
  double fall_value_max() const { return _fall_value_max; }
  void set_fall_value_max(double v)
  {
    auto o = _fall_value_max;
    if (o == v)
      return;
    _fall_value_max = v;
    callbacks.signals.on_fall_value_max_changed.emit(this, v, o);
  }
  double defend_value_max() const { return _defend_value_max; }
  void set_defend_value_max(double v)
  {
    auto o = _defend_value_max;
    if (o == v)
      return;
    _defend_value_max = v;
    callbacks.signals.on_defend_value_max_changed.emit(this, v, o);
  }
  double defend_ratio() const { return _defend_ratio; }
  void set_defend_ratio(double v) { _defend_ratio = v; }

  int blinking() const { return _blinking_duration; }
  void set_blinking(int v) { _blinking_duration = std::max(0, v); }
  int invisible() const { return _invisible_duration; }
  void set_invisible(int v) { _invisible_duration = std::max(0, v); }
  int invulnerable() const { return _invulnerable_duration; }
  void set_invulnerable(int v) { _invulnerable_duration = std::max(0, v); }

  const std::string &name() const { return _name; }
  void set_name(const std::string &v) { _name = v; }

  double reserve() const { return _reserve; }
  void set_reserve(double v)
  {
    auto o = _reserve;
    if (o == v)
      return;
    _reserve = v;
    callbacks.signals.on_reserve_changed.emit(this, v, o);
  }

  int mounted() const { return _mounted; }
  void set_mounted(int v) { _mounted = v; }
  int ghosted() const { return _ghosted; }
  void set_ghosted(int v) { _ghosted = v; }

  double arest() const { return _arest; }
  void set_arest(double v) { _arest = v; }
  int strength() const { return data().base.strength.value_or(1); }
  int weight() const { return data().base.weight.value_or(1); }
  int base_type() const { return data().base.type.value_or(0); }
  double gravity() const { return data().base.gravity.value_or(0); }
  double itr_motionless() const { return data().base.itr_motionless.value_or(0); }

  bool key_role() const { return _key_role; }
  void set_key_role(bool v) { _key_role = v; }
  bool name_visible() const { return _name_visible; }
  void set_name_visible(bool v) { _name_visible = v; }
  bool wakeup_invuln() const { return _wakeup_invuln; }
  void set_wakeup_invuln(bool v) { _wakeup_invuln = v; }
  bool dead_gone() const { return _dead_gone; }
  void set_dead_gone(bool v) { _dead_gone = v; }

  bool ctrl_visible() const { return _ctrl_visible; }
  void set_ctrl_visible(bool v) { _ctrl_visible = v; }

  double spawn_time() const { return _spawn_time; }
  const std::vector<std::string> &emitters() const { return _emitters; }

  virtual ~Entity() = default;

protected:
  LFW *_lfw = nullptr;

  // 渲染
  int _render_effect_time = 0;
  std::string _outline_color;
  double _outline_alpha = 0.8;
  double _outline_width = 1;
  std::optional<int> _outline_enabled;
  std::string _mix_color;
  double _mix_strength = 0;
  double _greyscale = 0;

  // 杂项
  std::optional<StatBarType> _stat_bar_type;
  double _resting = 0;
  double _resting_max = 0;
  double _toughness = 0;
  double _toughness_max = 0;
  double _toughness_resting = 0;
  double _toughness_resting_max = 0;
  Times _toughness_r_tick;
  double _catch_time = 0;
  double _catch_time_max = 0;
  double _fall_value = 0;
  double _fall_value_max = 0;
  Times _fall_r_tick;
  double _fall_r_value = 0;
  double _defend_value = 0;
  double _defend_value_max = 0;
  Times _defend_r_tick;
  double _defend_r_value = 0;
  double _defend_ratio = 0;
  double _healing = 0;
  double _hp = 0, _hp_r = 0, _hp_max = 0;
  double _mp = 0, _mp_max = 0;
  std::string _team;
  double _lifetime = 0;
  int _facing = 1;

  int _blinking_duration = 0;
  int _invisible_duration = 0;
  int _invulnerable_duration = 0;

  std::string _name;

  double _reserve = 0;
  int _mounted = 0;
  int _ghosted = 0;
  double _arest = 0;

  bool _key_role = false;
  bool _name_visible = false;
  bool _wakeup_invuln = false;
  bool _dead_gone = false;
  bool _ctrl_visible = false;

  double _spawn_time = 0;
  std::vector<std::string> _emitters;
  Times _hp_r_tick;
  Times _mp_r_tick;
};

// ---- 辅助函数 ----

inline bool is_fighter(const Entity *e)
{
  return e && e->entity_type() == EntityType::Fighter;
}

inline bool is_weapon(const Entity *e)
{
  return e && e->entity_type() == EntityType::Weapon;
}

inline bool is_ball(const Entity *e)
{
  return e && e->entity_type() == EntityType::Ball;
}

/// 伤害统计 — 对应 TS summary_mgr.apply_damage
/// TODO: 等 SummaryMgr 转换后替换
inline void apply_damage_summary(Entity *, double, Entity *, double) {}

LFW_NS_END

#endif
