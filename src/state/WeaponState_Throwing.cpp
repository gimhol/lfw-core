#include "lfw-core/state/WeaponState_Throwing.h"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

double WeaponState_Throwing::get_gravity(Entity &e)
{
  return e.dataset("weapon_throwing_gravity");
}

void WeaponState_Throwing::enter(Entity &e, const IFrameInfo &)
{
  _hit_ground_weapons.insert(&e);
}

void WeaponState_Throwing::leave(Entity &e, const IFrameInfo &)
{
  _hit_ground_weapons.erase(&e);
}

void WeaponState_Throwing::on_landing(Entity &e, const IVector3 &velocity)
{
  const auto &on_landing = e.current_frame().on_landing;
  if (on_landing.has_value())
  {
    e.enter_frame(on_landing.value());
    return;
  }
  // TODO: e.data().indexes?.throw_on_ground || indexes?.just_on_ground
  hit_ground_rebouncing(e, nullptr, velocity);
}

void WeaponState_Throwing::update(Entity &e)
{
  e.handle_ground_velocity_decay();
}

LFW_NS_END
