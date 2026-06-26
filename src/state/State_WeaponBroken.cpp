#include "lfw-core/state/State_WeaponBroken.h"
#include "lfw-core/defines/GONE_FRAME_INFO.hpp"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

void State_WeaponBroken::on_landing(Entity &e, const IVector3 &)
{
  e.enter_frame(GONE_FRAME_INFO);
}

LFW_NS_END
