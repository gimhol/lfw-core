#include "lfw-core/buff/Buff_MagicFlute.h"
#include <lfw-core/defines/SpeedMode.hpp>
#include <lfw-core/entity/calc_v.h>

LFW_NS_BEGIN

void Buff_MagicFlute::init()
{
  set_ticks(3);
  set_duration(2);
}

BuffResult Buff_MagicFlute::on_tick(Entity *attacker, Entity *victim)
{
  if (!victim)
    return BuffResult::Del;

  double prev_hp = victim->hp();
  victim->set_hp_r(victim->hp_r() - injury_r);
  victim->set_hp(victim->hp() - injury);
  victim->fallinjury = 20;
  victim->set_toughness(0);

  if (attacker)
    apply_damage_summary(attacker, injury, victim, prev_hp);

  return BuffResult::Keep;
}

BuffResult Buff_MagicFlute::on_update(Entity *attacker, Entity *victim)
{
  if (!victim)
    return BuffResult::Del;

  double vy = calc_v(victim->velocity_y(), 3, SpeedMode::AccTo, 3, 1);
  victim->set_velocity_y(vy);
  victim->handle_velocity_decay(0.25);

  switch (victim->entity_type())
  {
  case EntityType::Fighter:
    if (victim->state() != StateType::Falling)
      victim->enter_frame_by_id("");
    break;

  case EntityType::Weapon:
    switch (victim->state())
    {
    case StateType::WeaponInTheSky:
    case StateType::HeavyWeaponInTheSky:
      break;
    default:
      if (attacker)
        victim->set_team(attacker->team());
      victim->enter_frame_by_id("");
      break;
    }
    break;

  default:
    break;
  }

  return BuffResult::Keep;
}

LFW_NS_END
