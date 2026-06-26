#ifndef LFW_CORE_STATE_WEAPONSTATE_BASE_H
#define LFW_CORE_STATE_WEAPONSTATE_BASE_H

#include "lfw-core/state/State_Base.hpp"
#include "lfw-core/core.hpp"
#include <set>

LFW_NS_BEGIN

class WeaponState_Base : public State_Base
{
public:
  using State_Base::State_Base;

  const IFrameInfo *get_auto_frame(Entity &e) override;
  void on_landing(Entity &e, const IVector3 &velocity) override;
  void update(Entity &e) override;

protected:
  std::set<Entity *> _hit_ground_weapons;

  /// 落地反弹处理（对应 TS hit_ground_rebouncing）
  void hit_ground_rebouncing(Entity &e, const std::string *nf_id, const IVector3 &velocity);
};

LFW_NS_END
#endif
LFW_NS_END
#endif