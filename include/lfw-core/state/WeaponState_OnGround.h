#ifndef LFW_CORE_STATE_WEAPONSTATE_ONGROUND_H
#define LFW_CORE_STATE_WEAPONSTATE_ONGROUND_H

#include "lfw-core/state/WeaponState_Base.h"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class WeaponState_OnGround : public WeaponState_Base
{
public:
  using WeaponState_Base::WeaponState_Base;

  void enter(Entity &e, const IFrameInfo &prev_frame) override;
  void update(Entity &e) override;
};

LFW_NS_END
#endif