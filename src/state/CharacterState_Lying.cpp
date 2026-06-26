#include "lfw-core/state/CharacterState_Lying.h"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

void CharacterState_Lying::update(Entity &e)
{
  CharacterState_Base::update(e);
  // TODO: lying recovery logic pending
}

LFW_NS_END
