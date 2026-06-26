#include "lfw-core/entity/Entity.h"
#include "lfw-core/World.h"
#include <algorithm>
#include <cmath>
#include <lfw-core/utils/math/Math.hpp>
#include <lfw-core/utils/math/Times.hpp>

LFW_NS_BEGIN

// ============================================================
// Entity::Private — 所有数据成员
// ============================================================
struct Entity::Private
{
  LFW *_lfw = nullptr;
  World *_world = nullptr;
  std::string _id;
  int _wait = 0;
  int _variant = 0;
  int _render_effect_time = 0;
  std::string _outline_color;
  double _outline_alpha = 0.8, _outline_width = 1;
  std::optional<int> _outline_enabled;
  std::string _mix_color;
  double _mix_strength = 0, _greyscale = 0;

  IVector3 _position = Ditto::vec3();
  IVector3 _prev_position = Ditto::vec3();
  IVector3 _velocity = Ditto::vec3();
  IVector3 _temp_v = Ditto::vec3();
  double _ground_y = 0;
  double _prev_ground_y = 0;
  double _atom_time = 0;

  IEntityData _data{};
  IFrameInfo _frame{};
  IFrameInfo _prev_frame{};
  INextFrame _next_frame_by_id{};
  IFrameInfo *_landing_frame = nullptr;

  double _hp = 0, _hp_r = 0, _hp_max = 0;
  double _mp = 0, _mp_max = 0;
  double _toughness = 0, _toughness_max = 0;
  double _toughness_resting = 0, _toughness_resting_max = 0;
  double _fall_value = 0, _fall_value_max = 0;
  double _defend_value = 0, _defend_value_max = 0;
  double _defend_ratio = 0;
  double _healing = 0;
  double _fallinjury = 0;
  double _throwinjury = 0;
  std::map<std::string, Buff *> _buffs;
  std::string _team;
  double _lifetime = 0;
  int _facing = 1;

  std::optional<StatBarType> _stat_bar_type;
  double _resting = 0, _resting_max = 0;
  double _catch_time = 0, _catch_time_max = 0;
  Times _toughness_r_tick, _fall_r_tick, _defend_r_tick, _hp_r_tick, _mp_r_tick;
  Times _resting_tick;
  double _fall_r_value = 0, _defend_r_value = 0;

  int _blinking_duration = 0, _invisible_duration = 0, _invulnerable_duration = 0;
  std::string _name;
  double _reserve = 0;
  int _mounted = 0, _ghosted = 0;
  double _arest = 0;
  bool _key_role = false, _name_visible = false, _wakeup_invuln = false;
  bool _dead_gone = false, _ctrl_visible = false;
  std::optional<bool> _key_role_cache;
  double _spawn_time = 0;
  std::vector<std::string> _emitters;

  Entity *_catching = nullptr, *_catcher = nullptr;
  Entity *_bearer = nullptr, *_holding = nullptr;

  double aabb_min_x = 0, aabb_max_x = 0, aabb_min_z = 0, aabb_max_z = 0;
  int motionless = 0;
  int shaking = 0;
  std::optional<std::vector<std::string>> transforms;
};

const char *Entity::TAG = "Entity";

Entity::Entity() : _(std::make_unique<Private>()) {}
Entity::~Entity() = default;

// === 游戏上下文 ===
LFW *Entity::lfw() const { return _->_lfw; }
World *Entity::world() const { return _->_world; }
void Entity::set_world(World *w) { _->_world = w; }
const std::string &Entity::id() const { return _->_id; }
void Entity::set_id(const std::string &v) { _->_id = v; }
int Entity::wait() const { return _->_wait; }
void Entity::set_wait(int v) { _->_wait = v; }
int Entity::variant() const { return _->_variant; }
void Entity::set_variant(int v) { _->_variant = v; }

