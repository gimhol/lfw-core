#ifndef LFW_CORE_DEFINES_IFRAME_PICTURE_INFO_HPP
#define LFW_CORE_DEFINES_IFRAME_PICTURE_INFO_HPP

#include <string>

#include "lfw-core/base/Fields.hpp"

/// IFramePictureInfo — 帧图片裁剪信息
struct IFramePictureInfo
{
  std::string tex;
  double x = 0;
  double y = 0;
  double w = 0;
  double h = 0;
};

inline const auto &frame_picture_info_fields()
{
  static const auto fs = fields<IFramePictureInfo>(
      field("tex", FieldKind::String, &IFramePictureInfo::tex, "图片ID"),
      field("x", FieldKind::Float, &IFramePictureInfo::x, "X"),
      field("y", FieldKind::Float, &IFramePictureInfo::y, "Y"),
      field("w", FieldKind::Float, &IFramePictureInfo::w, "宽"),
      field("h", FieldKind::Float, &IFramePictureInfo::h, "高"));
  return fs;
}

#endif
