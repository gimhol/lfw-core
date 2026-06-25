#include "lfw-core/state/State_Base.hpp"

#include "lfw-core/defines/StateType.hpp"
#include "lfw-core/entity/Entity.hpp"

LFW_NS_BEGIN

void State_Base::update(Entity &e)
{
  switch (e.state())
  {
  case StateType::Burning:
    if (static_cast<int>(e.lifetime()) % 2 != 0)
      e.apply_opoints({spawn_buring_smoke(e, 1)});
    break;
  case StateType::BurnRun:
    if (static_cast<int>(e.lifetime()) % 2 != 0)
      e.apply_opoints({spawn_buring_smoke(e, 2)});
    break;
  default:
    break;
  }
}

void State_Base::leave(Entity &e, const IFrameInfo & /*next_frame*/)
{
  switch (state)
  {
  case StateType::HealSelf:
    e.set_healing(STATE_HEAL_SELF_HP);
    break;
  default:
    break;
  }
}
LFW_NS_END
