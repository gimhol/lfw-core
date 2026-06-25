#ifndef LFW_CORE_ANIMATION_ANIMATION_H
#define LFW_CORE_ANIMATION_ANIMATION_H

#include "lfw-core/animation/IAnimation.h"
#include "lfw-core/animation/Loop.h"

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
  static const char *tag();

  Animation() = default;

  // ---- IAnimation 接口 ----
  double value() const override;
  void set_value(double v) override;

  double duration() const override;
  void set_duration(double v) override;

  double time() const override;
  void set_time(double v) override;

  bool reverse() const override;
  void set_reverse(bool v) override;

  Animation &calc() override;
  using IAnimation::end;
  Animation &end(bool reverse_val) override;
  Animation &update(double dt) override;

  // ---- 扩展接口 ----
  bool done() const;

  int fill_mode() const;
  void set_fill_mode(int v);

  int count() const;
  void set_count(int v);

  int times() const;
  void set_times(int v);

  int direction() const;
  void set_direction(int v);

  Animation &start();
  virtual Animation &start(bool reverse_val);

  Animation &auto_trip(bool reverse_val, double dt);

  Loop &loop();
  const Loop &loop() const;

protected:
  double _value = 0;
  double _time = 0;
  double _duration = 0;
  int _direction = 1;
  int _fill_mode = 1;
  Loop _loop;
};

LFW_NS_END

#endif
