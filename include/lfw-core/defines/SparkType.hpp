#ifndef LFW_CORE_DEFINES_SPARKTYPE_HPP
#define LFW_CORE_DEFINES_SPARKTYPE_HPP

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class SparkType : uint8_t
{
  BrokenDefend,
  CriticalHit,
  SilentCriticalHit,
  DefendHit,
  Hit,
  HitFall,
  SilentHit,
  Bleed,
  BleedFall,
  CriticalBleed
};

inline std::string_view spark_type_to_string(SparkType v)
{
  switch (v)
  {
  case SparkType::BrokenDefend:
    return "broken_defend";
  case SparkType::CriticalHit:
    return "critical_hit";
  case SparkType::SilentCriticalHit:
    return "silent_critical_hit";
  case SparkType::DefendHit:
    return "defend_hit";
  case SparkType::Hit:
    return "hit";
  case SparkType::HitFall:
    return "hit_fall";
  case SparkType::SilentHit:
    return "silent_hit";
  case SparkType::Bleed:
    return "bleed";
  case SparkType::BleedFall:
    return "bleed_fall";
  case SparkType::CriticalBleed:
    return "critical_bleed";
  }
  return "";
}

inline std::optional<SparkType> spark_type_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, SparkType> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(SparkType::CriticalBleed); ++i)
    {
      auto v = static_cast<SparkType>(i);
      r[spark_type_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}


LFW_NS_END

#endif // LFW_CORE_DEFINES_SPARKTYPE_HPP
