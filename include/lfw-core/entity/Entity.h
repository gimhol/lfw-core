#ifndef LFW_CORE_ENTITY_ENTITY_H
#define LFW_CORE_ENTITY_ENTITY_H

#include <cstdint>
#include <string>
#include <vector>

#include "lfw-core/core.hpp"
#include "lfw-core/defines/EntityType.hpp"
#include "lfw-core/defines/SpeedMode.hpp"
#include "lfw-core/defines/StateType.hpp"
#include "lfw-core/defines/TeamEnum.hpp"

LFW_NS_BEGIN

struct IOpointInfo;
struct IFrameInfo;
struct INextFrame;
struct IVector3;
class LFW;

/// Entity — 实体基类，对应 TS Entity
/// 渐进式转换，当前合并了 State_Base + Buff 系统所需接口
class Entity
{
public:
  virtual ~Entity() = default;

  // === 基础标识 ===
  virtual const std::string &id() const = 0;

  // === 状态系统 ===
  virtual double lifetime() const = 0;
  virtual double healing() const = 0;
  virtual void set_healing(double v) = 0;
  virtual StateType state() const = 0;

  // === Buff 系统：标量属性（默认实现，可覆写） ===
  virtual double hp() const { return 0; }
  virtual void set_hp(double) {}
  virtual double hp_r() const { return 0; }
  virtual void set_hp_r(double) {}
  virtual double toughness() const { return 0; }
  virtual void set_toughness(double) {}
  virtual TeamEnum team() const { return TeamEnum::Independent; }
  virtual void set_team(TeamEnum) {}

  double wait = 0;
  double fallinjury = 0;

  // === Buff 系统：速度 ===
  virtual double velocity_y() const { return 0; }
  virtual void set_velocity_y(double) {}
  virtual void handle_velocity_decay(double) {}

  // === Buff 系统：帧操作 ===
  virtual void enter_frame_by_id(const std::string &) {}

  // === 类型 ===
  virtual EntityType entity_type() const { return EntityType::Entity; }

  // === 游戏上下文 ===
  virtual LFW *lfw() const { return nullptr; }

  // === 帧几何 ===
  virtual const IFrameInfo &current_frame() const = 0;

  // === 状态系统方法 ===
  virtual void apply_opoints(const std::vector<IOpointInfo> &opoints) = 0;

  // === 帧查询 ===
  virtual const IFrameInfo *get_sudden_death_frame() { return nullptr; }
  virtual const IFrameInfo *get_caught_end_frame() { return nullptr; }
  virtual const IFrameInfo *get_auto_frame() { return nullptr; }
  virtual const IFrameInfo *find_frame_by_id(const std::string * /*id*/) { return nullptr; }
};

// ---- 辅助函数 ----

inline bool is_fighter(const Entity *e)
{
  return e && e->entity_type() == EntityType::Fighter;
}

inline double calc_v(double current, double value, SpeedMode, double, double)
{
  return current + value; // stub: TODO 完整实现
}

inline void apply_damage_summary(Entity *, double, Entity *, double)
{
  // stub: TODO 等 SummaryMgr 转换
}

LFW_NS_END

#endif
