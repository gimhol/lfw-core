#include "lfw-core/state/CharacterState_Injured.h"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

void CharacterState_Injured::enter(Entity &e, const IFrameInfo &prev_frame)
{
  CharacterState_Base::enter(e, prev_frame);
  // 重型武器掉落并转移队伍
  if (auto *h = e.holding())
  {
    if (h->base_type() == 1) // WeaponEnum::Heavy
    {
      e.drop_holding();
      h->set_team(e.team());
    }
  }
}

LFW_NS_END
