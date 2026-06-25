#ifndef LFW_CORE_STATE_SPAWN_BURING_SMOKE_HPP
#define LFW_CORE_STATE_SPAWN_BURING_SMOKE_HPP

#include "lfw-core/defines/IOpointInfo.hpp"
#include "lfw-core/defines/OID.hpp"
#include "lfw-core/entity/Entity.hpp"
#include "lfw-core/entity/Lfw.hpp"

#include <cmath>

LFW_NS_BEGIN

/// spawn_buring_smoke — 生成燃烧烟雾 opoint
/// 对应 TS 的 spawn_buring_smoke(entity, 1|2)
///
/// foo=1: 燃烧状态烟雾（上半身随机位置）
/// foo=2: 燃烧逃跑状态烟雾（中心偏上随机位置）
///
/// @note 位置使用固定默认值（IFrameInfo 尚未包含 width/height/centerx/centery）
/// @note 朝向通过 lfw().mt.pick() 随机
inline IOpointInfo spawn_buring_smoke(const Entity &e, int foo)
{
  IOpointInfo ret;
  ret.kind = 0;
  ret.x = 0;
  ret.y = 0;
  ret.oid = ::oid_to_string(::OID::BrokenWeapon);

  // 随机朝向：对应 TS mt.pick([-1, 1])
  if (auto *l = e.lfw())
    ret.facing = static_cast<int>(l->mt.range(0, 2)) * 2 - 1; // -1 or 1
  else
    ret.facing = 1;

  ret.dvz = 0;
  ret.count = 1;

  switch (foo)
  {
  case 1:
    // TS: x = mt.range(w/4, 3w/4), y = centery + mt.range(-h/2, 0)
    // TODO: 用 e.current_frame().width/height/centerx/centery 替代硬编码
    ret.x = 20;
    ret.y = -30;
    break;
  case 2:
    // TS: x = centerx + mt.range(-w/6, w/6), y = centery + mt.range(-3h/4, 0)
    ret.x = 40;
    ret.y = -40;
    break;
  default:
    break;
  }

  return ret;
}

LFW_NS_END

#endif
