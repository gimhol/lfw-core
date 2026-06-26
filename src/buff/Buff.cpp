#include "lfw-core/buff/Buff.h"

LFW_NS_BEGIN

const char *Buff::KIND = "";

Buff::Buff(LFW *lfw, std::string id, std::string kind)
    : lfw(lfw), world(lfw ? &lfw->world() : nullptr),
      id(std::move(id)), kind(std::move(kind))
{
  _lifetime.set_range(0, 1).set_lifes(1);
}

bool Buff::dead() const { return _lifetime.remains() == 0; }
double Buff::lifetime() const { return _lifetime.value(); }
void Buff::set_lifetime(double v) { _lifetime.set_value(v); }
double Buff::duration() const { return _lifetime.max(); }
void Buff::set_duration(double v) { _lifetime.set_max(v); }
int Buff::ticks() const { return static_cast<int>(_ticker.max()); }
void Buff::set_ticks(int v) { _ticker.set_max(v); }
const std::vector<std::string> &Buff::victims() const { return _victims; }
const std::string &Buff::attacker_id() const { return _attacker_id; }
void Buff::init() {}

Entity *Buff::attacker() const
{
  if (_attacker_id.empty() || !world)
    return nullptr;
  return world->find_entity(_attacker_id);
}

void Buff::set_attacker(const std::string &attacker_id) { _attacker_id = attacker_id; }

void Buff::set_victims(const std::vector<std::string> &ids)
{
  for (const auto &vid : _victims)
  {
    if (auto *e = world ? world->find_entity(vid) : nullptr)
    {
      // TODO: e->buffs 清除引用，等 Entity 添加 buffs 成员
    }
  }
  _victims.clear();
  add_victims(ids);
}

void Buff::add_victims(const std::vector<std::string> &ids)
{
  for (const auto &vid : ids)
  {
    if (std::find(_victims.begin(), _victims.end(), vid) != _victims.end())
      continue;
    _victims.push_back(vid);
  }
}

void Buff::del_victims(const std::vector<std::string> &ids)
{
  for (const auto &vid : ids)
    del_victim(vid);
}

bool Buff::del_victim(const std::string &victim_id)
{
  bool found = false;
  std::size_t slow = 0;
  for (std::size_t fast = 0; fast < _victims.size(); ++fast)
  {
    if (slow < fast)
      _victims[slow] = _victims[fast];
    if (_victims[fast] == victim_id)
    {
      found = true;
      continue;
    }
    ++slow;
  }
  _victims.resize(slow);
  return found;
}

BuffResult Buff::on_tick(Entity *, Entity *) { return BuffResult::Keep; }
BuffResult Buff::on_update(Entity *, Entity *) { return BuffResult::Keep; }
BuffResult Buff::on_end(Entity *, Entity *) { return BuffResult::Keep; }

void Buff::update(double d)
{
  Entity *att = attacker();

  if (_ticker.add(d))
    loop(&Buff::on_tick, att);

  if (_lifetime.add())
    loop(&Buff::on_end, att);

  loop(&Buff::on_update, att);
}

void Buff::loop(BuffResult (Buff::*fn)(Entity *, Entity *), Entity *attacker_ptr)
{
  std::size_t slow = 0;
  for (std::size_t fast = 0; fast < _victims.size(); ++fast)
  {
    if (slow != fast)
      _victims[slow] = _victims[fast];

    Entity *victim = world ? world->find_entity(_victims[fast]) : nullptr;
    BuffResult ret = (this->*fn)(attacker_ptr, victim);

    if (ret == BuffResult::Del)
      continue;
    ++slow;
  }
  _victims.resize(slow);
}

void Buff::mount()
{
  if (_mounted)
    return;
  _mounted = true;
  if (world)
    world->buffs[id] = this;
}

void Buff::unmount()
{
  if (!_mounted)
    return;
  _mounted = false;
  del_victims(_victims);
  if (world)
    world->buffs.erase(id);
}

LFW_NS_END
