#ifndef LFW_CORE_ANIMATION_EASING_H
#define LFW_CORE_ANIMATION_EASING_H

#include <functional>

#include "lfw-core/animation/Animation.h"

LFW_NS_BEGIN

/**
 * 缓动动画 — 对应 TS Easing
 *
 * 在 begin 和 end 之间按缓动函数插值。
 * 默认使用 ease_in_out_sine 缓动。
 */
class Easing : public Animation
{
public:
  using EasingFunc = std::function<double(double factor, double from, double to)>;

  Easing(double begin_val = 0, double end_val = 1);

  double val_1() const;
  void set_val_1(double v);

  double val_2() const;
  void set_val_2(double v);

  const EasingFunc &easing() const;
  void set_easing(EasingFunc v);

  Easing &set(double begin_val, double end_val);
  Easing &set_easing_chain(EasingFunc v);

  Animation &calc() override;

protected:
  double _val_1 = 0;
  double _val_2 = 1;
  EasingFunc _easing;
};

LFW_NS_END

#endif
