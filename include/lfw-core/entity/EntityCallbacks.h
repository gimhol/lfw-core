#ifndef LFW_CORE_ENTITY_ENTITY_CALLBACKS_H
#define LFW_CORE_ENTITY_ENTITY_CALLBACKS_H

#include <string>

#include "lfw-core/base/Signal.h"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class Entity;

/// Entity 回调信号集 — 对应 TS IEntityCallbacks
/// 使用 Signal<> 替代 TS Callbacks 系统
struct EntityCallbacks
{
  Signal<Entity *, double, double> on_hp_changed;
  Signal<Entity *, double, double> on_mp_changed;
  Signal<Entity *, double, double> on_hp_max_changed;
  Signal<Entity *, double, double> on_mp_max_changed;
  Signal<Entity *, double, double> on_hp_r_changed;
  Signal<Entity *, std::string, std::string> on_team_changed;
  Signal<Entity *, std::string, std::string> on_name_changed;
  Signal<Entity *> on_dead;
  Signal<Entity *> on_disposed;
  Signal<Entity *, double, double> on_fall_value_changed;
  Signal<Entity *, double, double> on_toughness_changed;
  Signal<Entity *, double, double> on_toughness_max_changed;
  Signal<Entity *, double, double> on_defend_value_changed;
  Signal<Entity *, double, double> on_defend_value_max_changed;
  Signal<Entity *, double, double> on_healing_changed;
  Signal<Entity *, double, double> on_resting_changed;
  Signal<Entity *, double, double> on_resting_max_changed;
  Signal<Entity *, double, double> on_catch_time_max_changed;
  Signal<Entity *, double, double> on_fall_value_max_changed;
  Signal<Entity *, double, double> on_reserve_changed;
};

LFW_NS_END

#endif
