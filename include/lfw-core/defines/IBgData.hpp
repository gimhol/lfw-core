#ifndef LFW_CORE_DEFINES_IBGDATA_HPP
#define LFW_CORE_DEFINES_IBGDATA_HPP

#include <optional>
#include <string>
#include <vector>

#include "IBgInfo.hpp"
#include "IBgLayerInfo.hpp"
#include "IWorldDataset.hpp"
#include "lfw-core/base/Fields.hpp"

/// IBgData — 背景数据
struct IBgData
{
  std::string id;
  std::optional<std::string> alias_id;
  /// 类型固定为 "background"
  std::string type = "background";
  IBgInfo base;
  std::optional<IWorldDataset> dataset;
  std::vector<IBgLayerInfo> layers;
};

inline const auto &bg_data_fields()
{
  static const auto fs = fields<IBgData>(
      field("id", FieldKind::Str, &IBgData::id, "ID"),
      field("alias_id", FieldKind::Str, &IBgData::alias_id, "别名ID"),
      field("type", FieldKind::Str, &IBgData::type, "类型"),
      field("base", FieldKind::Map, // 嵌套对象，自定义序列化
            [](const IBgData &b) -> std::any
            { return b.base; }, [](IBgData &b, const std::any &val)
            { b.base = std::any_cast<IBgInfo>(val); }, "基础信息"),
      field("dataset", FieldKind::Map, [](const IBgData &b) -> std::any
            { return b.dataset; }, [](IBgData &b, const std::any &val)
            { b.dataset = std::any_cast<std::optional<IWorldDataset>>(val); }, "数据集"),
      field("layers", FieldKind::Map, [](const IBgData &b) -> std::any
            { return b.layers; }, [](IBgData &b, const std::any &val)
            { b.layers = std::any_cast<std::vector<IBgLayerInfo>>(val); }, "背景层"));
  return fs;
}

#endif
