#ifndef LFW_CORE_DEFINES_WORLDVAL_HPP
#define LFW_CORE_DEFINES_WORLDVAL_HPP

#include "lfw-core/core.hpp"


#include <cstdint>
#include <optional>
#include <string_view>

LFW_NS_BEGIN

enum class WorldVal : uint8_t
{
  test
};

inline std::string_view world_val_to_string(WorldVal v)
{
  switch (v)
  {
  case WorldVal::test:
    return "test";
  }
  return "";
}

inline std::optional<WorldVal> world_val_from_string(std::string_view s)
{
  if (s == "test")
    return WorldVal::test;
  return std::nullopt;
}


LFW_NS_END

#endif // LFW_CORE_DEFINES_WORLDVAL_HPP
