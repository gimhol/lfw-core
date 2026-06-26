#ifndef LFW_CORE_DEFINES_IBPOINT_INFO_HPP
#define LFW_CORE_DEFINES_IBPOINT_INFO_HPP

#include <optional>

#include "IQubePair.hpp"
#include "lfw-core/base/Fields.h"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IBpointInfo — 出血点信息
struct IBpointInfo
{
  double x = 0;
  double y = 0;
  std::optional<double> z;
  std::optional<double> r;
  std::optional<IQubePair> indicator_info;
};

inline const auto &bpoint_info_fields()
{
  static const auto fs = fields<IBpointInfo>(
      field("x", FieldKind::Flt, &IBpointInfo::x, "X"),
      field("y", FieldKind::Flt, &IBpointInfo::y, "Y"),
      field("z", FieldKind::Flt, &IBpointInfo::z, "Z"),
      field("r", FieldKind::Flt, &IBpointInfo::r, "R"));
  return fs;
}

LFW_NS_END

#endif
