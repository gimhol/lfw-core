#include <cassert>
#include <iostream>
#include <string>
#include <any>

#include <nlohmann/json.hpp>

#include "lfw-core/base/Fields.hpp"
#include "lfw-core/defines/INextFrame.hpp"
#include "lfw-core/defines/IQubePair.hpp"

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
    case FieldKind::Flt:
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
    case FieldKind::Str:
      j[e.info.key] = std::any_cast<std::string>(val);
      break;
    case FieldKind::Bool:
      j[e.info.key] = std::any_cast<bool>(val);
      break;
    case FieldKind::Strs:
    {
      auto &arr = std::any_cast<const std::vector<std::string> &>(val);
      j[e.info.key] = arr;
      break;
    }
    case FieldKind::Map:
    {
      if (e.info.value_type == typeid(std::string))
      {
        json obj_map = json::object();
        auto &m = std::any_cast<const std::unordered_map<int, std::string> &>(val);
        for (const auto &[k, v] : m)
          obj_map[std::to_string(k)] = v;
        j[e.info.key] = std::move(obj_map);
      }
      break;
    }
    case FieldKind::Obj:
    {
      // ============================================================
      // FieldKind::Obj 序列化 —— 按 FieldInfo::object_type 分发
      //
      // object_type 在 field() 声明时由 add_entry 自动填充 typeid(U)。
      // 序列化层无需 any_cast 猜测，直接按已知类型 switch。
      //
      // 新增 Object 类型步骤：
      //   1. struct 中用成员指针声明：field("xxx", FieldKind::Obj, &T::xxx, "名称")
      //   2. 在下方添加 else if 分支，匹配 typeid(你的类型)
      // ============================================================
      if (e.info.object_type == typeid(std::optional<TNextFrame>))
      {
        auto &opt = std::any_cast<const std::optional<TNextFrame> &>(val);
        if (opt.has_value())
        {
          json arr = json::array();
          for (const auto &nf : *opt)
            arr.push_back({{"frames", nf.id.has_value() ? static_cast<int>(nf.id->size()) : 0}});
          j[e.info.key] = std::move(arr);
        }
        else
          j[e.info.key] = nullptr;
      }
      else if (e.info.object_type == typeid(std::optional<IQubePair>))
      {
        auto &opt = std::any_cast<const std::optional<IQubePair> &>(val);
        if (opt.has_value())
        {
          j[e.info.key] = {{"left", {{"x", opt->left.x}, {"y", opt->left.y}}},
                           {"right", {{"x", opt->right.x}, {"y", opt->right.y}}}};
        }
        else
          j[e.info.key] = nullptr;
      }
      else
        j[e.info.key] = "<object>";
      break;
    }
    default:
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
    case FieldKind::Flt:
      if (v.is_number_float())
        e.set(obj, v.get<double>());
      else if (v.is_number_integer())
        e.set(obj, static_cast<double>(v.get<int>()));
      break;
    case FieldKind::Str:
      if (v.is_string())
        e.set(obj, v.get<std::string>());
      break;
    case FieldKind::Bool:
      if (v.is_boolean())
        e.set(obj, v.get<bool>());
      break;
    case FieldKind::Strs:
      if (v.is_array())
      {
        std::vector<std::string> arr;
        for (const auto &item : v)
          arr.push_back(item.get<std::string>());
        e.set(obj, arr);
      }
      break;
    case FieldKind::Map:
      if (v.is_object() && e.info.value_type == typeid(std::string))
      {
        std::unordered_map<int, std::string> m;
        for (auto it = v.begin(); it != v.end(); ++it)
          m[std::stoi(it.key())] = it.value().get<std::string>();
        e.set(obj, m);
      }
      break;
    case FieldKind::Obj:
      // 复杂对象：跳过反序列化，由具体类型自行处理
      break;
    default:
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
      field("name", FieldKind::Str, &HeroStats::name, "名称"),
      field("level", FieldKind::Int, &HeroStats::level, "等级"),
      field("hp", FieldKind::Int, &HeroStats::hp, "生命值"),
      field("mp", FieldKind::Int, &HeroStats::mp, "魔法值"),
      field("speed", FieldKind::Flt, &HeroStats::speed, "速度"),
      field("crit_rate", FieldKind::Flt, &HeroStats::crit_rate, "暴击率"),
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
    case FieldKind::Flt:
      prop["type"] = "number";
      break;
    case FieldKind::Str:
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
// Map + Strings 字段测试
// ========================================================================

struct BotConfig
{
  std::string name;
  std::unordered_map<int, std::string> keys;
  std::vector<std::string> tags;
};

static const auto &bot_config_fields()
{
  static const auto fs = fields<BotConfig>(
      field("name", FieldKind::Str, &BotConfig::name, "名称"),
      field("keys", FieldKind::Map, [](const BotConfig &b) -> std::any
            { return b.keys; }, [](BotConfig &b, const std::any &val)
            { b.keys = std::any_cast<std::unordered_map<int, std::string>>(val); }, "按键映射"),
      field("tags", FieldKind::Strs, &BotConfig::tags, "标签"));
  return fs;
}

static void test_json_map_serialize()
{
  const auto &fs = bot_config_fields();
  BotConfig cfg{"BotA", {{1, "A"}, {2, "B"}, {3, "C"}}, {"melee", "ai"}};

  json j = to_json(cfg, fs);
  assert(j["name"] == "BotA");
  assert(j["keys"]["1"] == "A");
  assert(j["keys"]["2"] == "B");
  assert(j["keys"]["3"] == "C");
  assert(j["tags"].size() == 2);
  assert(j["tags"][0] == "melee");
}

static void test_json_map_roundtrip()
{
  const auto &fs = bot_config_fields();
  BotConfig original{"RT", {{10, "X"}, {20, "Y"}}, {"tag1"}};

  json j = to_json(original, fs);
  BotConfig restored;
  from_json(restored, j, fs);

  assert(restored.name == "RT");
  assert(restored.keys.size() == 2);
  assert(restored.keys[10] == "X");
  assert(restored.keys[20] == "Y");
  assert(restored.tags.size() == 1);
  assert(restored.tags[0] == "tag1");
}

static void test_json_map_value_type()
{
  const auto &fs = bot_config_fields();
  auto *e = fs.find("keys");
  assert(e != nullptr);
  assert(e->info.kind == FieldKind::Map);
  assert(e->info.value_type == typeid(std::string));
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
  test_json_map_serialize();
  test_json_map_roundtrip();
  test_json_map_value_type();

  std::cout << "  PASS: JSON Reflection (8 subtests)\n";
}
