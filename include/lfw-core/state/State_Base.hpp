#ifndef LFW_CORE_STATE_STATE_BASE_HPP
#define LFW_CORE_STATE_STATE_BASE_HPP

#include <cstdint>
#include <string>

#include "lfw-core/core.hpp"
#include "lfw-core/defines/StateType.hpp"
#include "lfw-core/entity/Entity.hpp"

LFW_NS_BEGIN

// 前向声明
struct IFrameInfo;
struct INextFrame;
struct IVector3;

/// State_Base — 状态基类，对应 TS State_Base
class State_Base
{
public:
  const StateType state;

  explicit State_Base(StateType state) noexcept
      : state(state)
  {
  }

  virtual ~State_Base() = default;

  // === 生命周期钩子 ===

  /** 更新前调用（可选覆写） */
  virtual void pre_update(Entity & /*e*/) {}

  /** 每帧更新 */
  virtual void update(Entity &e);

  /** 进入状态时调用（可选覆写） */
  virtual void enter(Entity & /*e*/, const IFrameInfo & /*prev_frame*/) {}

  /** 离开状态时调用 */
  virtual void leave(Entity &e, const IFrameInfo &next_frame);

  /** 死亡时调用（可选覆写） */
  virtual void on_dead(Entity & /*e*/) {}

  /** 落地时调用（可选覆写） */
  virtual void on_landing(Entity & /*e*/, const IVector3 & /*velocity*/) {}

  // === 查询钩子 ===

  /** 获取重力值（可选覆写，返回 -1 表示不处理） */
  virtual double get_gravity(Entity & /*e*/) { return -1.0; }

  /** 获取猝死帧（可选覆写） */
  virtual const IFrameInfo *get_sudden_death_frame(Entity & /*e*/) { return nullptr; }

  /** 获取被抓结束帧（可选覆写） */
  virtual const IFrameInfo *get_caught_end_frame(Entity & /*e*/) { return nullptr; }

  /** 获取自动帧（可选覆写） */
  virtual const IFrameInfo *get_auto_frame(Entity & /*e*/) { return nullptr; }

  /** 按 ID 查找帧（可选覆写） */
  virtual const IFrameInfo *find_frame_by_id(Entity & /*e*/, const std::string * /*id*/) { return nullptr; }
};

LFW_NS_END
#endif // LFW_CORE_STATE_STATE_BASE_HPP
