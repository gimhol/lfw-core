#include "lfw-core/buff/Buff_Electroshock.h"

LFW_NS_BEGIN

void Buff_Electroshock::init() { set_ticks(3); }

BuffResult Buff_Electroshock::on_tick(Entity * /*attacker*/, Entity *victim)
{
  if (!victim || !is_fighter(victim))
    return BuffResult::Del;

  auto s = victim->state();
  if (s == StateType::Falling || s == StateType::Injured || s == StateType::Lying)
    return BuffResult::Keep;

  victim->set_wait(victim->wait() + 1);
  return BuffResult::Keep;
}

LFW_NS_END
