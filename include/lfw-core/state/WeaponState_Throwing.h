#ifndef LFW_CORE_STATE_WEAPONSTATE_THROWING_H
#define LFW_CORE_STATE_WEAPONSTATE_THROWING_H

#include "lfw-core/state/WeaponState_Base.h"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class WeaponState_Throwing : public WeaponState_Base
{
public:
  using WeaponState_Base::WeaponState_Base;

  double get_gravity(Entity &e) override;
  void enter(Entity &e, const IFrameInfo &prev_frame) override;
  void leave(Entity &e, const IFrameInfo &next_frame) override;
  void on_landing(Entity &e, const IVector3 &velocity) override;
  void update(Entity &e) override;
};

LFW_NS_END
#endif
LFW_NS_END
#endif