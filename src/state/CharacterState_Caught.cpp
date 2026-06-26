#include "lfw-core/state/CharacterState_Caught.h"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

void CharacterState_Caught::enter(Entity &e, const IFrameInfo &)
{
  e.set_fall_value(e.fall_value_max());
  e.set_velocity(0, 0, 0);
  // TODO: e.drop_holding() + heavy weapon team swap
}

void CharacterState_Caught::update(Entity &e)
{
  CharacterState_Base::update(e);
  e.set_velocity(0, 0, 0);
}

LFW_NS_END
