#ifndef LFW_CORE_BUFF_BUFF_H
#define LFW_CORE_BUFF_BUFF_H

#include <string>
#include <vector>

#include "lfw-core/LFW.hpp"
#include "lfw-core/World.h"
#include "lfw-core/core.hpp"
#include "lfw-core/entity/Entity.h"
#include "lfw-core/utils/math/Times.hpp"

LFW_NS_BEGIN

enum class BuffResult
{
  Keep,
  Del
};

class Buff
{
public:
  static const char *KIND;

  LFW *lfw = nullptr;
  World *world = nullptr;
  const std::string id;
  const std::string kind;
  int level = 0;

  bool dead() const { return _lifetime.remains() == 0; }
  double lifetime() const { return _lifetime.value(); }
  void set_lifetime(double v) { _lifetime.set_value(v); }
  double duration() const { return _lifetime.max(); }
  void set_duration(double v) { _lifetime.set_max(v); }

  int ticks() const { return static_cast<int>(_ticker.max()); }
  void set_ticks(int v) { _ticker.set_max(v); }

  const std::vector<std::string> &victims() const { return _victims; }
  const std::string &attacker_id() const { return _attacker_id; }
  Entity *attacker() const;

  Buff(LFW *lfw_ptr, std::string id_val, std::string kind_val);
  virtual ~Buff() = default;

  virtual void init() {}
  virtual BuffResult on_tick(Entity *attacker_ptr, Entity *victim_ptr);
  virtual BuffResult on_update(Entity *attacker_ptr, Entity *victim_ptr);
  virtual BuffResult on_end(Entity *attacker_ptr, Entity *victim_ptr);

  void set_attacker(const std::string &attacker_id_val);
  void set_victims(const std::vector<std::string> &ids);
  void add_victims(const std::vector<std::string> &ids);
  void del_victims(const std::vector<std::string> &ids);

  void update(double d);
  void mount();
  void unmount();

protected:
  bool _mounted = false;
  std::string _attacker_id;
  std::vector<std::string> _victims;
  Times _ticker;
  Times _lifetime{0, 1};

  void loop(BuffResult (Buff::*fn)(Entity *, Entity *), Entity *attacker_ptr);
  bool del_victim(const std::string &victim_id);
};

LFW_NS_END

#endif
