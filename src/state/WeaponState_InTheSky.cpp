#include "lfw-core/state/WeaponState_InTheSky.h"
#include "lfw-core/entity/Entity.h"
#include <cmath>

LFW_NS_BEGIN

void WeaponState_InTheSky::enter(Entity &e, const IFrameInfo &)
{
  _hit_ground_weapons.insert(&e);
}

void WeaponState_InTheSky::leave(Entity &e, const IFrameInfo &)
{
  _hit_ground_weapons.erase(&e);
}

void WeaponState_InTheSky::on_landing(Entity &e, const IVector3 &velocity)
{
  const auto &on_landing = e.current_frame().on_landing;
  if (on_landing.has_value())
  {
    e.enter_frame(on_landing.value());
    return;
  }
  // TODO: e.data().indexes?.just_on_ground
  hit_ground_rebouncing(e, nullptr, velocity);
}

void WeaponState_InTheSky::update(Entity &e)
{
  e.handle_ground_velocity_decay();

  double vy = e.velocity_y(), vx = e.velocity_x(), vz = e.velocity_z();
  // TODO: Defines.WT_FAST_* 常量未转换，使用默认阈值
  double fast_x = 99, fast_y = 99, fast_z = 99;

  // 速度太快 → 变为 throwing
  // TODO: wt != WT.Heavy 判断
  if (vy < -fast_y || vy > fast_y || vx < -fast_x || vx > fast_x || vz < -fast_z || vz > fast_z)
  {
    // TODO: e.find_align_frame → throwing frame
  }
}

LFW_NS_END
