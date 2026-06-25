#ifndef LFW_CORE_ENTITY_ENTITY_HPP
#define LFW_CORE_ENTITY_ENTITY_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "lfw-core/defines/StateType.hpp"

namespace lfw
{

  struct IOpointInfo;
  struct IFrameInfo;
  struct INextFrame;
  struct IVector3;
  class LFW;

  /// Entity — 实体基类（虚类），对应 TS Entity 的核心接口
  /// 渐进式转换：逐步添加成员，当前已添加 Buff 系统所需的最小接口
  class Entity
  {
  public:
    virtual ~Entity() = default;

    // === 基础标识 ===

    /** 实体唯一 ID */
    virtual const std::string &id() const = 0;

    // === 状态系统所需属性 ===

    /** 生存帧数 */
    virtual double lifetime() const = 0;

    /** 当前治疗量 */
    virtual double healing() const = 0;

    /** 设置当前治疗量 */
    virtual void set_healing(double v) = 0;

    /** 当前状态 */
    virtual StateType state() const = 0;

    // === 游戏上下文 ===

    /** 游戏上下文（含 mt 随机数生成器） */
    virtual LFW *lfw() const { return nullptr; }

    // === 帧几何（spawn_buring_smoke 等需要） ===

    /** 当前帧信息 */
    virtual const IFrameInfo &current_frame() const = 0;

    // === 状态系统所需方法 ===

    /** 应用 opoint 生成实体 */
    virtual void apply_opoints(const std::vector<IOpointInfo> &opoints) = 0;

    // === 帧查询 ===

    /** 获取猝死帧（可选覆写） */
    virtual const IFrameInfo *get_sudden_death_frame() { return nullptr; }

    /** 获取被抓结束帧（可选覆写） */
    virtual const IFrameInfo *get_caught_end_frame() { return nullptr; }

    /** 获取自动帧（可选覆写） */
    virtual const IFrameInfo *get_auto_frame() { return nullptr; }

    /** 按 ID 查找帧（可选覆写） */
    virtual const IFrameInfo *find_frame_by_id(const std::string * /*id*/) { return nullptr; }
  };

} // namespace lfw

#endif // LFW_CORE_ENTITY_ENTITY_HPP
