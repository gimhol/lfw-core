#include <cassert>
#include <iostream>
#include <string>
#include <any>

#include "lfw-core/base/Fields.hpp"

// ========================================================================
// Fields 测试
// ========================================================================

struct TestConfig
{
  std::string name;
  int hp = 100;
  float speed = 5.0f;
  double crit = 0.05;
  bool active = true;
};

static const auto &test_fields()
{
  static const auto fs = fields<TestConfig>(
      field("name", FieldKind::String, &TestConfig::name, "名称"),
      field("hp", FieldKind::Int, &TestConfig::hp, "生命"),
      field("speed", FieldKind::Float, &TestConfig::speed, "速度"),
      field("crit", FieldKind::Float, &TestConfig::crit, "暴击率"),
      field("active", FieldKind::Bool, &TestConfig::active, "激活"));
  return fs;
}

static void test_fields_entries_count()
{
  const auto &fs = test_fields();
  assert(fs.size() == 5);
}

static void test_fields_get()
{
  const auto &fs = test_fields();
  TestConfig cfg;
  cfg.name = "Hero";
  cfg.hp = 80;

  auto name = fs.get(cfg, "name");
  assert(std::any_cast<std::string>(name) == "Hero");

  auto hp = fs.get(cfg, "hp");
  assert(std::any_cast<int>(hp) == 80);
}

static void test_fields_set()
{
  const auto &fs = test_fields();
  TestConfig cfg;

  fs.set(cfg, "hp", std::any(999));
  assert(cfg.hp == 999);

  fs.set(cfg, "speed", std::any(10.5f));
  assert(cfg.speed == 10.5f);

  fs.set(cfg, "active", std::any(false));
  assert(!cfg.active);

  fs.set(cfg, "name", std::any(std::string("Warrior")));
  assert(cfg.name == "Warrior");
}

void run_fields_tests()
{
  std::cout << "  --- Fields ---\n";

  test_fields_entries_count();
  test_fields_get();
  test_fields_set();

  std::cout << "  PASS: Fields (3 subtests)\n";
}
