#ifndef LFW_CORE_DEFINES_CHASELOST_HPP
#define LFW_CORE_DEFINES_CHASELOST_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

/* ---- ChaseLost ---- */
#define ENUM_ITEMS(X)                   \
  X(ChaseLost, Hover, "hover", "", = 1) \
  X(ChaseLost, Leave, "leave", "", = 2) \
  X(ChaseLost, End, "end", "", = 4)

enum class ChaseLost : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(ChaseLostStringMap, ENUM_ITEMS, ChaseLost)
GEN_ENUM_NAME_MAP(ChaseLostNameMap, ENUM_ITEMS, ChaseLost)
GEN_ENUM_DESC_MAP(ChaseLostDescMap, ENUM_ITEMS, ChaseLost)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(chase_lost_to_string, chase_lost_from_string, ChaseLost, ChaseLostStringMap)
DEFINE_ENUM_STR_CONVERTERS(chase_lost_to_name, chase_lost_from_name, ChaseLost, ChaseLostNameMap)
DEFINE_ENUM_TO_STR(chase_lost_to_desc, ChaseLost, ChaseLostDescMap)

/* ---- ChaseStrategy ---- */
#define ENUM_ITEMS(X)                           \
  X(ChaseStrategy, Default, "default", "", = 0) \
  X(ChaseStrategy, TillLost, "till_lost", "", = 1)

enum class ChaseStrategy : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(ChaseStrategyStringMap, ENUM_ITEMS, ChaseStrategy)
GEN_ENUM_NAME_MAP(ChaseStrategyNameMap, ENUM_ITEMS, ChaseStrategy)
GEN_ENUM_DESC_MAP(ChaseStrategyDescMap, ENUM_ITEMS, ChaseStrategy)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(chase_strategy_to_string, chase_strategy_from_string, ChaseStrategy, ChaseStrategyStringMap)
DEFINE_ENUM_STR_CONVERTERS(chase_strategy_to_name, chase_strategy_from_name, ChaseStrategy, ChaseStrategyNameMap)
DEFINE_ENUM_TO_STR(chase_strategy_to_desc, ChaseStrategy, ChaseStrategyDescMap)

#endif // LFW_CORE_DEFINES_CHASELOST_HPP
