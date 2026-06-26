#include "lfw-core/state/WeaponState_Base.h"
#include "lfw-core/entity/Entity.h"
#include <lfw-core/utils/math/Math.hpp>

LFW_NS_BEGIN

const IFrameInfo *WeaponState_Base::get_auto_frame(Entity &e)
{
  // TODO: e.data().indexes?.in_the_skys / on_ground (indexes 字段未转换)
  return nullptr;
}

void WeaponState_Base::on_landing(Entity &e, const IVector3 & /*velocity*/)
{
  const auto &on_landing = e.current_frame().on_landing;
  if (on_landing.has_value())
  {
    e.enter_frame(on_landing.value());
    return;
  }
  // TODO: e.data().indexes?.on_ground
  e.enter_frame_by_id("");
}

void WeaponState_Base::update(Entity &e)
{
  e.handle_ground_velocity_decay();
}

void WeaponState_Base::hit_ground_rebouncing(Entity &e, const std::string *nf_id, const IVector3 &velocity)
{
  double vy = velocity.y, vx = velocity.x, vz = velocity.z;

  // TODO: Defines.WT_BOUNCE_* / WT_FAST_* 常量未转换，使用默认值
  double bounce_x = 0.5, bounce_y = 0.5, bounce_z = 0.5;
  double bounce_min_x = 99, bounce_min_y = 0.5, bounce_min_z = 99;
  double fast_x = 99, fast_y = 99, fast_z = 99;

  double dvy = math::round_float(-vy * bounce_y);
  double dvx = math::round_float(vx * bounce_x);
  double dvz = math::round_float(vz * bounce_z);

  if (_hit_ground_weapons.count(&e))
  {
    _hit_ground_weapons.erase(&e);
    // TODO: drop_hurt 伤害处理
  }

  bool bounced = false;
  if (std::abs(dvy) >= bounce_min_y)
  {
    e.set_velocity_y(dvy);
    bounced = true;
  }
  if (std::abs(dvx) >= bounce_min_x)
  {
    e.set_velocity_x(dvx);
    bounced = true;
  }
  if (std::abs(dvz) >= bounce_min_z)
  {
    e.set_velocity_z(dvz);
    bounced = true;
  }

  if (bounced && nf_id)
    e.enter_frame_by_id(*nf_id);
}

LFW_NS_END
