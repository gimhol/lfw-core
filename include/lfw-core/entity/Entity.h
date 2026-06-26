#ifndef LFW_CORE_ENTITY_ENTITY_H
#define LFW_CORE_ENTITY_ENTITY_H

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include "lfw-core/base/Signal.h"
#include "lfw-core/core.hpp"
#include "lfw-core/defines/EntityType.hpp"
#include "lfw-core/defines/IFrameInfo.hpp"
#include "lfw-core/defines/INextFrame.hpp"
#include "lfw-core/defines/StateType.hpp"
#include "lfw-core/defines/TeamEnum.hpp"
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
  virtual double hp() const = 0;
  virtual void set_hp(double v) = 0;
  virtual double hp_r() const = 0;
  virtual void set_hp_r(double v) = 0;
  virtual double hp_max() const = 0;
  virtual void set_hp_max(double v) = 0;
  virtual double mp() const = 0;
  virtual void set_mp(double v) = 0;
  virtual double mp_max() const = 0;
  virtual void set_mp_max(double v) = 0;

  // === 韧性 / 防御 / 坠落 ===
  virtual double toughness() const = 0;
  virtual void set_toughness(double v) = 0;
  virtual double toughness_max() const = 0;
  virtual void set_toughness_max(double v) = 0;
  virtual double fall_value() const = 0;
  virtual void set_fall_value(double v) = 0;
  virtual double defend_value() const = 0;
  virtual void set_defend_value(double v) = 0;
  virtual double healing() const { return 0; }
  virtual void set_healing(double) {}
  double fallinjury = 0;
  double throwinjury = 0;

  // === 队伍 ===
  virtual TeamEnum team() const = 0;
  virtual void set_team(TeamEnum v) = 0;

  // === 状态 ===
  virtual StateType state() const = 0;
  virtual double lifetime() const = 0;
  virtual bool is_ghosted() const { return false; }
  virtual bool is_mounted() const { return false; }

  // === 朝向 ===
  virtual int facing() const = 0;

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

  virtual ~Entity() = default;

protected:
  LFW *_lfw = nullptr;

  int _render_effect_time = 0;
  std::string _outline_color;
  double _outline_alpha = 0.8;
  double _outline_width = 1;
  std::optional<int> _outline_enabled;
  std::string _mix_color;
  double _mix_strength = 0;
  double _greyscale = 0;
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
