#ifndef LFW_CORE_STATE_CHARACTERSTATE_CAUGHT_H
#define LFW_CORE_STATE_CHARACTERSTATE_CAUGHT_H
#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"
LFW_NS_BEGIN
class CharacterState_Caught : public CharacterState_Base
{
public:
  explicit CharacterState_Caught(StateType s = StateType::Caught)
      : CharacterState_Base(s) {}

  void enter(Entity &e, const IFrameInfo &prev_frame) override;
  void update(Entity &e) override;
};
LFW_NS_END
#endif
