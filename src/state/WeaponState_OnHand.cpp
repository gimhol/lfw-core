#include "lfw-core/state/WeaponState_OnHand.h"
#include "lfw-core/entity/Entity.h"
#include <algorithm>

LFW_NS_BEGIN

void WeaponState_OnHand::pre_update(Entity &e)
{
  if (e.motionless() && e.bearer())
    e.bearer()->set_motionless(std::max(e.motionless(), e.bearer()->motionless()));
}

LFW_NS_END
