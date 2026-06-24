#ifndef LFW_CORE_DEFINES_IBG_LAYER_INFO_HPP
#define LFW_CORE_DEFINES_IBG_LAYER_INFO_HPP

#include <optional>
#include <string>

#include "lfw-core/base/Fields.hpp"

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
      field("id", FieldKind::String, &IBgLayerInfo::id, "ID"),
      field("file", FieldKind::String, &IBgLayerInfo::file, "文件"),
      field("width", FieldKind::Float, &IBgLayerInfo::width, "宽"),
      field("height", FieldKind::Float, &IBgLayerInfo::height, "高"),
      field("x", FieldKind::Float, &IBgLayerInfo::x, "X"),
      field("y", FieldKind::Float, &IBgLayerInfo::y, "Y"),
      field("z", FieldKind::Float, &IBgLayerInfo::z, "Z"),
      field("w", FieldKind::Float, &IBgLayerInfo::w, "W"),
      field("h", FieldKind::Float, &IBgLayerInfo::h, "H"),
      field("loop", FieldKind::Float, &IBgLayerInfo::loop, "循环间隔"));
  return fs;
}

#endif
