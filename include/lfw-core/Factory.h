#ifndef LFW_CORE_FACTORY_H
#define LFW_CORE_FACTORY_H

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "lfw-core/base/Graves.h"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class Buff;
class Entity;
class LFW;
class World;
struct IEntityData;

/// 实体创建器签名: (World*, IEntityData&) → Entity*
using EntityCreator = std::function<Entity *(World *, const IEntityData &)>;

/// 控制器创建器签名: (const std::string &player_id, Entity*) → BaseController*
/// TODO: BaseController 待转换后启用
using CtrlCreator = std::function<void *(const std::string &, Entity *)>;

/// Buff 创建器签名: (LFW*, id, kind) → Buff*
using BuffCreator = std::function<Buff *(LFW *, const std::string &id, const std::string &kind)>;

/// Factory — 实体/控制器/Buff 工厂与对象池
/// 对应 TS Factory
class Factory
{
public:
  static const char *TAG;

  // === 实体池（Graves） ===
  /// 回收实体到对象池
  void recycle_entity(Entity *e);

  /// 从对象池获取实体
  Entity *acquire_entity(int type);

  // === 静态注册 ===
  static void register_entity(int type, EntityCreator creator);
  static void register_ctrl(const std::string &oid, CtrlCreator creator);
  static void register_buff(const std::string &kind, BuffCreator creator);

  // === 创建 ===
  Entity *create_entity(World *world, const IEntityData &data);
  void *create_ctrl(const std::string &oid, const std::string &player_id, Entity *entity);
  Buff *create_buff(const std::string &kind, LFW *lfw, const std::string &id);

private:
  std::map<int, Graves> entity_pools; ///< 按类型分池的对象池
};

LFW_NS_END

#endif
