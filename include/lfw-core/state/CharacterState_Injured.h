#ifndef LFW_CORE_STATE_CHARACTERSTATE_INJURED_H
#define LFW_CORE_STATE_CHARACTERSTATE_INJURED_H
#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"
LFW_NS_BEGIN
class CharacterState_Injured : public CharacterState_Base
{
public:
  explicit CharacterState_Injured(StateType s = StateType::Injured)
      : CharacterState_Base(s) {}

  void enter(Entity &e, const IFrameInfo &prev_frame) override;
};
LFW_NS_END
#endif
