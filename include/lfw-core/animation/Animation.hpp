#ifndef LFW_CORE_ANIMATION_ANIMATION_HPP
#define LFW_CORE_ANIMATION_ANIMATION_HPP

#include "lfw-core/animation/IAnimation.hpp"
#include "lfw-core/animation/Loop.hpp"

LFW_NS_BEGIN

/**
 * 基础动画类 — 对应 TS Animation
 *
 * 实现 IAnimation 接口，提供时间驱动的基础动画逻辑。
 * 支持方向控制、循环播放、填充模式。
 */
class Animation : public IAnimation
{
public:
  static const char *tag() { return "Animation"; }

  Animation() = default;

  // ---- IAnimation 接口 ----

  double value() const override { return _value; }
  void set_value(double v) override { _value = v; }

  double duration() const override { return _duration; }
  void set_duration(double v) override;

  double time() const override { return _time; }
  void set_time(double v) override;

  bool reverse() const override { return _direction == -1; }
  void set_reverse(bool v) override;

  Animation &calc() override;
  using IAnimation::end;
  Animation &end(bool reverse_val) override;
  Animation &update(double dt) override;

  // ---- 扩展接口 ----

  /// 是否已完成
  bool done() const;

  /// 填充模式（1=填充边界, 0=不填充）
  int fill_mode() const { return _fill_mode; }
  void set_fill_mode(int v);

  /// 循环次数
  int count() const { return _loop.count(); }
  void set_count(int v) { _loop.set_count(v); }

  /// 总循环次数
  int times() const { return _loop.times(); }
  void set_times(int v) { _loop.set_times(v); }

  /// 播放方向（1=正向, -1=反向）
  int direction() const { return _direction; }
  void set_direction(int v);

  /// 开始动画（使用当前反向状态）
  Animation &start() { return start(reverse()); }

  /// 开始动画（指定反向状态）
  Animation &start(bool reverse_val);

  /// 自动跳转（用于双向动画自动切换方向）
  Animation &auto_trip(bool reverse_val, double dt);

  /// 获取内部 Loop 引用
  Loop &loop() { return _loop; }
  const Loop &loop() const { return _loop; }

protected:
  double _value = 0;
  double _time = 0;
  double _duration = 0;
  int _direction = 1;
  int _fill_mode = 1;
  Loop _loop;
};

LFW_NS_END

#endif // LFW_CORE_ANIMATION_ANIMATION_HPP
