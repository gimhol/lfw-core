#include "lfw-core/Factory.h"
#include "lfw-core/World.h"
#include "lfw-core/buff/Buff.h"
#include "lfw-core/ditto/Ditto.h"
#include "lfw-core/defines/IEntityData.hpp"
#include "lfw-core/entity/Entity.h"

LFW_NS_BEGIN

const char *Factory::TAG = "Factory";

// ============================================================
// 静态注册表
// ============================================================
static std::map<int, EntityCreator> &entity_creators()
{
  static std::map<int, EntityCreator> m;
  return m;
}

static std::map<std::string, CtrlCreator> &ctrl_creators()
{
  static std::map<std::string, CtrlCreator> m;
  return m;
}

static std::map<std::string, BuffCreator> &buff_creators()
{
  static std::map<std::string, BuffCreator> m;
  return m;
}

// ============================================================
// 实体池
// ============================================================
void Factory::recycle_entity(Entity *e)
{
  if (!e)
    return;
  int t = static_cast<int>(e->type());
  entity_pools[t].add(e);
}

Entity *Factory::acquire_entity(int type)
{
  auto it = entity_pools.find(type);
  if (it == entity_pools.end())
    return nullptr;
  return static_cast<Entity *>(it->second.take());
}

// ============================================================
// 静态注册
// ============================================================
void Factory::register_entity(int type, EntityCreator creator)
{
  auto &m = entity_creators();
  if (m.find(type) != m.end())
    Ditto::warn(std::string("[") + TAG + "::register_entity] type already exists");
  m[type] = std::move(creator);
}

void Factory::register_ctrl(const std::string &oid, CtrlCreator creator)
{
  auto &m = ctrl_creators();
  if (m.find(oid) != m.end())
    Ditto::warn(std::string("[") + TAG + "::register_ctrl] oid already exists");
  m[oid] = std::move(creator);
}

void Factory::register_buff(const std::string &kind, BuffCreator creator)
{
  auto &m = buff_creators();
  if (m.find(kind) != m.end())
    Ditto::warn(std::string("[") + TAG + "::register_buff] kind already exists");
  m[kind] = std::move(creator);
}

// ============================================================
// 创建方法
// ============================================================
Entity *Factory::create_entity(World *world, const IEntityData &data)
{
  auto &m = entity_creators();
  int t = static_cast<int>(data.type);
  auto it = m.find(t);
  if (it == m.end())
    return nullptr;
  return it->second(world, data);
}

void *Factory::create_ctrl(const std::string &oid, const std::string &player_id, Entity *entity)
{
  auto &m = ctrl_creators();
  auto it = m.find(oid);
  if (it == m.end())
    return nullptr;
  return it->second(player_id, entity);
}

Buff *Factory::create_buff(const std::string &kind, LFW *lfw, const std::string &id)
{
  auto &m = buff_creators();
  auto it = m.find(kind);
  if (it == m.end())
    return nullptr;
  auto *ret = it->second(lfw, id, kind);
  if (ret)
    ret->init();
  return ret;
}

LFW_NS_END
