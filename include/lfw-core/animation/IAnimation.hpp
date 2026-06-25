#ifndef LFW_CORE_ANIMATION_IANIMATION_HPP
#define LFW_CORE_ANIMATION_IANIMATION_HPP

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/**
 * 动画接口 — 对应 TS IAnimation
 */
struct IAnimation
{
  virtual ~IAnimation() = default;

  /// 当前值
  virtual double value() const = 0;

  /// 动画时长（毫秒）
  virtual double duration() const = 0;

  /// 动画进度
  virtual double time() const = 0;

  /// 是否反向播放
  virtual bool reverse() const = 0;

  /// 设置当前值
  virtual void set_value(double v) = 0;

  /// 设置动画时长
  virtual void set_duration(double v) = 0;

  /// 设置动画进度
  virtual void set_time(double v) = 0;

  /// 设置是否反向播放
  virtual void set_reverse(bool v) = 0;

  /// 计算当前值 — 此函数中应该计算 value
  virtual IAnimation &calc() = 0;

  /// 结束动画（使用当前反向状态）
  IAnimation &end() { return end(reverse()); }

  /// 结束动画（指定反向状态）
  virtual IAnimation &end(bool reverse_val) = 0;

  /// 更新动画
  virtual IAnimation &update(double dt) = 0;
};

LFW_NS_END

#endif // LFW_CORE_ANIMATION_IANIMATION_HPP
