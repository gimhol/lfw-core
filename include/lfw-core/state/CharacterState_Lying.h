#ifndef LFW_CORE_STATE_CHARACTERSTATE_LYING_H
#define LFW_CORE_STATE_CHARACTERSTATE_LYING_H
#include "lfw-core/state/CharacterState_Base.h"
#include "lfw-core/core.hpp"
LFW_NS_BEGIN
class CharacterState_Lying : public CharacterState_Base {
public:
  explicit CharacterState_Lying(StateType s = StateType::Lying) : CharacterState_Base(s) {}
  void update(Entity &e) override;
};
LFW_NS_END
#endif
