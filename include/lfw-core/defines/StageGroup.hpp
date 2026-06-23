#ifndef LFW_CORE_DEFINES_STAGEGROUP_HPP
#define LFW_CORE_DEFINES_STAGEGROUP_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class StageGroup : uint8_t
{
  Hidden,
  Dev
};

inline std::string_view stage_group_to_string(StageGroup v)
{
  switch (v)
  {
  case StageGroup::Hidden:
    return "hidden";
  case StageGroup::Dev:
    return "Dev";
  }
  return "";
}

inline std::optional<StageGroup> stage_group_from_string(std::string_view s)
{
  static const auto m = std::unordered_map<std::string_view, StageGroup>{
      {"hidden", StageGroup::Hidden},
      {"Dev", StageGroup::Dev},
  };
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_STAGEGROUP_HPP
