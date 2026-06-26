#include "lfw-core/state/CharacterState_Walking.h"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

void CharacterState_Walking::update(Entity &e)
{
  CharacterState_Base::update(e);

  // TODO: e.ctrl.UD / e.ctrl.LR not available until BaseController is converted
  // if (!UD && !LR && !e.wait()) {
  //   check holding weapon → stay in frame or enter standing
  // }

  if (e.hp() <= 0)
  {
    auto *nf = e.get_sudden_death_frame();
    if (nf)
      e.enter_frame(*nf);
  }
  else if (e.position().y > e.ground_y())
  {
    e.enter_frame_by_id("");
  }
}

LFW_NS_END
