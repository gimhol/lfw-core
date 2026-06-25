#ifndef LFW_CORE_ENTITY_CALC_V_H
#define LFW_CORE_ENTITY_CALC_V_H

#include "lfw-core/core.hpp"
#include "lfw-core/defines/SpeedMode.hpp"

LFW_NS_BEGIN

/// 计算新速度 — 对应 TS calc_v
inline double calc_v(double current, double value, SpeedMode mode,
                     double acc = 0, int direction = 1)
{
  switch (mode)
  {
  case SpeedMode::Fixed:
    return value;
  case SpeedMode::Extra:
    return current;
  case SpeedMode::FixedAcc:
    return current + value;
  case SpeedMode::Acc:
    return current + value * direction;
  case SpeedMode::FixedLF2:
  {
    double target = value;
    if (current < target && target > 0)
      return target;
    if (current > target && target < 0)
      return target;
    return current;
  }
  case SpeedMode::AccTo:
  {
    double target = value;
    double dv = acc * direction;
    double next = current + dv;
    if (dv > 0)
      return next > target ? target : next;
    if (dv < 0)
      return next < target ? target : next;
    return current;
  }
  case SpeedMode::FixedAccTo:
  {
    double target = value;
    double dv = acc * direction;
    double next = current + dv;
    if (dv > 0)
      return next > target ? target : next;
    if (dv < 0)
      return next < target ? target : next;
    return current;
  }
  default:
    return current + value;
  }
}

LFW_NS_END

#endif
