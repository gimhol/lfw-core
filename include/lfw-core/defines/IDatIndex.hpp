#ifndef LFW_CORE_DEFINES_IDAT_INDEX_HPP
#define LFW_CORE_DEFINES_IDAT_INDEX_HPP

#include <optional>
#include <string>
#include <vector>

#include "lfw-core/base/Fields.hpp"

/// IDatIndex — 数据索引
struct IDatIndex
{
  std::string id;
  std::optional<std::string> type;
  std::string file;
  std::optional<std::string> hash;
  std::optional<std::string> alias;
  std::optional<std::vector<std::string>> groups;
  std::optional<std::string> skipped;
  std::optional<std::string> bot;
};

inline const auto &dat_index_fields()
{
  static const auto fs = fields<IDatIndex>(
      field("id", FieldKind::String, &IDatIndex::id, "ID"),
      field("type", FieldKind::String, &IDatIndex::type, "数据类型"),
      field("file", FieldKind::String, &IDatIndex::file, "文件"),
      field("hash", FieldKind::String, &IDatIndex::hash, "哈希"),
      field("alias", FieldKind::String, &IDatIndex::alias, "别名"),
      field("groups", FieldKind::Strings, &IDatIndex::groups, "分组"),
      field("skipped", FieldKind::String, &IDatIndex::skipped, "跳过"),
      field("bot", FieldKind::String, &IDatIndex::bot, "Bot"));
  return fs;
}

/// ITempDatIndex — 临时数据索引（继承 IDatIndex + src）
struct ITempDatIndex : IDatIndex
{
  std::string src;
};

#endif // LFW_CORE_DEFINES_IDAT_INDEX_HPP
