#ifndef LFW_CORE_DEFINES_ENTITYTYPE_HPP
#define LFW_CORE_DEFINES_ENTITYTYPE_HPP

#include <cstdint>

/// EntityEnum.ts — 使用 HitFlag 位值
enum class EntityType : uint8_t
{
  Entity = 4,
  Fighter = 8,
  Weapon = 16,
  Ball = 32
};

#endif // LFW_CORE_DEFINES_ENTITYTYPE_HPP
