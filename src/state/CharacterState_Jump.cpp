#include "lfw-core/state/CharacterState_Jump.h"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

void CharacterState_Jump::update(Entity &e)
{
  // TODO: ctrl + jumping calc pending BaseController
  e.handle_ground_velocity_decay();
}

LFW_NS_END
