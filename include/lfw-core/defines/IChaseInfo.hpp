#ifndef LFW_CORE_DEFINES_ICHASE_INFO_HPP
#define LFW_CORE_DEFINES_ICHASE_INFO_HPP

#include <optional>

#include "HitFlag.hpp"
#include "lfw-core/base/Fields.hpp"

/// IChaseInfo — 追踪信息
struct IChaseInfo
{
  std::optional<int> strategy;
  int flag = 0;
  int lost = 0;
  std::optional<double> oy;
};

inline const auto &chase_info_fields()
{
  static const auto fs = fields<IChaseInfo>(
      field("stratedy", FieldKind::Int, &IChaseInfo::strategy, "策略"),
      field("flag", FieldKind::Int, &IChaseInfo::flag, "标志"),
      field("lost", FieldKind::Int, &IChaseInfo::lost, "丢失行为"),
      field("oy", FieldKind::Float, &IChaseInfo::oy, "OY偏移"));
  return fs;
}

#endif
