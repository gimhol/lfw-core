#ifndef LFW_CORE_ENTITY_TYPE_CHECK_H
#define LFW_CORE_ENTITY_TYPE_CHECK_H

#include "lfw-core/core.hpp"
#include "lfw-core/defines/EntityType.hpp"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

/// 类型判断 — 对应 TS type_check.ts

inline bool is_fighter(const Entity *e)
{
  return e && e->entity_type() == EntityType::Fighter;
}

inline bool is_weapon(const Entity *e)
{
  return e && e->entity_type() == EntityType::Weapon;
}

inline bool is_ball(const Entity *e)
{
  return e && e->entity_type() == EntityType::Ball;
}

inline bool is_entity(const Entity *e)
{
  if (!e)
    return false;
  auto t = e->entity_type();
  return t == EntityType::Entity ||
         t == EntityType::Fighter ||
         t == EntityType::Weapon ||
         t == EntityType::Ball;
}

LFW_NS_END

#endif
