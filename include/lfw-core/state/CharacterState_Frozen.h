#ifndef LFW_CORE_STATE_CHARACTERSTATE_FROZEN_H
#define LFW_CORE_STATE_CHARACTERSTATE_FROZEN_H
#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"
LFW_NS_BEGIN
class CharacterState_Frozen : public CharacterState_Base {
public:
  explicit CharacterState_Frozen(StateType s = StateType::Frozen) : CharacterState_Base(s) {}
  void update(Entity &e) override;
};
LFW_NS_END
#endif
