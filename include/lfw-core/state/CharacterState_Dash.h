#ifndef LFW_CORE_STATE_CHARACTERSTATE_DASH_H
#define LFW_CORE_STATE_CHARACTERSTATE_DASH_H
#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"
LFW_NS_BEGIN
class CharacterState_Dash : public CharacterState_Base {
public:
  explicit CharacterState_Dash(StateType s = StateType::Dash) : CharacterState_Base(s) {}
  void update(Entity &e) override;
};
LFW_NS_END
#endif
