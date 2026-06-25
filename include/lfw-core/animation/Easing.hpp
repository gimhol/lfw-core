#ifndef LFW_CORE_ANIMATION_EASING_HPP
#define LFW_CORE_ANIMATION_EASING_HPP

#include <functional>

#include "lfw-core/animation/Animation.hpp"

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

  Easing(double begin_val = 0, double end_val = 1)
  {
    _val_1 = begin_val;
    _val_2 = end_val;
  }

  /// 起始值
  double val_1() const { return _val_1; }
  void set_val_1(double v) { _val_1 = v; }

  /// 结束值
  double val_2() const { return _val_2; }
  void set_val_2(double v) { _val_2 = v; }

  /// 缓动函数
  const EasingFunc &easing() const { return _easing; }
  void set_easing(EasingFunc v) { _easing = std::move(v); }

  /// 同时设置起始值和结束值
  Easing &set(double begin_val, double end_val)
  {
    _val_1 = begin_val;
    _val_2 = end_val;
    return *this;
  }

  Easing &set_easing_chain(EasingFunc v)
  {
    _easing = std::move(v);
    return *this;
  }

  Animation &calc() override;

protected:
  double _val_1 = 0;
  double _val_2 = 1;
  EasingFunc _easing;
};

LFW_NS_END

#endif // LFW_CORE_ANIMATION_EASING_HPP
