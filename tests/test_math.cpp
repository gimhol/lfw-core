#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "lfw-core/utils/math/Math.hpp"
#include "lfw-core/utils/math/MT.hpp"

// ========================================================================
// math 基础函数测试
// ========================================================================
static void test_math_clamp()
{
  assert(math::clamp(5, 0, 10) == 5);
  assert(math::clamp(-1, 0, 10) == 0);
  assert(math::clamp(99, 0, 10) == 10);
}

static void test_math_round()
{
  assert(math::round_float(3.14159, 100.0) > 3.13 && math::round_float(3.14159, 100.0) < 3.15);
  assert(math::floor_float(3.14159, 100.0) > 3.13 && math::floor_float(3.14159, 100.0) < 3.15);
  assert(math::float_equal(0.1 + 0.2, 0.3));
  assert(!math::float_equal(0.1, 0.2));
}

static void test_math_between()
{
  assert(math::between(5, 0, 10));
  assert(!math::between(15, 0, 10));
  assert(math::between(0, 0, 10));
  assert(math::between(10, 0, 10));
}

static void test_math_clamp_add()
{
  assert(math::clamp_add(8, 5, 0, 10) == 10.0);
  assert(math::clamp_add(2, 3, 0, 10) == 5.0);
}

static void test_math_normalize()
{
  assert(math::normalize(5) == 1);
  assert(math::normalize(-5) == -1);
  assert(math::normalize(0) == 0);
  assert(math::normalize(0.001) == 1);
  assert(math::normalize(-0.001) == -1);
}

static void test_math_probability()
{
  double p = math::probability(10, 0.5);
  assert(p > 0.0 && p < 1.0);
}

static void test_math_project_to_line()
{
  auto [x, y] = math::project_to_line(3.0, 4.0, 1.0, 0.0);
  assert(x > 2.9 && x < 3.1);
  assert(y > -0.1 && y < 0.1);
}

static void test_math_range()
{
  auto seq = math::range(0, 10, 2);
  assert(seq.size() == 6);
  assert(seq[0] == 0);
  assert(seq[5] == 10);

  auto seq2 = math::range(5, 1, -1);
  assert(seq2.size() == 5);
  assert(seq2[0] == 5);
  assert(seq2[4] == 1);
}

// ========================================================================
// MersenneTwister 测试
// ========================================================================
static void test_mt_deterministic()
{
  MersenneTwister mt(12345);
  // 同种子应产生相同序列
  std::uint32_t first = mt.next_int();
  for (int i = 0; i < 10; ++i)
    mt.next_int();
  mt.reset(12345);
  assert(mt.next_int() == first);
}

static void test_mt_float()
{
  MersenneTwister mt(42);
  for (int i = 0; i < 100; ++i)
  {
    double f = mt.next_float();
    assert(f >= 0.0 && f < 1.0);
  }
}

static void test_mt_range()
{
  MersenneTwister mt(7);
  for (int i = 0; i < 100; ++i)
  {
    auto r = mt.range(10, 20);
    assert(r >= 10 && r < 20);
  }
}

static void test_mt_pick()
{
  MersenneTwister mt(1);
  std::vector<int> arr = {10, 20, 30};
  for (int i = 0; i < 20; ++i)
  {
    auto *p = mt.pick(arr);
    assert(p != nullptr);
    assert(*p == 10 || *p == 20 || *p == 30);
  }

  std::vector<int> empty;
  assert(mt.pick(empty) == nullptr);
}

static void test_mt_take()
{
  MersenneTwister mt(99);
  std::vector<int> arr = {1, 2, 3, 4, 5};
  std::size_t original_size = arr.size();

  auto v = mt.take(arr);
  assert(v.has_value());
  assert(arr.size() == original_size - 1);

  while (mt.take(arr).has_value())
    ;
  assert(arr.empty());
  assert(!mt.take(arr).has_value());
}

static void test_mt_save_load()
{
  MersenneTwister mt(555);
  for (int i = 0; i < 10; ++i)
    mt.next_int();

  auto state = mt.save();
  auto v1 = mt.next_int();
  auto v2 = mt.next_int();

  // 还原快照后应产生相同序列
  mt.load(state);
  assert(mt.next_int() == v1);
  assert(mt.next_int() == v2);
}

// ========================================================================
void run_math_tests()
{
  std::cout << "  --- math ---\n";

  test_math_clamp();
  test_math_round();
  test_math_between();
  test_math_clamp_add();
  test_math_normalize();
  test_math_probability();
  test_math_project_to_line();
  test_math_range();
  std::cout << "  PASS: math (8 subtests)\n";

  std::cout << "  --- MersenneTwister ---\n";
  test_mt_deterministic();
  test_mt_float();
  test_mt_range();
  test_mt_pick();
  test_mt_take();
  test_mt_save_load();
  std::cout << "  PASS: MersenneTwister (6 subtests)\n";
}
