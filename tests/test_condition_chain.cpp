#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include "lfw-core/base/ConditionChain.hpp"

// ========================================================================
// ConditionChain 测试
// ========================================================================

struct Ctx
{
  int value = 0;
};

struct AlwaysTrue : IJudger<Ctx>
{
  bool run(const Ctx &) override { return true; }
  const std::string &text() const override
  {
    static std::string t = "always_true";
    return t;
  }
};

struct AlwaysFalse : IJudger<Ctx>
{
  bool run(const Ctx &) override { return false; }
  const std::string &text() const override
  {
    static std::string t = "always_false";
    return t;
  }
};

struct Increment : IJudger<Ctx>
{
  int *counter;
  explicit Increment(int *c) : counter(c) {}
  bool run(const Ctx &) override
  {
    ++(*counter);
    return true;
  }
  const std::string &text() const override
  {
    static std::string t = "inc";
    return t;
  }
};

struct ValueCheck : IJudger<Ctx>
{
  int expected;
  explicit ValueCheck(int e) : expected(e) {}
  bool run(const Ctx &ctx) override { return ctx.value == expected; }
  const std::string &text() const override
  {
    static std::string t = "val_check";
    return t;
  }
};

static void test_condition_chain_all_pass()
{
  ConditionChain<Ctx> chain;
  AlwaysTrue t1, t2;
  chain.reset({&t1, &t2});

  Ctx ctx;
  assert(chain.flow(ctx) == true);
}

static void test_condition_chain_fail_fast()
{
  ConditionChain<Ctx> chain;
  int counter = 0;
  AlwaysTrue t1;
  Increment inc1(&counter);
  AlwaysFalse f1;
  Increment inc2(&counter);
  chain.reset({&t1, &inc1, &f1, &inc2});

  Ctx ctx;
  bool result = chain.flow(ctx);
  assert(result == false);
  assert(counter == 1);
}

static void test_condition_chain_empty()
{
  ConditionChain<Ctx> chain;
  Ctx ctx;
  bool r = chain.flow(ctx);
  (void)r;
}

// ========================================================================
void run_condition_chain_tests()
{
  std::cout << "  --- ConditionChain ---\n";

  test_condition_chain_all_pass();
  test_condition_chain_fail_fast();
  test_condition_chain_empty();

  std::cout << "  PASS: ConditionChain (3 subtests)\n";
}
