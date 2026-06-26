#ifndef LFW_CORE_STATE_WEAPONSTATE_ONHAND_H
#define LFW_CORE_STATE_WEAPONSTATE_ONHAND_H

#include "lfw-core/state/WeaponState_Base.h"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class WeaponState_OnHand : public WeaponState_Base
{
public:
  using WeaponState_Base::WeaponState_Base;

  void pre_update(Entity &e) override;
};

LFW_NS_END
#endif