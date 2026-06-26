#include "lfw-core/state/States.h"
#include "lfw-core/state/State_Base.hpp"
#include "lfw-core/ditto/Ditto.h"

LFW_NS_BEGIN

State_Base *States::get(int key) const
{
  auto it = state_map.find(key);
  return it != state_map.end() ? it->second : nullptr;
}

void States::set(int key, State_Base *value)
{
  if (state_map.find(key) != state_map.end())
    Ditto::warn("[States::set] key already exists");
  state_map[key] = value;
}

void States::add(std::initializer_list<State_Base *> values)
{
  for (auto *v : values)
  {
    int key = static_cast<int>(v->state);
    if (state_map.find(key) != state_map.end())
      Ditto::warn("[States::add] state key already exists");
    state_map[key] = v;
  }
}

void States::set_in_range(int from, int to, const std::function<State_Base *(int)> &create)
{
  for (int key = from; key <= to; ++key)
    set(key, create(key));
}

void States::set_all_of(const std::vector<int> &keys, const std::function<State_Base *(int)> &create)
{
  for (int key : keys)
    set(key, create(key));
}

State_Base *States::fallback(EntityType type, int code)
{
  int state_key = static_cast<int>(type) * 10000 + code;
  auto *s = get(state_key);
  if (s)
    return s;

  // TODO: CharacterState_Base / WeaponState_Base / BallState_Base 待转换
  auto *state_ptr = new State_Base(static_cast<StateType>(code));
  set(state_key, state_ptr);
  return state_ptr;
}

LFW_NS_END
