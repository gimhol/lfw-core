#ifndef LFW_CORE_DEFINES_ILEGACY_PICTURE_INFO_HPP
#define LFW_CORE_DEFINES_ILEGACY_PICTURE_INFO_HPP

#include "IPictureInfo.hpp"
#include "lfw-core/base/Fields.h"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// ILegacyPictureInfo — 旧版实体图片信息（继承 IPictureInfo）
struct ILegacyPictureInfo : IPictureInfo
{
  /// 行数
  int row = 0;

  /// 列数
  int col = 0;

  /// 格宽
  int cell_w = 0;

  /// 格高
  int cell_h = 0;
};

inline const auto &legacy_picture_info_fields()
{
  static const auto fs = fields<ILegacyPictureInfo>(
      field("id", FieldKind::Str, &ILegacyPictureInfo::id, "图片ID"),
      field("path", FieldKind::Str, &ILegacyPictureInfo::path, "路径"),
      field("variants", FieldKind::Strs, &ILegacyPictureInfo::variants, "变体"),
      field("row", FieldKind::Int, &ILegacyPictureInfo::row, "行数"),
      field("col", FieldKind::Int, &ILegacyPictureInfo::col, "列数"),
      field("cell_w", FieldKind::Int, &ILegacyPictureInfo::cell_w, "格宽"),
      field("cell_h", FieldKind::Int, &ILegacyPictureInfo::cell_h, "格高"));
  return fs;
}

LFW_NS_END

#endif