// === 渲染 ===
int Entity::render_effect_time() const { return _->_render_effect_time; }
const std::string &Entity::outline_color() const { return _->_outline_color; }
void Entity::set_outline_color(const std::string &v)
{
  _->_outline_color = v;
  ++_->_render_effect_time;
}
double Entity::outline_alpha() const { return _->_outline_alpha; }
void Entity::set_outline_alpha(double v)
{
  _->_outline_alpha = v;
  ++_->_render_effect_time;
}
double Entity::outline_width() const { return _->_outline_width; }
void Entity::set_outline_width(double v)
{
  _->_outline_width = v;
  ++_->_render_effect_time;
}
std::optional<int> Entity::outline_enabled() const { return _->_outline_enabled; }
void Entity::set_outline_enabled(std::optional<int> v)
{
  _->_outline_enabled = v;
  ++_->_render_effect_time;
}
const std::string &Entity::mix_color() const { return _->_mix_color; }
void Entity::set_mix_color(const std::string &v)
{
  _->_mix_color = v;
  ++_->_render_effect_time;
}
double Entity::mix_strength() const { return _->_mix_strength; }
void Entity::set_mix_strength(double v)
{
  _->_mix_strength = v;
  ++_->_render_effect_time;
}
double Entity::greyscale() const { return _->_greyscale; }
void Entity::set_greyscale(double v)
{
  _->_greyscale = v;
  ++_->_render_effect_time;
}

// === 位置 / 速度 ===
const IVector3 &Entity::position() const { return _->_position; }
const IVector3 &Entity::prev_position() const { return _->_prev_position; }
const IVector3 &Entity::velocity() const { return _->_velocity; }
double Entity::ground_y() const { return _->_ground_y; }
double Entity::prev_ground_y() const { return _->_prev_ground_y; }
double Entity::velocity_x() const { return _->_velocity.x; }
double Entity::velocity_y() const { return _->_velocity.y; }
double Entity::velocity_z() const { return _->_velocity.z; }
void Entity::set_velocity_x(double v) { _->_velocity.x = v; }
void Entity::set_velocity_y(double v) { _->_velocity.y = v; }
void Entity::set_velocity_z(double v) { _->_velocity.z = v; }
void Entity::set_velocity(double x, double y, double z)
{
  _->_velocity.x = x;
  _->_velocity.y = y;
  _->_velocity.z = z;
}
void Entity::set_position_x(double v) { _->_position.x = v; }
void Entity::set_position_y(double v) { _->_position.y = v; }
void Entity::set_position_z(double v) { _->_position.z = v; }
void Entity::set_position(double x, double y, double z)
{
  _->_position.x = x;
  _->_position.y = y;
  _->_position.z = z;
}
void Entity::handle_velocity_decay(double) { /* stub */ }

// === 数据 ===
const IEntityData &Entity::data() const { return _->_data; }
EntityType Entity::type() const { return _->_data.type; }
const std::vector<std::string> *Entity::group() const
{
  if (_->_data.base.group.has_value())
    return &_->_data.base.group.value();
  return nullptr;
}
const std::vector<IItrInfo> *Entity::itr() const
{
  if (_->_frame.itr.has_value())
    return &_->_frame.itr.value();
  return nullptr;
}
const std::vector<IBdyInfo> *Entity::bdy() const
{
  if (_->_frame.bdy.has_value())
    return &_->_frame.bdy.value();
  return nullptr;
}

double Entity::dataset(const std::string &name) const
{
  // TODO: frame.data check pending IFrameInfo.data field
  // Check data.base for matching field
  // Simplified: return 0 until IWorldDataset is fully integrated
  if (world)
  {
    // TODO: world->dataset[name] lookup
  }
  return 0;
}

Entity *Entity::get_emitter(int idx) const
{
  if (idx < 0 || static_cast<size_t>(idx) >= _->_emitters.size())
    return nullptr;
  if (!_->_world)
    return nullptr;
  auto it = _->_world->entity_map.find(_->_emitters[idx]);
  return it != _->_world->entity_map.end() ? it->second : nullptr;
}
Entity *Entity::src_emitter() const { return get_emitter(0); }
Entity *Entity::pre_emitter() const
{
  if (_->_emitters.empty())
    return nullptr;
  return get_emitter(static_cast<int>(_->_emitters.size()) - 1);
}

