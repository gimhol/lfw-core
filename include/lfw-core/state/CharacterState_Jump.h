#ifndef LFW_CORE_STATE_CHARACTERSTATE_JUMP_H
#define LFW_CORE_STATE_CHARACTERSTATE_JUMP_H
#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"
LFW_NS_BEGIN
class CharacterState_Jump : public CharacterState_Base {
public:
  explicit CharacterState_Jump(StateType s = StateType::Jump) : CharacterState_Base(s) {}
  void update(Entity &e) override;  // TODO: ctrl + jumping calc
};
LFW_NS_END
#endif
