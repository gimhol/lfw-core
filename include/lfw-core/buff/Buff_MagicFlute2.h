#ifndef LFW_CORE_BUFF_BUFF_MAGICFLUTE2_H
#define LFW_CORE_BUFF_BUFF_MAGICFLUTE2_H

#include "lfw-core/buff/Buff.h"
#include "lfw-core/entity/calc_v.h"
#include "lfw-core/entity/type_check.h"

LFW_NS_BEGIN

/**
 * 魔笛2 Buff — 对应 TS Buff_MagicFlute2
 */
class Buff_MagicFlute2 : public Buff
{
public:
  double injury = 1;
  double injury_r = 0.5;

  using Buff::Buff;

  void init() override
  {
    set_ticks(3);
    set_duration(2);
  }

  BuffResult on_tick(Entity *attacker, Entity *victim) override
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

  BuffResult on_update(Entity *attacker, Entity *victim) override
  {
    if (!victim)
      return BuffResult::Del;

    double vy = calc_v(victim->velocity_y(), 1.5, SpeedMode::AccTo, 1.5, 1);
    victim->set_velocity_y(vy);
    victim->handle_velocity_decay(0.25);

    switch (victim->entity_type())
    {
    case EntityType::Fighter:
      if (victim->state() != StateType::Falling)
      {
        victim->enter_frame_by_id("");
      }
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
};

LFW_NS_END

#endif
