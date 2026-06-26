#include "lfw-core/state/WeaponState_OnGround.h"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

void WeaponState_OnGround::enter(Entity &e, const IFrameInfo &)
{
  // TODO: e.lfw.new_team (LFW 未完整转换)
}

void WeaponState_OnGround::update(Entity &e)
{
  e.handle_ground_velocity_decay();
}

LFW_NS_END
