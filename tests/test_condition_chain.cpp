#include <cassert>
#include <iostream>
#include <string>

#include "lfw-core/base/ConditionChain.h"

// ========================================================================
// ConditionChain 测试
// ========================================================================

struct Ctx
{
  int value = 0;
};

struct AlwaysTrue : IJudger
{
  bool run(void *) override { return true; }
  const std::string &text() const override
  {
    static std::string t = "always_true";
    return t;
  }
};

struct AlwaysFalse : IJudger
{
  bool run(void *) override { return false; }
  const std::string &text() const override
  {
    static std::string t = "always_false";
    return t;
  }
};

struct Increment : IJudger
{
  int *counter;
  explicit Increment(int *c) : counter(c) {}
  bool run(void *) override
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

struct ValueCheck : IJudger
{
  int expected;
  explicit ValueCheck(int e) : expected(e) {}
  bool run(void *ctx) override
  {
    return static_cast<Ctx *>(ctx)->value == expected;
  }
  const std::string &text() const override
  {
    static std::string t = "val_check";
    return t;
  }
};

static void test_condition_chain_all_pass()
{
  ConditionChain chain;
  AlwaysTrue t1, t2;
  chain.reset({&t1, &t2});

  Ctx ctx;
  assert(chain.flow(&ctx) == true);
}

static void test_condition_chain_fail_fast()
{
  ConditionChain chain;
  int counter = 0;
  AlwaysTrue t1;
  Increment inc1(&counter);
  AlwaysFalse f1;
  Increment inc2(&counter);
  chain.reset({&t1, &inc1, &f1, &inc2});

  Ctx ctx;
  assert(chain.flow(&ctx) == false);
  assert(counter == 1); // inc1 ran, f1 failed, inc2 skipped
}

static void test_condition_chain_value_check()
{
  ConditionChain chain;
  ValueCheck vc1(10), vc2(20);
  chain.reset({&vc1, &vc2});

  Ctx ctx{10};
  assert(chain.run(&ctx) == true);
  chain.next();
  assert(chain.run(&ctx) == false);

  ctx.value = 20;
  assert(chain.run(&ctx) == true);
}

// ========================================================================
void run_condition_chain_tests()
{
  std::cout << "  --- ConditionChain ---\n";

  test_condition_chain_all_pass();
  test_condition_chain_fail_fast();
  test_condition_chain_value_check();

  std::cout << "  PASS: ConditionChain (3 subtests)\n";
}
