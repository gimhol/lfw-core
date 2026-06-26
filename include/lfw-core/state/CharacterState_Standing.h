#ifndef LFW_CORE_STATE_CHARACTERSTATE_STANDING_H
#define LFW_CORE_STATE_CHARACTERSTATE_STANDING_H

#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class CharacterState_Standing : public CharacterState_Base
{
public:
  explicit CharacterState_Standing(StateType s = StateType::Standing)
      : CharacterState_Base(s) {}

  void update(Entity &e) override;
};

LFW_NS_END

#endif