#include <cassert>
#include <iostream>
#include <string>

#include "lfw-core/base/Graves.h"

using namespace lfw;

// ========================================================================
// Graves 对象池测试
// ========================================================================

struct TestItem
{
  int id = 0;
  std::string label;
  bool alive = true;

  TestItem(int i, std::string l) : id(i), label(std::move(l)) {}
};

static void test_graves_empty()
{
  Graves pool;
  assert(pool.empty());
  assert(pool.available() == 0);
  assert(pool.take() == nullptr);
}

static void test_graves_add_and_take()
{
  Graves pool;
  TestItem item(1, "Alpha");

  pool.add(&item);
  assert(!pool.empty());
  assert(pool.available() == 1);

  auto *p = static_cast<TestItem *>(pool.take());
  assert(p != nullptr);
  assert(p->id == 1);
  assert(p->label == "Alpha");

  assert(pool.empty());
  assert(pool.take() == nullptr);
}

static void test_graves_reuse()
{
  Graves pool;
  TestItem a(10, "First");
  TestItem b(20, "Second");

  pool.add(&a);
  pool.add(&b);

  // 初始填充按 push 顺序 (FIFO)
  auto *p1 = static_cast<TestItem *>(pool.take());
  auto *p2 = static_cast<TestItem *>(pool.take());
  assert(p1 == &a); // 先 push 的先出
  assert(p2 == &b);

  // 归还后复用槽位 (LIFO)
  pool.add(&a);
  auto *p3 = static_cast<TestItem *>(pool.take());
  assert(p3 == &a); // 归还的立即在下次取出
}

static void test_graves_multiple_add_take()
{
  Graves pool;
  TestItem items[] = {
      {0, "0"}, {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}};

  for (auto &item : items)
    pool.add(&item);

  assert(pool.available() == 5);

  int taken = 0;
  while (pool.take())
    ++taken;
  assert(taken == 5);
  assert(pool.empty());
}

static void test_typed_graves()
{
  TypedGraves<TestItem> pool;
  TestItem a(1, "Alpha");
  TestItem b(2, "Beta");

  pool.add(&a);
  pool.add(&b);

  assert(pool.available() == 2);
  assert(!pool.empty());

  // 类型安全，无需 static_cast
  TestItem *p1 = pool.take();
  TestItem *p2 = pool.take();
  assert(p1->id == 1);
  assert(p2->id == 2);

  assert(pool.empty());

  // 与原始 Graves 交互
  pool.raw().add(&a);
  assert(pool.available() == 1);
}

// ========================================================================
void run_graves_tests()
{
  std::cout << "  --- Graves ---\n";

  test_graves_empty();
  test_graves_add_and_take();
  test_graves_reuse();
  test_graves_multiple_add_take();
  test_typed_graves();

  std::cout << "  PASS: Graves (5 subtests)\n";
}
