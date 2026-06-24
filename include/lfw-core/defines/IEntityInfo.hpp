#ifndef LFW_CORE_DEFINES_IENTITY_INFO_HPP
#define LFW_CORE_DEFINES_IENTITY_INFO_HPP

#include <optional>
#include <string>
#include <vector>

/// IEntityInfo — 实体配置信息
struct IEntityInfo
{
  std::optional<std::string> id;
  std::optional<std::string> name;
  std::optional<std::string> oid;
  std::optional<int> team;
  std::optional<double> hp;
  std::optional<double> mp;
  std::optional<double> x, y, z;
  std::optional<int> facing;
  std::optional<std::string> state;
  std::optional<std::vector<std::string>> weapons;
  std::optional<bool> is_bot;
};

#endif
