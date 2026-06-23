#ifndef LFW_CORE_DEFINES_BACKGROUNDGROUP_HPP
#define LFW_CORE_DEFINES_BACKGROUNDGROUP_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class BackgroundGroup : uint8_t
{
  Regular,
  Hidden
};

inline std::string_view background_group_to_string(BackgroundGroup v)
{
  switch (v)
  {
  case BackgroundGroup::Regular:
    return "regular";
  case BackgroundGroup::Hidden:
    return "hidden";
  }
  return "";
}

inline std::optional<BackgroundGroup> background_group_from_string(std::string_view s)
{
  static const auto m = std::unordered_map<std::string_view, BackgroundGroup>{
      {"regular", BackgroundGroup::Regular},
      {"hidden", BackgroundGroup::Hidden},
  };
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_BACKGROUNDGROUP_HPP
