#ifndef LFW_CORE_DEFINES_IPICTURE_INFO_HPP
#define LFW_CORE_DEFINES_IPICTURE_INFO_HPP

#include <optional>
#include <string>
#include <vector>

#include "lfw-core/base/Fields.h"

/// IPictureInfo — 图片信息
struct IPictureInfo
{
  std::string id;
  std::string path;
  std::optional<std::vector<std::string>> variants;
  std::optional<int> row, col, cell_w;
};

inline const auto &picture_info_fields()
{
  static const auto fs = fields<IPictureInfo>(
      field("id", FieldKind::Str, &IPictureInfo::id, "ID"),
      field("path", FieldKind::Str, &IPictureInfo::path, "路径"),
      field("row", FieldKind::Int, &IPictureInfo::row, "行数"),
      field("col", FieldKind::Int, &IPictureInfo::col, "列数"),
      field("cell_w", FieldKind::Int, &IPictureInfo::cell_w, "格宽"));
  return fs;
}

#endif
