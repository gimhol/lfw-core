#ifndef LFW_CORE_BUFF_BUFF_MAGICFLUTE_H
#define LFW_CORE_BUFF_BUFF_MAGICFLUTE_H

#include "lfw-core/buff/Buff.h"

LFW_NS_BEGIN

/**
 * 魔笛 Buff — 对应 TS Buff_MagicFlute
 */
class Buff_MagicFlute : public Buff
{
public:
  double injury = 1;
  double injury_r = 0.5;

  using Buff::Buff;

  void init() override;
  BuffResult on_tick(Entity *attacker, Entity *victim) override;
  BuffResult on_update(Entity *attacker, Entity *victim) override;
};

LFW_NS_END

#endif
