#include <cstdio>
#include <string>
#include <vector>

#include "lfw-core/base/ConditionChain.hpp"

// ============================================================
// 上下文
// ============================================================
struct BattleContext
{
  int hp;
  int mp;
  int wave;        // 当前波次
  bool has_shield; // 是否有护盾
};

// ============================================================
// 具体表达式实现（继承 IJudger，即 Expression 的接口基类）
// ============================================================

/// 血量低于阈值的条件
struct HpBelow : IJudger<BattleContext>
{
  int threshold;
  explicit HpBelow(int t) : threshold(t) {}
  bool run(const BattleContext &ctx) override
  {
    bool ok = ctx.hp < threshold;
    std::printf("    [HpBelow %d] hp=%d → %s\n", threshold, ctx.hp, ok ? "通过" : "失败");
    return ok;
  }
  const std::string &text() const override
  {
    static std::string t;
    return t;
  }
};

/// 魔法值低于阈值的条件
struct MpBelow : IJudger<BattleContext>
{
  int threshold;
  explicit MpBelow(int t) : threshold(t) {}
  bool run(const BattleContext &ctx) override
  {
    bool ok = ctx.mp < threshold;
    std::printf("    [MpBelow %d] mp=%d → %s\n", threshold, ctx.mp, ok ? "通过" : "失败");
    return ok;
  }
  const std::string &text() const override
  {
    static std::string t;
    return t;
  }
};

/// 波次检查
struct WaveCheck : IJudger<BattleContext>
{
  int target_wave;
  explicit WaveCheck(int w) : target_wave(w) {}
  bool run(const BattleContext &ctx) override
  {
    bool ok = ctx.wave >= target_wave;
    std::printf("    [WaveCheck %d] wave=%d → %s\n", target_wave, ctx.wave, ok ? "通过" : "失败");
    return ok;
  }
  const std::string &text() const override
  {
    static std::string t;
    return t;
  }
};

/// 打印消息的动作（总是返回 true）
struct LogAction : IJudger<BattleContext>
{
  std::string msg;
  explicit LogAction(std::string m) : msg(std::move(m)) {}
  bool run(const BattleContext &) override
  {
    std::printf("    [Action] %s\n", msg.c_str());
    return true;
  }
  const std::string &text() const override
  {
    static std::string t;
    return t;
  }
};

// ============================================================
// 示例运行
// ============================================================
void run_condition_chain_demo()
{
  std::printf("--- Expressions 表达式链示例 ---\n\n");

  // 创建表达式实例
  HpBelow hp_low(30);
  MpBelow mp_low(20);
  WaveCheck wave_5(5);
  WaveCheck wave_10(10);
  LogAction use_potion("使用血瓶!");
  LogAction use_mp_potion("使用蓝瓶!");
  LogAction use_ultimate("释放终极技能!");

  // ---------- 场景 1: 紧急治疗 ----------
  std::printf("  场景 1: 紧急治疗链\n");
  std::printf("  规则: hp<30 → 使用血瓶\n");

  ConditionChain<BattleContext> heal_chain;
  heal_chain.reset({&hp_low, &use_potion});

  BattleContext ctx1{25, 100, 3, false};
  std::printf("  执行 flow:\n");
  bool ok = heal_chain.flow(ctx1);
  std::printf("  → 结果: %s\n\n", ok ? "通过" : "未通过");

  // ---------- 场景 2: 多条件链 ----------
  std::printf("  场景 2: 高级技能链\n");
  std::printf("  规则: hp<30 + mp<20 → 使用蓝瓶 → wave>=10 → 释放终极技能\n");

  ConditionChain<BattleContext> skill_chain;
  skill_chain.reset({&hp_low, &mp_low, &use_mp_potion, &wave_10, &use_ultimate});

  BattleContext ctx2{25, 15, 10, false};
  std::printf("  执行 flow:\n");
  ok = skill_chain.flow(ctx2);
  std::printf("  → 结果: %s\n\n", ok ? "通过" : "未通过");

  // ---------- 场景 3: 中途失败 ----------
  std::printf("  场景 3: 条件不满足时中断\n");
  std::printf("  规则: wave>=5 → 释放终极技能\n");

  ConditionChain<BattleContext> fail_chain;
  fail_chain.reset({&wave_5, &use_ultimate});

  BattleContext ctx3{100, 100, 2, false};
  std::printf("  执行 flow:\n");
  ok = fail_chain.flow(ctx3);
  std::printf("  → wave=2 < 5, 链在第一步中断, 结果: %s\n\n", ok ? "通过" : "未通过");

  // ---------- 场景 4: reset + 重新运行 ----------
  std::printf("  场景 4: 重置后重新运行\n");
  std::printf("  规则: hp<30 → 使用血瓶\n");

  heal_chain.reset_index();
  BattleContext ctx4{20, 50, 5, false};
  ok = heal_chain.flow(ctx4);
  std::printf("  → 结果: %s\n\n", ok ? "通过" : "未通过");

  // ---------- 场景 5: 空列表 ----------
  std::printf("  场景 5: 空表达式列表\n");
  ConditionChain<BattleContext> empty_chain;
  std::printf("  run() → %s\n", empty_chain.run(ctx1) ? "true" : "false");
  std::printf("  is_first=%s  is_last=%s\n",
              empty_chain.is_first() ? "true" : "false",
              empty_chain.is_last() ? "true" : "false");

  std::printf("\n--- Expressions 示例结束 ---\n\n");
}
