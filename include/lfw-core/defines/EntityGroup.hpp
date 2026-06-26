#ifndef LFW_CORE_DEFINES_ENTITYGROUP_HPP
#define LFW_CORE_DEFINES_ENTITYGROUP_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// EntityGroup.ts
#define ENUM_ITEMS(X)                                  \
  X(EntityGroup, Hidden, "hidden", "", )               \
  X(EntityGroup, Boss, "Boss", "", )                   \
  X(EntityGroup, Giant, "Giant", "", )                 \
  X(EntityGroup, Regular, "1000", "", )                \
  X(EntityGroup, _3000, "3000", "", )                  \
  X(EntityGroup, VsWeapon, "VsWeapon", "", )           \
  X(EntityGroup, StageWeapon, "StageWeapon", "", )     \
  X(EntityGroup, FreezableBall, "FreezableBall", "", ) \
  X(EntityGroup, Freezer, "Freezer", "", )             \
  X(EntityGroup, Dev, "Dev", "", )

enum class EntityGroup : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(EntityGroupStringMap, ENUM_ITEMS, EntityGroup)
GEN_ENUM_NAME_MAP(EntityGroupNameMap, ENUM_ITEMS, EntityGroup)
GEN_ENUM_DESC_MAP(EntityGroupDescMap, ENUM_ITEMS, EntityGroup)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(entity_group_to_string, entity_group_from_string, EntityGroup, EntityGroupStringMap)
DEFINE_ENUM_STR_CONVERTERS(entity_group_to_name, entity_group_from_name, EntityGroup, EntityGroupNameMap)
DEFINE_ENUM_TO_STR(entity_group_to_desc, EntityGroup, EntityGroupDescMap)
LFW_NS_END

#endif // LFW_CORE_DEFINES_ENTITYGROUP_HPP
