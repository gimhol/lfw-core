#ifndef LFW_CORE_DEFINES_IBG_LAYER_INFO_HPP
#define LFW_CORE_DEFINES_IBG_LAYER_INFO_HPP

#include <optional>
#include <string>

#include "lfw-core/base/Fields.h"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IBgLayerInfo — 背景层信息
struct IBgLayerInfo
{
  std::optional<std::string> id, name, file;
  std::optional<double> absolute;
  std::optional<int> color;
  double width = 0, height = 0;
  double x = 0, y = 0, z = 0, w = 0, h = 0;
  std::optional<double> loop;
  std::optional<double> cc, c1, c2;
  std::optional<double> offsetAnimX, offsetAnimY;
};

inline const auto &bg_layer_info_fields()
{
  static const auto fs = fields<IBgLayerInfo>(
      field("id", FieldKind::Str, &IBgLayerInfo::id, "ID"),
      field("file", FieldKind::Str, &IBgLayerInfo::file, "文件"),
      field("width", FieldKind::Flt, &IBgLayerInfo::width, "宽"),
      field("height", FieldKind::Flt, &IBgLayerInfo::height, "高"),
      field("x", FieldKind::Flt, &IBgLayerInfo::x, "X"),
      field("y", FieldKind::Flt, &IBgLayerInfo::y, "Y"),
      field("z", FieldKind::Flt, &IBgLayerInfo::z, "Z"),
      field("w", FieldKind::Flt, &IBgLayerInfo::w, "W"),
      field("h", FieldKind::Flt, &IBgLayerInfo::h, "H"),
      field("loop", FieldKind::Flt, &IBgLayerInfo::loop, "循环间隔"));
  return fs;
}

LFW_NS_END

#endif
