#ifndef LFW_CORE_DEFINES_ENTITYTYPE_HPP
#define LFW_CORE_DEFINES_ENTITYTYPE_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

/// EntityEnum.ts — 使用 HitFlag 位值
#define ENUM_ITEMS(X)                        \
  X(EntityType, Entity, "entity", "", = 4)   \
  X(EntityType, Fighter, "fighter", "", = 8) \
  X(EntityType, Weapon, "weapon", "", = 16)  \
  X(EntityType, Ball, "ball", "", = 32)

#define ENUM_ITEM(ENUM, NAME, STR, DESC, VAL) NAME VAL,
enum class EntityType : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(EntityTypeStringMap, ENUM_ITEMS, EntityType)
GEN_ENUM_NAME_MAP(EntityTypeNameMap, ENUM_ITEMS, EntityType)
GEN_ENUM_DESC_MAP(EntityTypeDescMap, ENUM_ITEMS, EntityType)
#undef ENUM_ITEM
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(entity_type_to_string, entity_type_from_string, EntityType, EntityTypeStringMap)
DEFINE_ENUM_STR_CONVERTERS(entity_type_to_name, entity_type_from_name, EntityType, EntityTypeNameMap)
DEFINE_ENUM_TO_STR(entity_type_to_desc, EntityType, EntityTypeDescMap)
#endif // LFW_CORE_DEFINES_ENTITYTYPE_HPP