// === HP / MP ===
double Entity::hp() const { return _->_hp; }
void Entity::set_hp(double v)
{
  v = math::round_float(std::max(0.0, v));
  double o = _->_hp;
  if (o == v)
    return;
  _->_hp = v;
  callbacks.signals.on_hp_changed.emit(this, v, o);
  if (o > 0 && v <= 0)
    callbacks.signals.on_dead.emit(this);
  if (v > _->_hp_r)
    _->_hp_r = v;
}
double Entity::hp_r() const { return _->_hp_r; }
void Entity::set_hp_r(double v)
{
  v = math::round_float(std::max(0.0, v));
  double o = _->_hp_r;
  if (o == v)
    return;
  callbacks.signals.on_hp_r_changed.emit(this, (_->_hp_r = v), o);
}
double Entity::hp_max() const { return _->_hp_max; }
void Entity::set_hp_max(double v)
{
  v = math::round_float(std::max(0.0, v));
  auto o = _->_hp_max;
  if (o == v)
    return;
  _->_hp_max = v;
  callbacks.signals.on_hp_max_changed.emit(this, v, o);
}
double Entity::mp() const { return _->_mp; }
void Entity::set_mp(double v)
{
  v = math::round_float(std::max(0.0, v));
  double o = _->_mp;
  if (o == v)
    return;
  _->_mp = v;
  callbacks.signals.on_mp_changed.emit(this, v, o);
}
double Entity::mp_max() const { return _->_mp_max; }
void Entity::set_mp_max(double v)
{
  v = math::round_float(std::max(0.0, v));
  auto o = _->_mp_max;
  if (o == v)
    return;
  _->_mp_max = v;
  callbacks.signals.on_mp_max_changed.emit(this, v, o);
}

// === 韧性 / 防御 / 坠落 ===
double Entity::toughness() const { return _->_toughness; }
void Entity::set_toughness(double v)
{
  v = math::round_float(v);
  if (v < 0)
    v = 0;
  double o = _->_toughness;
  if (o == v)
    return;
  _->_toughness = v;
  if (v < o)
    _->_toughness_resting = _->_toughness_resting_max;
  callbacks.signals.on_toughness_changed.emit(this, v, o);
}
double Entity::toughness_max() const { return _->_toughness_max; }
void Entity::set_toughness_max(double v)
{
  v = math::round_float(v);
  if (v < 0)
    v = 0;
  auto o = _->_toughness_max;
  if (o == v)
    return;
  _->_toughness_max = v;
  callbacks.signals.on_toughness_max_changed.emit(this, v, o);
}
double Entity::fall_value() const { return _->_fall_value; }
void Entity::set_fall_value(double v)
{
  v = math::round_float(v);
  double o = _->_fall_value;
  if (o == v)
    return;
  _->_fall_value = v;
  if (v < o)
  {
    _->_resting = _->_resting_max;
    _->_toughness_resting = _->_toughness_resting_max;
  }
  callbacks.signals.on_fall_value_changed.emit(this, v, o);
}
double Entity::defend_value() const { return _->_defend_value; }
void Entity::set_defend_value(double v)
{
  v = math::round_float(v);
  double o = _->_defend_value;
  if (o == v)
    return;
  _->_defend_value = v;
  if (v < o)
  {
    _->_resting = _->_resting_max;
    _->_toughness_resting = _->_toughness_resting_max;
  }
  callbacks.signals.on_defend_value_changed.emit(this, v, o);
}
double Entity::healing() const { return _->_healing; }
void Entity::set_healing(double v)
{
  v = math::round_float(v);
  if (_->_hp_r == _->_hp)
    v = 0;
  double o = _->_healing;
  if (o == v)
    return;
  _->_healing = v;
  callbacks.signals.on_healing_changed.emit(this, v, o);
}
double Entity::fallinjury() const { return _->_fallinjury; }
void Entity::set_fallinjury(double v) { _->_fallinjury = v; }
double Entity::throwinjury() const { return _->_throwinjury; }
void Entity::set_throwinjury(double v) { _->_throwinjury = v; }

// === 队伍 ===
const std::string &Entity::team() const { return _->_team; }
void Entity::set_team(const std::string &v)
{
  std::string o = _->_team;
  _->_team = v;
  try
  {
    _->_variant = std::stoi(v);
  }
  catch (...)
  {
    _->_variant = 0;
  }
  callbacks.signals.on_team_changed.emit(this, v, o);
  ++_->_render_effect_time;
}

// === 状态 / 朝向 ===
StateType Entity::state() const { return StateType::Standing; }
double Entity::lifetime() const { return _->_lifetime; }
void Entity::set_lifetime(double v) { _->_lifetime = v; }
bool Entity::is_ghosted() const { return _->_ghosted > 0; }
bool Entity::is_mounted() const { return _->_mounted > 0; }
int Entity::facing() const { return _->_facing; }
void Entity::set_facing(int v) { _->_facing = v; }

