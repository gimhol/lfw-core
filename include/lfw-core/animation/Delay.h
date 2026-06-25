#ifndef LFW_CORE_ANIMATION_DELAY_H
#define LFW_CORE_ANIMATION_DELAY_H

#include "lfw-core/animation/Animation.h"

LFW_NS_BEGIN

/**
 * 延时动画 — 对应 TS Delay
 *
 * 始终保持固定 value，不随时间变化。
 */
class Delay : public Animation
{
public:
  explicit Delay(double val = 0)
  {
    _value = val;
  }

  Animation &calc() override { return *this; }
};

LFW_NS_END

#endif
