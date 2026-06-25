#ifndef LFW_CORE_WORLD_H
#define LFW_CORE_WORLD_H

#include <map>
#include <string>

#include "lfw-core/core.hpp"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

class Buff;

/// World — 游戏世界（最小化实现，为 Buff 系统提供依赖）
/// TODO: 完整转换 pending
class World
{
public:
  /// 按 ID 查找实体
  Entity *find_entity(const std::string &eid)
  {
    auto it = entity_map.find(eid);
    return it != entity_map.end() ? it->second : nullptr;
  }

  /// TODO: 完整转换后移除 mutable，由 World 统一管理生命周期
  std::map<std::string, Entity *> entity_map;

  /// Buff 注册表（id → Buff*）
  std::map<std::string, Buff *> buffs;
};

LFW_NS_END

#endif