// === 帧 ===
const IFrameInfo &Entity::current_frame() const { return _->_frame; }
const IFrameInfo &Entity::prev_frame() const { return _->_prev_frame; }
double Entity::dvx() const
{
  auto v = _->_frame.dvx.value_or(0);
  return v * dataset("fvx_f");
}
double Entity::dvy() const
{
  auto v = _->_frame.dvy.value_or(0);
  return v * dataset("fvy_f");
}
double Entity::dvz() const
{
  auto v = _->_frame.dvz.value_or(0);
  return v * dataset("fvz_f");
}
const IFrameInfo *Entity::get_sudden_death_frame() { return nullptr; }
const IFrameInfo *Entity::get_caught_end_frame() { return nullptr; }
const IFrameInfo *Entity::get_auto_frame() { return nullptr; }
const IFrameInfo *Entity::find_frame_by_id(const std::string *) { return nullptr; }
void Entity::apply_opoints(const std::vector<IOpointInfo> &) {}
void Entity::enter_frame_by_id(const std::string &) {}
EnterFrameResult Entity::enter_frame(const INextFrame &, bool) { return EnterFrameResult::NotFound; }
void Entity::set_frame(const INextFrame &) { /* TODO: 完整实现 pending State_Base */ }
void Entity::set_state(StateType) { /* TODO: 完整实现 pending _states */ }

// === 物理 ===
double Entity::itr_fall(const IItrInfo *itr) const
{
  if (!itr)
    return dataset("itr_fall");
  return itr->fall.value_or(dataset("itr_fall"));
}
void Entity::handle_gravity()
{
  if (bearer() || catcher())
    return;
  double g = gravity() * _->_atom_time;
  set_velocity_y(velocity_y() + g);
}
void Entity::handle_ground_velocity_decay()
{
  /* TODO: 完整实现 pending landing_frame + dataset */
  handle_velocity_decay(0);
}

// === 阵营判定 ===
bool Entity::is_ally(const Entity *other) const
{
  if (!other)
    return false;
  return team() == other->team();
}

// === 抓取 ===
Entity *Entity::catching() const { return _->_catching; }
Entity *Entity::catcher() const { return _->_catcher; }
Entity *Entity::bearer() const { return _->_bearer; }
Entity *Entity::holding() const { return _->_holding; }
void Entity::set_bearer(Entity *e)
{
  auto o = _->_bearer;
  if (o == e)
    return;
  _->_bearer = e;
  callbacks.signals.on_holder_changed.emit(this, e, o);
}
void Entity::set_holding(Entity *e)
{
  auto o = _->_holding;
  if (o == e)
    return;
  _->_holding = e;
  callbacks.signals.on_holding_changed.emit(this, e, o);
}

// === Buff ===
const std::map<std::string, Buff *> &Entity::buffs() const { return _->_buffs; }
std::map<std::string, Buff *> &Entity::buffs() { return _->_buffs; }
void Entity::clear_buffs() { _->_buffs.clear(); }

// === 实体类型 ===
EntityType Entity::entity_type() const { return EntityType::Entity; }

