#include <cstdio>
#include <string>
#include <utility>

#include "lfw-core/base/InstFactory.hpp"

// ============================================================
// 基类: 所有"子弹"的公共基类
// ============================================================
struct Bullet
{
  std::string kind;
  int damage = 0;
  std::string label;

  virtual ~Bullet() = default;
  virtual void fire() const = 0;
  virtual const char *type_name() const = 0;
};

// ============================================================
// 具体子弹类型
// ============================================================
struct FireBullet : Bullet
{
  FireBullet()
  {
    label = "火焰弹";
    damage = 50;
  }
  void fire() const override
  {
    std::printf("    [发射] 🔥 FireBullet dmg=%d (%s)\n", damage, label.c_str());
  }
  const char *type_name() const override { return "FireBullet"; }
};

struct IceBullet : Bullet
{
  IceBullet()
  {
    label = "冰霜弹";
    damage = 30;
  }
  void fire() const override
  {
    std::printf("    [发射] ❄️ IceBullet dmg=%d (%s)\n", damage, label.c_str());
  }
  const char *type_name() const override { return "IceBullet"; }
};

struct LightningBullet : Bullet
{
  int chain_count = 3;
  LightningBullet()
  {
    label = "雷电弹";
    damage = 80;
  }
  void fire() const override
  {
    std::printf("    [发射] ⚡ LightningBullet dmg=%d chain=%d (%s)\n",
                damage, chain_count, label.c_str());
  }
  const char *type_name() const override { return "LightningBullet"; }
};

// ============================================================
// 子弹工厂
// ============================================================
class BulletFactory : public InstFactory<Bullet>
{
public:
  std::string tag() const override { return "BulletFactory"; }

  Kind get_kind(const Bullet &inst) const override
  {
    return inst.kind;
  }

  void set_kind(Bullet &inst, Kind k) override
  {
    inst.kind = std::move(k);
  }

  // 便捷注册方法
  template <typename B>
  void register_type(const Kind &kind)
  {
    register_kind(kind, {
                            .create = []() -> std::unique_ptr<Bullet>
                            { return std::make_unique<B>(); },
                            .reset = [](Bullet &b)
                            {
          // 重置为默认状态
          b.damage = 0; },
                        });
  }
};

// ============================================================
// 示例运行
// ============================================================
void run_instfactory_demo()
{
  std::printf("--- InstFactory 实例工厂示例 ---\n\n");

  BulletFactory factory;

  // 注册 3 种子弹类型
  factory.register_type<FireBullet>("fire");
  factory.register_type<IceBullet>("ice");
  factory.register_type<LightningBullet>("lightning");

  // ① 获取实例并发射
  std::printf("  第 1 步: 获取实例并发射\n");
  auto *b1 = factory.get("fire");
  b1->fire();
  auto *b2 = factory.get("ice");
  b2->fire();
  auto *b3 = factory.get("lightning");
  b3->fire();
  std::printf("\n");

  // ② 回收实例到池中
  std::printf("  第 2 步: 回收实例到池\n");
  factory.recycle(*b1);
  factory.recycle(*b2);
  std::printf("  回收了 fire, ice\n\n");

  // ③ 再次获取 — 从池中复用
  std::printf("  第 3 步: 再次获取（复用池）\n");
  auto *b4 = factory.get("fire");
  b4->fire();
  auto *b5 = factory.get("ice");
  b5->fire();
  std::printf("  成功从池中复用\n\n");

  // ④ 命名实例（key）
  std::printf("  第 4 步: 命名实例\n");
  auto *boss_bullet = factory.get("lightning", "boss_weapon");
  boss_bullet->fire();
  std::printf("  exists(lightning, boss_weapon) = %s\n",
              factory.exists("lightning", "boss_weapon") ? "true" : "false");

  auto *same = factory.find("lightning", "boss_weapon");
  std::printf("  find(lightning, boss_weapon) 地址%s相同\n",
              same == boss_bullet ? "" : "不");

  // ============================================================
  // 整型 Kind 示例
  // ============================================================
  std::printf("  --- 整型 Kind 示例 ---\n");

  enum class SkillType
  {
    Fire = 1,
    Ice = 2,
    Thunder = 3
  };

  struct Skill
  {
    int type = 0;
    int cooldown = 0;
    const char *name = "";
  };

  class SkillFactory : public InstFactory<Skill, int>
  {
  public:
    std::string tag() const override { return "SkillFactory"; }
    int get_kind(const Skill &inst) const override { return inst.type; }
    void set_kind(Skill &inst, int k) override { inst.type = k; }
  };

  SkillFactory sf;
  sf.register_kind(1, {
                          .create = []() -> std::unique_ptr<Skill>
                          { return std::make_unique<Skill>(); },
                          .reset = [](Skill &s)
                          { s.cooldown = 0; s.name = ""; },
                      });
  sf.register_kind(2, {
                          .create = []() -> std::unique_ptr<Skill>
                          { return std::make_unique<Skill>(); },
                          .reset = [](Skill &s)
                          { s.cooldown = 0; s.name = ""; },
                      });

  auto *s1 = sf.get(1);
  s1->name = "火球术";
  s1->cooldown = 5;
  std::printf("  Skill type=%d name=%s cooldown=%d\n", s1->type, s1->name, s1->cooldown);

  auto *s2 = sf.get(2, "ice_blast");
  s2->name = "冰爆";
  std::printf("  Named skill type=%d name=%s\n", s2->type, s2->name);

  auto *found = sf.find(2, "ice_blast");
  std::printf("  find(2, ice_blast) %s nullptr\n", found ? "!=" : "==");

  std::printf("\n--- InstFactory 示例结束 ---\n\n");
}
