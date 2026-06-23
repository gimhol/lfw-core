#ifndef LFW_CORE_DEFINES_ENTITYGROUP_HPP
#define LFW_CORE_DEFINES_ENTITYGROUP_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

/// EntityGroup.ts
enum class EntityGroup : uint8_t
{
  Hidden,
  Boss,
  Giant,
  Regular,
  _3000,
  VsWeapon,
  StageWeapon,
  FreezableBall,
  Freezer,
  Dev
};

inline std::string_view entity_group_to_string(EntityGroup v)
{
  switch (v)
  {
  case EntityGroup::Hidden:
    return "hidden";
  case EntityGroup::Boss:
    return "Boss";
  case EntityGroup::Giant:
    return "Giant";
  case EntityGroup::Regular:
    return "1000";
  case EntityGroup::_3000:
    return "3000";
  case EntityGroup::VsWeapon:
    return "VsWeapon";
  case EntityGroup::StageWeapon:
    return "StageWeapon";
  case EntityGroup::FreezableBall:
    return "FreezableBall";
  case EntityGroup::Freezer:
    return "Freezer";
  case EntityGroup::Dev:
    return "Dev";
  }
  return "";
}

inline std::optional<EntityGroup> entity_group_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, EntityGroup> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(EntityGroup::Dev); ++i)
    {
      auto v = static_cast<EntityGroup>(i);
      r[entity_group_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_ENTITYGROUP_HPP
