#include <iostream>
#include <string>

#include "lfw-core/base/FSM.hpp"

// ============================================================
// 角色状态枚举
// ============================================================
enum class HeroState
{
  Idle,
  Run,
  Jump,
  Fall
};

// ============================================================
// 状态实现
// ============================================================
struct HeroContext
{
  bool wants_move = false;
  bool wants_jump = false;
  bool is_grounded = true;
};

class IdleState : public IState<HeroState>
{
public:
  HeroState key() const override { return HeroState::Idle; }
  const char *name() const override { return "Idle"; }

  void enter() override
  {
    std::cout << "    [Idle] 进入待机\n";
  }
  void leave() override
  {
    std::cout << "    [Idle] 离开待机\n";
  }

  std::optional<HeroState> update(float dt) override
  {
    if (ctx && ctx->wants_move)
      return HeroState::Run;
    if (ctx && ctx->wants_jump && ctx->is_grounded)
      return HeroState::Jump;
    return std::nullopt;
  }

  HeroContext *ctx = nullptr;
};

class RunState : public IState<HeroState>
{
public:
  HeroState key() const override { return HeroState::Run; }
  const char *name() const override { return "Run"; }

  void enter() override
  {
    std::cout << "    [Run] 进入跑步\n";
  }
  void leave() override
  {
    std::cout << "    [Run] 离开跑步\n";
  }

  std::optional<HeroState> update(float dt) override
  {
    if (!ctx || !ctx->wants_move)
      return HeroState::Idle;
    if (ctx && ctx->wants_jump && ctx->is_grounded)
      return HeroState::Jump;
    return std::nullopt;
  }

  HeroContext *ctx = nullptr;
};

class JumpState : public IState<HeroState>
{
public:
  HeroState key() const override { return HeroState::Jump; }
  const char *name() const override { return "Jump"; }

  float timer = 0;

  void enter() override
  {
    timer = 0;
    std::cout << "    [Jump] 起跳!\n";
  }
  void leave() override
  {
    std::cout << "    [Jump] 落下\n";
  }

  std::optional<HeroState> update(float dt) override
  {
    timer += dt;
    if (timer > 0.6f)
      return HeroState::Fall;
    return std::nullopt;
  }
};

class FallState : public IState<HeroState>
{
public:
  HeroState key() const override { return HeroState::Fall; }
  const char *name() const override { return "Fall"; }

  void enter() override
  {
    std::cout << "    [Fall] 开始下落\n";
  }
  void leave() override
  {
    std::cout << "    [Fall] 落地\n";
  }

  std::optional<HeroState> update(float dt) override
  {
    if (ctx && ctx->is_grounded)
      return ctx->wants_move ? HeroState::Run : HeroState::Idle;
    return std::nullopt;
  }

  HeroContext *ctx = nullptr;
};

// ============================================================
// 状态变更监听器（使用 Signal 回调）
// ============================================================
struct StateLogger
{
  void on_changed(const FSM<HeroState> &fsm)
  {
    auto *s = fsm.state();
    std::cout << "    >>> 状态变更: "
              << (s && s->name() ? s->name() : "?") << "\n";
  }
};

// ============================================================
// 示例运行
// ============================================================
void run_fsm_demo()
{
  std::cout << "--- FSM 有限状态机示例 ---\n";

  // 上下文
  HeroContext ctx;

  // 状态实例
  IdleState idle;
  RunState run;
  JumpState jump;
  FallState fall;

  idle.ctx = &ctx;
  run.ctx = &ctx;
  fall.ctx = &ctx;

  // FSM
  FSM<HeroState> fsm("Hero");
  fsm.add(idle, run, jump, fall);
  fsm.logger([](const std::string &msg)
             { std::cout << "  " << msg << "\n"; });

  // 用 Signal 监听状态变更（成员函数方式）
  StateLogger logger;
  fsm.on_state_changed(&logger, &StateLogger::on_changed);

  // 也用函数指针方式注册第二个监听
  fsm.on_state_changed_fn([](const FSM<HeroState> &fsm)
                          {
    auto *s = fsm.state();
    auto *p = fsm.prev_state();
    std::cout << "    [fn] "
              << (p && p->name() ? p->name() : "?")
              << " → "
              << (s && s->name() ? s->name() : "?")
              << "\n"; });

  // 初始状态
  fsm.use(HeroState::Idle);
  std::cout << "\n";

  // --- 模拟行为 ---
  std::cout << "  [1] 按移动键 → 应切换到 Run\n";
  ctx.wants_move = true;
  fsm.update(0.1f);
  std::cout << "\n";

  std::cout << "  [2] 松开移动键 → 应回到 Idle\n";
  ctx.wants_move = false;
  fsm.update(0.1f);
  std::cout << "\n";

  std::cout << "  [3] 按跳 → 应切换到 Jump, 然后 Fall, 最后回到 Idle\n";
  ctx.wants_jump = true;
  ctx.is_grounded = true;
  fsm.update(0.1f); // Idle → Jump

  ctx.wants_jump = false;
  fsm.update(0.3f); // Jump 中
  fsm.update(0.3f); // Jump → Fall (timer > 0.6)

  ctx.is_grounded = true;
  fsm.update(0.1f); // Fall → Idle (grounded, not moving)
  std::cout << "\n";

  std::cout << "  [4] 直接 use 切换到相同状态 → 应被跳过\n";
  fsm.use(HeroState::Idle);
  std::cout << "\n";

  std::cout << "--- FSM 示例结束 ---\n\n";
}
