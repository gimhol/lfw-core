#ifndef LFW_CORE_BUFF_BUFF_ELECTROSHOCK_H
#define LFW_CORE_BUFF_BUFF_ELECTROSHOCK_H

#include "lfw-core/buff/Buff.h"

LFW_NS_BEGIN

/**
 * 电击 Buff — 对应 TS Buff_Electroshock
 *
 * TODO: 等 Entity 的 wait / full StateEnum 覆盖后实现完整逻辑
 */
class Buff_Electroshock : public Buff
{
public:
  static constexpr const char *KIND = "Electroshock";

  using Buff::Buff;

  void init() override { set_ticks(3); }

  BuffResult on_tick(Entity *, Entity *) override
  {
    // TODO: 实现 Entity.state() 判断 + victim->wait 修改
    return BuffResult::Keep;
  }
};

LFW_NS_END

#endif
