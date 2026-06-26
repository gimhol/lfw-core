#ifndef LFW_CORE_STATE_CHARACTERSTATE_FALLING_H
#define LFW_CORE_STATE_CHARACTERSTATE_FALLING_H
#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"
LFW_NS_BEGIN
class CharacterState_Falling : public CharacterState_Base {
public:
  explicit CharacterState_Falling(StateType s = StateType::Falling) : CharacterState_Base(s) {}
  void update(Entity &e) override;
};
LFW_NS_END
#endif
