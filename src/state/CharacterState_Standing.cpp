#include "lfw-core/state/CharacterState_Standing.h"
#include "lfw-core/state/State_Base.hpp"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

void CharacterState_Standing::update(Entity &e)
{
  CharacterState_Base::update(e);

  if (e.hp() <= 0)
  {
    auto *nf = e.get_sudden_death_frame();
    if (nf)
      e.enter_frame(*nf);
  }
  else if (e.position().y > e.ground_y())
  {
    e.enter_frame_by_id(""); // TODO: e.data.indexes?.in_the_skys?.[0]
  }
}

LFW_NS_END
