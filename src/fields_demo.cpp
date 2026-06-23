#include <cstdio>
#include <string>
#include <vector>

#include "lfw-core/base/Fields.hpp"

// ============================================================
// 示例结构体
// ============================================================
struct PlayerConfig
{
  std::string name;
  int hp = 100;
  int mp = 50;
  float speed = 5.0f;
  double damage_mult = 1.0;
  bool god_mode = false;
};

// ============================================================
// 定义字段元数据（编译期构建，运行期可用）
// ============================================================
static const auto &player_fields()
{
  static const auto fs = fields<PlayerConfig>(
      field("name", FieldKind::String, &PlayerConfig::name, "名称")
          .desc("玩家名称")
          .max_length(16),
      field("hp", FieldKind::Int, &PlayerConfig::hp, "生命值")
          .desc("当前生命值")
          .min(0)
          .max(9999),
      field("mp", FieldKind::Int, &PlayerConfig::mp, "魔法值")
          .desc("当前魔法值")
          .min(0)
          .max(9999),
      field("speed", FieldKind::Float, &PlayerConfig::speed, "速度")
          .desc("移动速度")
          .min(0)
          .max(100)
          .step(0.1),
      field("damage_mult", FieldKind::Float, &PlayerConfig::damage_mult, "伤害倍率")
          .desc("伤害倍率")
          .min(0)
          .max(10)
          .step(0.01),
      field("god_mode", FieldKind::Bool, &PlayerConfig::god_mode, "无敌模式")
          .desc("开启后不会受到伤害"));
  return fs;
}

// ============================================================
// 示例运行
// ============================================================
void run_fields_demo()
{
  std::printf("--- Fields 字段反射示例 ---\n\n");

  // ① 遍历字段元数据
  std::printf("  第 1 步: 遍历字段元数据\n");
  const auto &fs = player_fields();
  for (const auto &e : fs.entries())
  {
    const auto &info = e.info;
    std::printf("    [%s] %s (%s)", info.key.c_str(), info.title.c_str(),
                field_kind_name(info.kind));
    if (!info.desc.empty())
      std::printf("  — %s", info.desc.c_str());
    if (info.has_min || info.has_max)
      std::printf("  [%.1f ~ %.1f]", info.min_val, info.max_val);
    std::printf("\n");
  }
  std::printf("\n");

  // ② 通过反射读写字段
  std::printf("  第 2 步: 反射读写\n");
  PlayerConfig cfg;
  cfg.name = "勇者";
  cfg.hp = 80;

  // 读取
  auto name_val = fs.get(cfg, "name");
  auto hp_val = fs.get(cfg, "hp");
  std::printf("    get(name)  = %s\n", std::any_cast<std::string>(name_val).c_str());
  std::printf("    get(hp)    = %d\n", std::any_cast<int>(hp_val));

  // 写入
  fs.set(cfg, "hp", std::any(999));
  fs.set(cfg, "god_mode", std::any(true));
  std::printf("    set(hp, 999)      → hp=%d\n", cfg.hp);
  std::printf("    set(god_mode, T)  → god_mode=%s\n", cfg.god_mode ? "true" : "false");
  std::printf("\n");

  // ③ 遍历 + 序列化示例
  std::printf("  第 3 步: 序列化所有字段\n");
  PlayerConfig cfg2{"英雄", 200, 100, 3.5f, 2.0, false};
  for (const auto &e : fs.entries())
  {
    auto val = e.get(cfg2);
    const auto &info = e.info;
    std::printf("    %s (%s): ", info.key.c_str(), info.title.c_str());

    switch (info.kind)
    {
    case FieldKind::Int:
      std::printf("%d\n", std::any_cast<int>(val));
      break;
    case FieldKind::Float:
    {
      // float 可能存为 float 或 double，安全转换
      double d = 0;
      try
      {
        d = std::any_cast<double>(val);
      }
      catch (...)
      {
        d = static_cast<double>(std::any_cast<float>(val));
      }
      std::printf("%.2f\n", d);
      break;
    }
    case FieldKind::String:
      std::printf("\"%s\"\n", std::any_cast<std::string>(val).c_str());
      break;
    case FieldKind::Bool:
      std::printf("%s\n", std::any_cast<bool>(val) ? "true" : "false");
      break;
    }
  }
  std::printf("\n");

  std::printf("--- Fields 示例结束 ---\n\n");
}
