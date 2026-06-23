#include <cassert>
#include <iostream>
#include <string>
#include <any>

#include <nlohmann/json.hpp>

#include "lfw-core/base/Fields.hpp"

using json = nlohmann::json;

// ============================================================
// 反射序列化/反序列化辅助函数
// ============================================================
template <typename T>
json to_json(const T &obj, const Fields<T> &fs)
{
  json j;
  for (const auto &e : fs.entries())
  {
    auto val = e.get(obj);
    switch (e.info.kind)
    {
    case FieldKind::Int:
      j[e.info.key] = std::any_cast<int>(val);
      break;
    case FieldKind::Float:
    {
      double d = 0;
      try
      {
        d = std::any_cast<double>(val);
      }
      catch (...)
      {
        d = static_cast<double>(std::any_cast<float>(val));
      }
      j[e.info.key] = d;
      break;
    }
    case FieldKind::String:
      j[e.info.key] = std::any_cast<std::string>(val);
      break;
    case FieldKind::Bool:
      j[e.info.key] = std::any_cast<bool>(val);
      break;
    }
  }
  return j;
}

template <typename T>
void from_json(T &obj, const json &j, const Fields<T> &fs)
{
  for (const auto &e : fs.entries())
  {
    const auto &key = e.info.key;
    if (!j.contains(key))
      continue;
    const auto &v = j[key];
    switch (e.info.kind)
    {
    case FieldKind::Int:
      if (v.is_number_integer())
        e.set(obj, v.get<int>());
      break;
    case FieldKind::Float:
      if (v.is_number_float())
        e.set(obj, v.get<double>());
      else if (v.is_number_integer())
        e.set(obj, static_cast<double>(v.get<int>()));
      break;
    case FieldKind::String:
      if (v.is_string())
        e.set(obj, v.get<std::string>());
      break;
    case FieldKind::Bool:
      if (v.is_boolean())
        e.set(obj, v.get<bool>());
      break;
    }
  }
}

// ============================================================
// 测试结构体
// ============================================================
struct HeroStats
{
  std::string name;
  int level = 1;
  int hp = 100;
  int mp = 50;
  float speed = 5.0f;
  double crit_rate = 0.05;
  bool is_ally = true;
};

static const auto &hero_fields()
{
  static const auto fs = fields<HeroStats>(
      field("name", FieldKind::String, &HeroStats::name, "名称"),
      field("level", FieldKind::Int, &HeroStats::level, "等级"),
      field("hp", FieldKind::Int, &HeroStats::hp, "生命值"),
      field("mp", FieldKind::Int, &HeroStats::mp, "魔法值"),
      field("speed", FieldKind::Float, &HeroStats::speed, "速度"),
      field("crit_rate", FieldKind::Float, &HeroStats::crit_rate, "暴击率"),
      field("is_ally", FieldKind::Bool, &HeroStats::is_ally, "友军"));
  return fs;
}

// ============================================================
// 测试
// ============================================================
static void test_json_serialize()
{
  const auto &fs = hero_fields();
  HeroStats hero{"Arthur", 50, 3200, 180, 6.5f, 0.15, true};
  json j = to_json(hero, fs);

  assert(j["name"] == "Arthur");
  assert(j["level"] == 50);
  assert(j["hp"] == 3200);
  assert(j["mp"] == 180);
  assert(j["speed"] == 6.5);
  assert(j["crit_rate"] == 0.15);
  assert(j["is_ally"] == true);
}

static void test_json_deserialize()
{
  const auto &fs = hero_fields();
  json input = R"({"name":"Merlin","level":35,"hp":1800,"mp":420,"speed":4.2,"crit_rate":0.25,"is_ally":false})"_json;

  HeroStats loaded;
  from_json(loaded, input, fs);

  assert(loaded.name == "Merlin");
  assert(loaded.level == 35);
  assert(loaded.hp == 1800);
  assert(loaded.mp == 420);
  assert(loaded.speed == 4.2f);
  assert(loaded.crit_rate == 0.25);
  assert(loaded.is_ally == false);
}

static void test_json_roundtrip()
{
  const auto &fs = hero_fields();
  HeroStats original{"Roundtrip", 42, 999, 888, 7.7f, 0.33, false};

  json j = to_json(original, fs);
  HeroStats restored;
  from_json(restored, j, fs);

  assert(restored.name == original.name);
  assert(restored.level == original.level);
  assert(restored.hp == original.hp);
  assert(restored.mp == original.mp);
  assert(restored.speed == original.speed);
  assert(restored.crit_rate == original.crit_rate);
  assert(restored.is_ally == original.is_ally);
}

static void test_json_partial_update()
{
  const auto &fs = hero_fields();
  json patch = R"({"hp":9999,"level":99})"_json;

  HeroStats updated{"初始", 1, 100, 50, 5.0f, 0.05, true};
  from_json(updated, patch, fs);

  // patched fields
  assert(updated.hp == 9999);
  assert(updated.level == 99);
  // unchanged fields
  assert(updated.name == "初始");
  assert(updated.mp == 50);
}

static void test_json_schema_generation()
{
  const auto &fs = hero_fields();
  json schema;
  schema["type"] = "object";
  schema["properties"] = json::object();

  for (const auto &e : fs.entries())
  {
    json prop;
    switch (e.info.kind)
    {
    case FieldKind::Int:
      prop["type"] = "integer";
      break;
    case FieldKind::Float:
      prop["type"] = "number";
      break;
    case FieldKind::String:
      prop["type"] = "string";
      break;
    case FieldKind::Bool:
      prop["type"] = "boolean";
      break;
    }
    schema["properties"][e.info.key] = std::move(prop);
  }

  assert(schema["properties"]["name"]["type"] == "string");
  assert(schema["properties"]["level"]["type"] == "integer");
  assert(schema["properties"]["hp"]["type"] == "integer");
  assert(schema["properties"]["is_ally"]["type"] == "boolean");
}

// ========================================================================
void run_json_reflection_tests()
{
  std::cout << "  --- JSON Reflection ---\n";

  test_json_serialize();
  test_json_deserialize();
  test_json_roundtrip();
  test_json_partial_update();
  test_json_schema_generation();

  std::cout << "  PASS: JSON Reflection (5 subtests)\n";
}