// === 杂项 ===
StatBarType Entity::stat_bar_type() const { return _->_stat_bar_type.value_or(key_role() ? StatBarType::Float : StatBarType::None); }
void Entity::set_stat_bar_type(StatBarType v) { _->_stat_bar_type = v; }
double Entity::resting() const { return _->_resting; }
void Entity::set_resting(double v)
{
  v = math::round_float(v);
  auto o = _->_resting;
  if (o == v)
    return;
  _->_resting = v;
  callbacks.signals.on_resting_changed.emit(this, v, o);
}
double Entity::resting_max() const { return _->_resting_max; }
void Entity::set_resting_max(double v)
{
  v = math::round_float(v);
  auto o = _->_resting_max;
  if (o == v)
    return;
  _->_resting_max = v;
  callbacks.signals.on_resting_max_changed.emit(this, v, o);
}
double Entity::toughness_resting() const { return _->_toughness_resting; }
void Entity::set_toughness_resting(double v)
{
  v = math::round_float(v);
  _->_toughness_resting = v;
}
double Entity::toughness_resting_max() const { return _->_toughness_resting_max; }
void Entity::set_toughness_resting_max(double v)
{
  v = math::round_float(v);
  _->_toughness_resting_max = v;
}
double Entity::catch_time_max() const { return _->_catch_time_max; }
void Entity::set_catch_time_max(double v)
{
  v = math::round_float(v);
  auto o = _->_catch_time_max;
  if (o == v)
    return;
  _->_catch_time_max = v;
  callbacks.signals.on_catch_time_max_changed.emit(this, v, o);
}
double Entity::fall_value_max() const { return _->_fall_value_max; }
void Entity::set_fall_value_max(double v)
{
  v = math::round_float(v);
  auto o = _->_fall_value_max;
  if (o == v)
    return;
  _->_fall_value_max = v;
  callbacks.signals.on_fall_value_max_changed.emit(this, v, o);
}
double Entity::defend_value_max() const { return _->_defend_value_max; }
void Entity::set_defend_value_max(double v)
{
  v = math::round_float(v);
  auto o = _->_defend_value_max;
  if (o == v)
    return;
  _->_defend_value_max = v;
  callbacks.signals.on_defend_value_max_changed.emit(this, v, o);
}
double Entity::defend_ratio() const { return _->_defend_ratio; }
void Entity::set_defend_ratio(double v)
{
  v = math::round_float(v);
  _->_defend_ratio = v;
}
int Entity::blinking() const { return _->_blinking_duration; }
void Entity::set_blinking(int v) { _->_blinking_duration = static_cast<int>(math::round_float(std::max(0.0, static_cast<double>(v)))); }
int Entity::invisible() const { return _->_invisible_duration; }
void Entity::set_invisible(int v) { _->_invisible_duration = std::max(0, v); }
int Entity::invulnerable() const { return _->_invulnerable_duration; }
void Entity::set_invulnerable(int v) { _->_invulnerable_duration = std::max(0, v); }
const std::string &Entity::name() const { return _->_name; }
void Entity::set_name(const std::string &v)
{
  auto o = _->_name;
  _->_name = v;
  callbacks.signals.on_name_changed.emit(this, v, o);
}
double Entity::reserve() const { return _->_reserve; }
void Entity::set_reserve(double v)
{
  v = math::round_float(v);
  auto o = _->_reserve;
  if (o == v)
    return;
  _->_reserve = v;
  callbacks.signals.on_reserve_changed.emit(this, v, o);
}
int Entity::mounted() const { return _->_mounted; }
void Entity::set_mounted(int v) { _->_mounted = v; }
int Entity::ghosted() const { return _->_ghosted; }
void Entity::set_ghosted(int v) { _->_ghosted = v; }
double Entity::arest() const { return _->_arest; }
void Entity::set_arest(double v) { _->_arest = math::round_float(v); }
int Entity::strength() const { return _->_data.base.strength.value_or(1); }
int Entity::weight() const { return _->_data.base.weight.value_or(1); }
int Entity::base_type() const { return _->_data.base.type.value_or(0); }
double Entity::gravity() const { return _->_data.base.gravity.value_or(0); }
double Entity::itr_motionless() const { return _->_data.base.itr_motionless.value_or(0); }
bool Entity::key_role() const
{
  if (_->_key_role_cache.has_value())
    return _->_key_role_cache.value();
  // TODO: check ctrl.player → true once BaseController is converted
  const auto &group = _->_data.base.group;
  if (!group.has_value() || group->empty())
  {
    _->_key_role_cache = false;
    return false;
  }
  for (const auto &g : *group)
  {
    if (g == "Regular" || g == "Boss")
    {
      _->_key_role_cache = true;
      return true;
    }
  }
  _->_key_role_cache = false;
  return false;
}
void Entity::set_key_role(bool v)
{
  _->_key_role = v;
  _->_key_role_cache = v;
}
bool Entity::name_visible() const { return _->_name_visible ? true : key_role(); }
void Entity::set_name_visible(bool v) { _->_name_visible = v; }
bool Entity::wakeup_invuln() const { return _->_wakeup_invuln ? true : key_role(); }
void Entity::set_wakeup_invuln(bool v) { _->_wakeup_invuln = v; }
bool Entity::dead_gone() const
{
  if (_->_dead_gone)
    return true;
  return !key_role();
}
void Entity::set_dead_gone(bool v) { _->_dead_gone = v; }
bool Entity::ctrl_visible() const { return _->_ctrl_visible; }
void Entity::set_ctrl_visible(bool v) { _->_ctrl_visible = v; }
double Entity::spawn_time() const { return _->_spawn_time; }
const std::vector<std::string> &Entity::emitters() const { return _->_emitters; }

LFW_NS_END
