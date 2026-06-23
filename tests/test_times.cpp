#include <cassert>
#include <cmath>
#include <iostream>

#include "lfw-core/utils/math/Times.hpp"

// ========================================================================
// Times 测试
// ========================================================================

static void test_times_default_construction()
{
  Times t;
  assert(t.value() == 0.0);
  assert(t.min() == 0.0);
  assert(t.max() == Times::MAX);
  assert(t.lifes() == Times::LIFES);
  assert(t.remains() == Times::LIFES);
  assert(t.is_min());
  assert(!t.is_max());
  std::cout << "  PASS: default construction\n";
}

static void test_times_set_range()
{
  Times t;
  t.set_range(3.7, 10.2);

  assert(t.min() == 3.0);   // floor(3.7) vs floor(10.2) → min = 3
  assert(t.max() == 10.0);  // max = 10
  assert(t.value() == 3.0); // value = floor(a) = 3

  // 反向参数
  t.set_range(20.5, 5.3);
  assert(t.min() == 5.0);
  assert(t.max() == 20.0);
  assert(t.value() == 20.0); // value = floor(a) = floor(20.5) = 20
  std::cout << "  PASS: set_range\n";
}

static void test_times_add_basic()
{
  Times t(0, 5);
  assert(t.value() == 0.0);

  // add 1, not yet at max
  bool hit = t.add(1.0);
  assert(t.value() == 1.0);
  assert(!hit);

  // add 4, reaches exactly 5 (>= max)
  hit = t.add(4.0);
  assert(t.value() == 5.0);
  assert(hit);
  assert(t.is_max());
  std::cout << "  PASS: add basic\n";
}

static void test_times_add_wrap()
{
  Times t(0, 3);

  t.add(1); // 1
  t.add(1); // 2
  t.add(1); // 3 → hits max
  assert(t.value() == 3.0);
  assert(t.is_max());

  // 再 add → value 超出 max，回卷到 min
  t.add(1); // 3+1=4 > max=3 → value = min = 0
  assert(t.value() == 0.0);
  assert(!t.is_max());
  std::cout << "  PASS: add wrap-around\n";
}

static void test_times_lifes()
{
  Times t(0, 5);
  t.set_lifes(3);

  assert(t.lifes() == 3.0);
  assert(t.remains() == 3.0);

  // 第1次到达 max：remains 3→2
  bool hit = t.add(5);
  assert(hit);
  assert(t.remains() == 2.0);

  // 第2次：value 包裹回 min，再到达 max，remains 2→1
  t.add(1); // value 6 > 5 → wrap to 0, ret=true since 6>=5
  assert(t.remains() == 1.0);
  assert(t.value() == 0.0);

  hit = t.add(5);
  assert(hit);
  assert(t.remains() == 0.0);

  // 剩余次数用尽，不再生效
  hit = t.add(5);
  assert(!hit);             // remains==0，直接返回 false
  assert(t.value() == 5.0); // value 未变
  assert(t.remains() == 0.0);
  std::cout << "  PASS: lifes/remains\n";
}

static void test_times_reset()
{
  Times t(2, 8);
  t.add(2); // value = 4
  t.set_lifes(5);

  t.reset();
  assert(t.value() == t.min());     // value 回到 min
  assert(t.remains() == t.lifes()); // remains 回到 lifes
  assert(t.max() == 8.0);           // max 不变
  std::cout << "  PASS: reset\n";
}

static void test_times_reborn()
{
  Times t(10, 20);
  t.add(5);
  t.set_lifes(3);
  t.add(20); // 触发一次

  t.reborn();
  assert(t.value() == Times::MIN);
  assert(t.min() == Times::MIN);
  assert(t.max() == Times::MAX);
  assert(t.lifes() == Times::LIFES);
  assert(t.remains() == Times::LIFES);
  std::cout << "  PASS: reborn\n";
}

static void test_times_setters()
{
  Times t;

  t.set_value(3.7);
  assert(t.value() == 3.0); // floor

  t.set_min(5.2);
  assert(t.min() == 5.0);

  t.set_max(100.9);
  assert(t.max() == 100.0);
  std::cout << "  PASS: setters use floor\n";
}

static void test_times_snapshot()
{
  Times t(1, 10);
  t.add(3);
  t.set_lifes(4);

  auto snap = t.to_snapshot();
  assert(snap.nums[0] == 4.0);  // value
  assert(snap.nums[1] == 1.0);  // min
  assert(snap.nums[2] == 10.0); // max
  assert(snap.nums[3] == 4.0);  // lifes
  assert(snap.nums[4] == 4.0);  // remains

  // 修改原对象
  t.add(10);
  assert(t.value() != snap.nums[0]);

  // 从快照恢复
  t.read_snapshot(snap);
  assert(t.value() == 4.0);
  assert(t.min() == 1.0);
  assert(t.max() == 10.0);
  assert(t.lifes() == 4.0);
  assert(t.remains() == 4.0);
  std::cout << "  PASS: snapshot save/load\n";
}

static void test_times_is_max_min()
{
  Times t(0, 5);

  assert(t.is_min());
  assert(!t.is_max());

  t.add(5);
  assert(!t.is_min());
  assert(t.is_max());
  std::cout << "  PASS: is_max / is_min\n";
}

static void test_times_chain()
{
  Times t;
  t.set_range(0, 100).set_lifes(5).reset();
  assert(t.min() == 0.0);
  assert(t.max() == 100.0);
  assert(t.value() == 0.0);
  assert(t.lifes() == 5.0);
  std::cout << "  PASS: chain calls\n";
}

// ========================================================================
void run_times_tests()
{
  std::cout << "  --- Times ---\n";

  test_times_default_construction();
  test_times_set_range();
  test_times_add_basic();
  test_times_add_wrap();
  test_times_lifes();
  test_times_reset();
  test_times_reborn();
  test_times_setters();
  test_times_snapshot();
  test_times_is_max_min();
  test_times_chain();
}
