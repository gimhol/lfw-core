#ifndef LFW_CORE_DEFINES_IENTITY_DATA_HPP
#define LFW_CORE_DEFINES_IENTITY_DATA_HPP

#include <map>
#include <optional>
#include <string>

#include "EntityType.hpp"
#include "IBaseData.hpp"
#include "IBdyInfo.hpp"
#include "IEntityInfo.hpp"
#include "IFrameIndexes.hpp"
#include "IFrameInfo.hpp"
#include "IItrInfo.hpp"
#include "INextFrame.hpp"

/// TItrPrefabs — ITR 预制件表
using TItrPrefabs = std::map<std::string, IItrInfo>;

/// TBdyPrefabs — BDY 预制件表
using TBdyPrefabs = std::map<std::string, IBdyInfo>;

/// IEntityData — 核心实体数据
/// 对应 TS 的 IEntityData extends IBaseData<IEntityInfo>
struct IEntityData : IBaseData
{
  /// 角色基础信息
  IEntityInfo base;

  /// 角色死亡时的帧过渡
  std::optional<INextFrame> on_dead;

  /// MP 耗尽时的帧过渡
  std::optional<INextFrame> on_exhaustion;

  /// 帧索引表
  std::optional<IFrameIndexes> indexes;

  /// BDY 预制件表
  std::optional<TBdyPrefabs> bdy_prefabs;

  /// ITR 预制件表
  std::optional<TItrPrefabs> itr_prefabs;

  /// 帧表：帧 ID → 帧信息
  std::map<std::string, IFrameInfo> frames;

  /// 数据是否已处理（加载后预处理标记）
  std::optional<bool> processed;
};

#endif
