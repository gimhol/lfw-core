#ifndef LFW_CORE_STATE_CHARACTERSTATE_RUNNING_H
#define LFW_CORE_STATE_CHARACTERSTATE_RUNNING_H

#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class CharacterState_Running : public CharacterState_Base
{
public:
  explicit CharacterState_Running(StateType s = StateType::Running)
      : CharacterState_Base(s) {}

  void update(Entity &e) override;
};

LFW_NS_END

#endif