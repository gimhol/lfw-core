#include "lfw-core/state/CharacterState_Falling.h"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

void CharacterState_Falling::update(Entity &e)
{
  CharacterState_Base::update(e);
  // TODO: bouncing / falling logic pending
}

LFW_NS_END
