#ifndef LFW_CORE_BUFF_BUFF_ELECTROSHOCK_H
#define LFW_CORE_BUFF_BUFF_ELECTROSHOCK_H

#include "lfw-core/buff/Buff.h"

LFW_NS_BEGIN

/**
 * 电击 Buff — 对应 TS Buff_Electroshock
 */
class Buff_Electroshock : public Buff
{
public:
  static constexpr const char *KIND = "Electroshock";

  using Buff::Buff;

  void init() override { set_ticks(3); }

  BuffResult on_tick(Entity * /*attacker*/, Entity *victim) override
  {
    if (!victim || !is_fighter(victim))
      return BuffResult::Del;

    auto s = victim->state();
    if (s == StateType::Falling || s == StateType::Injured || s == StateType::Lying)
      return BuffResult::Keep;

    victim->wait += 1;
    return BuffResult::Keep;
  }
};

LFW_NS_END

#endif
