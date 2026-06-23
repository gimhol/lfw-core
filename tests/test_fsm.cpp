#include <cassert>
#include <iostream>

#include "lfw-core/base/FSM.hpp"

// ========================================================================
// FSM 测试
// ========================================================================

enum class TestState
{
  Idle,
  Active,
  Done
};

struct TestContext
{
  bool trigger_go = false;
  bool trigger_done = false;
  int enter_count = 0;
};

class IdleS : public IState<TestState>
{
public:
  TestState key() const override { return TestState::Idle; }
  const char *name() const override { return "Idle"; }

  void enter() override
  {
    if (ctx)
      ++ctx->enter_count;
  }

  std::optional<TestState> update(float /*dt*/) override
  {
    if (ctx && ctx->trigger_go)
      return TestState::Active;
    return std::nullopt;
  }

  TestContext *ctx = nullptr;
};

class ActiveS : public IState<TestState>
{
public:
  TestState key() const override { return TestState::Active; }
  const char *name() const override { return "Active"; }

  void enter() override
  {
    if (ctx)
      ++ctx->enter_count;
  }

  std::optional<TestState> update(float /*dt*/) override
  {
    if (ctx && ctx->trigger_done)
      return TestState::Done;
    return std::nullopt;
  }

  TestContext *ctx = nullptr;
};

class DoneS : public IState<TestState>
{
public:
  TestState key() const override { return TestState::Done; }
  const char *name() const override { return "Done"; }

  void enter() override
  {
    if (ctx)
      ++ctx->enter_count;
  }

  std::optional<TestState> update(float /*dt*/) override
  {
    return std::nullopt;
  }

  TestContext *ctx = nullptr;
};

static void test_fsm_initial_state()
{
  TestContext ctx;
  FSM<TestState, IState<TestState>> fsm;

  auto idle = std::make_unique<IdleS>();
  idle->ctx = &ctx;
  auto *idle_ptr = idle.get();
  fsm.add(idle_ptr);
  idle.release();

  auto active = std::make_unique<ActiveS>();
  active->ctx = &ctx;
  auto *active_ptr = active.get();
  fsm.add(active_ptr);
  active.release();

  auto done = std::make_unique<DoneS>();
  done->ctx = &ctx;
  auto *done_ptr = done.get();
  fsm.add(done_ptr);
  done.release();

  fsm.use(TestState::Idle);
  assert(fsm.state() != nullptr);
  assert(fsm.state()->key() == TestState::Idle);
}

static void test_fsm_transition()
{
  TestContext ctx;
  FSM<TestState, IState<TestState>> fsm;

  auto idle = std::make_unique<IdleS>();
  idle->ctx = &ctx;
  auto *idle_ptr2 = idle.get();
  fsm.add(idle_ptr2);
  idle.release();

  auto active = std::make_unique<ActiveS>();
  active->ctx = &ctx;
  auto *active_ptr2 = active.get();
  fsm.add(active_ptr2);
  active.release();

  auto done = std::make_unique<DoneS>();
  done->ctx = &ctx;
  auto *done_ptr2 = done.get();
  fsm.add(done_ptr2);
  done.release();

  fsm.use(TestState::Idle);

  // 触发 Idle → Active
  ctx.trigger_go = true;
  fsm.update(0.016f);
  assert(fsm.state()->key() == TestState::Active);

  // 触发 Active → Done
  ctx.trigger_done = true;
  fsm.update(0.016f);
  assert(fsm.state()->key() == TestState::Done);
}

static void test_fsm_enter_count()
{
  TestContext ctx;
  FSM<TestState, IState<TestState>> fsm;

  auto idle = std::make_unique<IdleS>();
  idle->ctx = &ctx;
  auto *idle_ptr3 = idle.get();
  fsm.add(idle_ptr3);
  idle.release();

  auto active = std::make_unique<ActiveS>();
  active->ctx = &ctx;
  auto *active_ptr3 = active.get();
  fsm.add(active_ptr3);
  active.release();

  auto done = std::make_unique<DoneS>();
  done->ctx = &ctx;
  auto *done_ptr3 = done.get();
  fsm.add(done_ptr3);
  done.release();

  assert(ctx.enter_count == 0);
  fsm.use(TestState::Idle);
  assert(ctx.enter_count >= 1); // Idle enter

  ctx.trigger_go = true;
  fsm.update(0.016f);
  assert(ctx.enter_count >= 2); // Active enter
}

// ========================================================================
void run_fsm_tests()
{
  std::cout << "  --- FSM ---\n";

  test_fsm_initial_state();
  test_fsm_transition();
  test_fsm_enter_count();

  std::cout << "  PASS: FSM (3 subtests)\n";
}
