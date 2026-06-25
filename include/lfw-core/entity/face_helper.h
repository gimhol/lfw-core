#ifndef LFW_CORE_ENTITY_FACE_HELPER_H
#define LFW_CORE_ENTITY_FACE_HELPER_H

#include "lfw-core/core.hpp"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

/// 朝向（1=同向, -1=反向）— 对应 TS TFace
using TFace = int;

/// 判断两实体是否同向 — 对应 TS same_face
inline TFace same_face(const Entity &ref, const Entity &target)
{
  return ref.facing() == target.facing() ? 1 : -1;
}

/// 翻转朝向 — 对应 TS turn_face
inline TFace turn_face(TFace f)
{
  return f == 1 ? -1 : 1;
}

LFW_NS_END

#endif
