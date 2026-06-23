#include <cstdio>
#include <string>

#include <nlohmann/json.hpp>

#include "lfw-core/base/Fields.hpp"

using json = nlohmann::json;

// ============================================================
// 通过 Fields<T> 反射将任意结构体序列化为 JSON
// ============================================================
template <typename T>
json to_json(const T &obj, const Fields<T> &fs)
{
  json j;
  for (const auto &e : fs.entries())
  {
    auto val = e.get(obj);
    const auto &key = e.info.key;

    switch (e.info.kind)
    {
    case FieldKind::Int:
      j[key] = std::any_cast<int>(val);
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
      j[key] = d;
      break;
    }
    case FieldKind::String:
      j[key] = std::any_cast<std::string>(val);
      break;
    case FieldKind::Bool:
      j[key] = std::any_cast<bool>(val);
      break;
    }
  }
  return j;
}

// ============================================================
// 通过 Fields<T> 反射从 JSON 反序列化
// ============================================================
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
// 示例结构体
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

// 字段定义
static const auto &hero_fields()
{
  static const auto fs = fields<HeroStats>(
      field("name", FieldKind::String, &HeroStats::name, "名称"),
      field("level", FieldKind::Int, &HeroStats::level, "等级").min(1).max(99),
      field("hp", FieldKind::Int, &HeroStats::hp, "生命值").min(0).max(99999),
      field("mp", FieldKind::Int, &HeroStats::mp, "魔法值").min(0).max(99999),
      field("speed", FieldKind::Float, &HeroStats::speed, "速度").min(0).max(100),
      field("crit_rate", FieldKind::Float, &HeroStats::crit_rate, "暴击率").min(0).max(1).step(0.01),
      field("is_ally", FieldKind::Bool, &HeroStats::is_ally, "友军"));
  return fs;
}

// ============================================================
// 示例运行
// ============================================================
void run_json_reflection_demo()
{
  std::printf("--- JSON 反射序列化/反序列化示例 ---\n\n");

  const auto &fs = hero_fields();

  // ① 序列化
  std::printf("  第 1 步: 结构体 → JSON\n");
  HeroStats hero{"亚瑟", 50, 3200, 180, 6.5f, 0.15, true};
  json j = to_json(hero, fs);
  std::printf("  %s\n\n", j.dump(2).c_str());

  // ② 从 JSON 反序列化
  std::printf("  第 2 步: JSON → 结构体\n");
  json input = R"({
    "name": "梅林",
    "level": 35,
    "hp": 1800,
    "mp": 420,
    "speed": 4.2,
    "crit_rate": 0.25,
    "is_ally": false
  })"_json;

  HeroStats loaded;
  from_json(loaded, input, fs);
  std::printf("  name=%s  level=%d  hp=%d  mp=%d\n",
              loaded.name.c_str(), loaded.level, loaded.hp, loaded.mp);
  std::printf("  speed=%.1f  crit_rate=%.2f  is_ally=%s\n\n",
              loaded.speed, loaded.crit_rate, loaded.is_ally ? "true" : "false");

  // ③ 部分更新（JSON 只包含部分字段）
  std::printf("  第 3 步: 部分字段更新\n");
  json patch = R"({ "hp": 9999, "level": 99 })"_json;

  HeroStats updated{"初始", 1, 100, 50, 5.0f, 0.05, true};
  from_json(updated, patch, fs);
  std::printf("  name=%s  level=%d  hp=%d  mp=%d\n",
              updated.name.c_str(), updated.level, updated.hp, updated.mp);
  std::printf("  （name/mp/speed/crit_rate/is_ally 保持不变）\n\n");

  // ④ 遍历字段元数据生成 JSON Schema
  std::printf("  第 4 步: 从字段元数据生成 JSON Schema\n");
  json schema;
  schema["$schema"] = "https://json-schema.org/draft-07/schema#";
  schema["title"] = "HeroStats";
  schema["type"] = "object";
  schema["properties"] = json::object();

  for (const auto &e : fs.entries())
  {
    const auto &info = e.info;
    json prop;
    prop["description"] = info.desc.empty() ? info.title : info.desc;

    switch (info.kind)
    {
    case FieldKind::Int:
      prop["type"] = "integer";
      if (info.has_min)
        prop["minimum"] = static_cast<long long>(info.min_val);
      if (info.has_max)
        prop["maximum"] = static_cast<long long>(info.max_val);
      break;
    case FieldKind::Float:
      prop["type"] = "number";
      if (info.has_min)
        prop["minimum"] = info.min_val;
      if (info.has_max)
        prop["maximum"] = info.max_val;
      break;
    case FieldKind::String:
      prop["type"] = "string";
      if (info.max_length > 0)
        prop["maxLength"] = info.max_length;
      break;
    case FieldKind::Bool:
      prop["type"] = "boolean";
      break;
    }
    schema["properties"][info.key] = std::move(prop);
  }
  std::printf("  %s\n", schema.dump(2).c_str());

  std::printf("\n--- JSON 反射示例结束 ---\n\n");
}
