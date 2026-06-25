#ifndef LFW_CORE_DEFINES_IBOUNDING_HPP
#define LFW_CORE_DEFINES_IBOUNDING_HPP

#include "lfw-core/base/Fields.hpp"

/// IBounding — 包围盒（6 面）
struct IBounding
{
  double left = 0;
  double right = 0;
  double top = 0;
  double bottom = 0;
  double near = 0;
  double far = 0;
};

inline const auto &bounding_fields()
{
  static const auto fs = fields<IBounding>(
      field("left", FieldKind::Float, &IBounding::left, "左"),
      field("right", FieldKind::Float, &IBounding::right, "右"),
      field("top", FieldKind::Float, &IBounding::top, "上"),
      field("bottom", FieldKind::Float, &IBounding::bottom, "下"),
      field("near", FieldKind::Float, &IBounding::near, "近"),
      field("far", FieldKind::Float, &IBounding::far, "远"));
  return fs;
}

#endif // LFW_CORE_DEFINES_IBOUNDING_HPP
