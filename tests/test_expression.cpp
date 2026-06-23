#include <cassert>
#include <any>
#include <iostream>
#include <optional>
#include <string>

#include "lfw-core/base/Expression.hpp"

// ========================================================================
// Expression 测试
// ========================================================================

struct Stats
{
  int hp = 100;
  int mp = 50;
  double distance = 0.0;
};

static auto make_getter()
{
  return [](const std::string &word) -> std::optional<ValGetter<Stats>>
  {
    if (word == "hp")
      return ValGetter<Stats>{[](const Stats &ctx, const std::string &, const std::string &) -> std::any
                              { return ctx.hp; }};
    if (word == "mp")
      return ValGetter<Stats>{[](const Stats &ctx, const std::string &, const std::string &) -> std::any
                              { return ctx.mp; }};
    if (word == "distance")
      return ValGetter<Stats>{[](const Stats &ctx, const std::string &, const std::string &) -> std::any
                              { return ctx.distance; }};
    return std::nullopt;
  };
}

static void test_expression_numeric_compare()
{
  auto getter = make_getter();
  Stats ctx{30, 80, 100.0};

  Expression<Stats> e1("hp < 50", getter);
  assert(e1.run(ctx) == true);

  Expression<Stats> e2("hp >= 100", getter);
  assert(e2.run(ctx) == false);

  Expression<Stats> e3("mp > 20", getter);
  assert(e3.run(ctx) == true);
}

static void test_expression_and()
{
  auto getter = make_getter();
  Stats ctx{30, 80, 100.0};

  Expression<Stats> e("hp < 50 && mp > 20", getter);
  assert(e.run(ctx) == true);
}

static void test_expression_or()
{
  auto getter = make_getter();
  Stats ctx{30, 80, 100.0};

  Expression<Stats> e1("hp < 50 || mp > 100", getter);
  assert(e1.run(ctx) == true);

  Expression<Stats> e2("hp > 50 || mp > 100", getter);
  assert(e2.run(ctx) == false);
}

static void test_expression_equal()
{
  auto getter = make_getter();
  Stats ctx{30, 80, 100.0};

  Expression<Stats> e("distance == 100", getter);
  assert(e.run(ctx) == true);
}

static void test_expression_not_equal()
{
  auto getter = make_getter();
  Stats ctx{30, 80, 100.0};

  Expression<Stats> e("hp != 30", getter);
  assert(e.run(ctx) == false);
}

// ========================================================================
void run_expression_tests()
{
  std::cout << "  --- Expression ---\n";

  test_expression_numeric_compare();
  test_expression_and();
  test_expression_or();
  test_expression_equal();
  test_expression_not_equal();

  std::cout << "  PASS: Expression (5 subtests)\n";
}
