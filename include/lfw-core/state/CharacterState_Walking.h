#ifndef LFW_CORE_STATE_CHARACTERSTATE_WALKING_H
#define LFW_CORE_STATE_CHARACTERSTATE_WALKING_H

#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class CharacterState_Walking : public CharacterState_Base
{
public:
  explicit CharacterState_Walking(StateType s = StateType::Walking)
      : CharacterState_Base(s) {}

  void update(Entity &e) override;
};

LFW_NS_END

#endif