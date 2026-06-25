#ifndef LFW_CORE_ANIMATION_PERIODIC_H
#define LFW_CORE_ANIMATION_PERIODIC_H

#include <cmath>
#include <limits>

#include "lfw-core/animation/Animation.h"

LFW_NS_BEGIN

/**
 * 周期性动画基类 — 对应 TS Periodic（abstract）
 *
 * 通过 method(v) 纯虚函数计算当前值，子类实现具体的周期函数。
 * duration 默认为 MAX_SAFE_INTEGER（无限时长）。
 */
class Periodic : public Animation
{
public:
  double offset = 0;

  Periodic(double bottom_val = 0, double height_val = 1, double scale_val = 1)
  {
    _duration = std::numeric_limits<double>::max();
    _b = bottom_val;
    _h = height_val;
    _s = scale_val;
  }

  /// 底部偏移
  double bottom() const { return _b; }
  void set_bottom(double v) { _b = v; }

  /// 振幅高度
  double height() const { return _h; }
  void set_height(double v) { _h = v; }

  /// 频率缩放
  double scale() const { return _s; }
  void set_scale(double v) { _s = v; }

  /// 设置偏移
  Periodic &set_offset(double v)
  {
    offset = v;
    return *this;
  }

  /// 同时设置 bottom、height、scale
  Periodic &set(double bottom_val, double height_val, double scale_val)
  {
    _b = bottom_val;
    _h = height_val;
    _s = scale_val;
    calc();
    return *this;
  }

  /// 子类实现具体的周期计算函数
  virtual double method(double v) const = 0;

  Animation &calc() override
  {
    _value = method(offset + _time * _s);
    return *this;
  }

protected:
  double _b = 0; // bottom
  double _h = 1; // height
  double _s = 1; // scale
};

LFW_NS_END

#endif
