#ifndef LFW_CORE_DEFINES_IDAT_CONTEXT_HPP
#define LFW_CORE_DEFINES_IDAT_CONTEXT_HPP

#include <map>
#include <optional>
#include <string>

#include "IDatIndex.hpp"
#include "IEntityData.hpp"
#include "IEntityInfo.hpp"
#include "IFrameInfo.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IDatContext — 数据上下文（加载/处理过程中的完整数据包裹）
struct IDatContext
{
  /// 数据索引
  IDatIndex index;

  /// 实体基础信息
  IEntityInfo base;

  /// 原始数据文本
  std::string text;

  /// 帧表：帧 ID → 帧信息
  std::map<std::string, IFrameInfo> frames;

  /// 解析后的实体数据（可能为空）
  std::optional<IEntityData> data;
};

LFW_NS_END

#endif
