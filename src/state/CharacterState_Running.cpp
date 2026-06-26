#include "lfw-core/state/CharacterState_Running.h"
#include "lfw-core/entity/Entity.h"
#include <cmath>

LFW_NS_BEGIN

void CharacterState_Running::update(Entity &e)
{
  CharacterState_Base::update(e);

  double vz = e.velocity().z;
  double vx = e.velocity_x();

  if (vz != 0)
  {
    double dz = std::abs(vz / 4);
    if (vx > dz)
      vx -= dz;
    if (vx < -dz)
      vx += dz;
    e.set_velocity_x(vx);
  }

  if (e.hp() <= 0)
  {
    auto *nf = e.get_sudden_death_frame();
    if (nf)
      e.enter_frame(*nf);
  }
}

LFW_NS_END
