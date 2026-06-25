#ifndef LFW_CORE_BUFF_BUFF_MAGICFLUTE2_H
#define LFW_CORE_BUFF_BUFF_MAGICFLUTE2_H

#include "lfw-core/buff/Buff.h"

LFW_NS_BEGIN

/**
 * 魔笛2 Buff — 对应 TS Buff_MagicFlute2
 * TODO: 等 Entity 完整转换后补全
 */
class Buff_MagicFlute2 : public Buff
{
public:
  double injury = 1;
  double injury_r = 0.5;

  using Buff::Buff;

  void init() override
  {
    set_ticks(3);
    set_duration(2);
  }
  BuffResult on_tick(Entity *, Entity *) override { return BuffResult::Keep; }
  BuffResult on_update(Entity *, Entity *) override { return BuffResult::Keep; }
};

LFW_NS_END

#endif
