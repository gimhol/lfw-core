#ifndef LFW_CORE_DEFINES_IBOT_DATA_HPP
#define LFW_CORE_DEFINES_IBOT_DATA_HPP

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "IBotAction.hpp"
#include "IBotDataSet.hpp"
#include "lfw-core/base/Fields.h"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IBotData — Bot 数据
struct IBotData
{
  /// Bot 数据 ID
  std::string id;

  /// 角色 ID
  std::string oid;

  /// Bot 动作表：动作名 → 动作定义
  std::map<std::string, IBotAction> actions;

  /// 帧状态 → 动作列表（当 bot 的帧状态符合时触发对应动作）
  std::optional<std::map<std::string, std::vector<std::string>>> states;

  /// 帧 ID → 动作列表（当 bot 的帧 ID 符合时触发对应动作）
  std::optional<std::map<std::string, std::vector<std::string>>> frames;

  /// Bot 数据集（AI 参数）
  std::optional<IBotDataSet> dataset;
};

inline const auto &bot_data_fields()
{
  static const auto fs = fields<IBotData>(
      field("id", FieldKind::Str, &IBotData::id, "ID"),
      field("oid", FieldKind::Str, &IBotData::oid, "角色ID"),
      field("actions", FieldKind::Map, [](const IBotData &b) -> std::any
            { return b.actions; }, [](IBotData &b, const std::any &val)
            { b.actions = std::any_cast<std::map<std::string, IBotAction>>(val); }, "动作表"),
      field("states", FieldKind::Map, [](const IBotData &b) -> std::any
            { return b.states; }, [](IBotData &b, const std::any &val)
            { b.states = std::any_cast<std::optional<std::map<std::string, std::vector<std::string>>>>(val); }, "帧状态-动作列表"),
      field("frames", FieldKind::Map, [](const IBotData &b) -> std::any
            { return b.frames; }, [](IBotData &b, const std::any &val)
            { b.frames = std::any_cast<std::optional<std::map<std::string, std::vector<std::string>>>>(val); }, "帧ID-动作列表"),
      field("dataset", FieldKind::Map, [](const IBotData &b) -> std::any
            { return b.dataset; }, [](IBotData &b, const std::any &val)
            { b.dataset = std::any_cast<std::optional<IBotDataSet>>(val); }, "Bot数据集"));
  return fs;
}

LFW_NS_END

#endif
