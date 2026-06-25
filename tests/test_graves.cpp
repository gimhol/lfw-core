#include <cassert>
#include <iostream>
#include <string>
#include <utility>

#include "lfw-core/base/Graves.h"

// ========================================================================
// Graves 对象池测试
// ========================================================================

struct TestItem
{
  int id = 0;
  std::string label;

  TestItem() = default;

  TestItem(int id, std::string label)
      : id(id), label(std::move(label)) {}

  TestItem(const TestItem &) = delete;
  TestItem &operator=(const TestItem &) = delete;

  TestItem(TestItem &&other) noexcept
      : id(other.id), label(std::move(other.label))
  {
    other.id = -1;
  }

  TestItem &operator=(TestItem &&other) noexcept
  {
    if (this != &other)
    {
      id = other.id;
      label = std::move(other.label);
      other.id = -1;
    }
    return *this;
  }
};

static void test_graves_empty()
{
  Graves<TestItem> pool;
  assert(pool.empty());
  assert(pool.available() == 0);
  assert(!pool.take().has_value());
}

static void test_graves_add_and_take()
{
  Graves<TestItem> pool;
  pool.add(TestItem(1, "Alpha"));

  assert(!pool.empty());
  assert(pool.available() == 1);

  auto item = pool.take();
  assert(item.has_value());
  assert(item->id == 1);
  assert(item->label == "Alpha");

  assert(pool.empty());
  assert(!pool.take().has_value());
}

static void test_graves_reuse()
{
  Graves<TestItem> pool;
  pool.add(TestItem(10, "First"));
  pool.add(TestItem(20, "Second"));

  auto a = pool.take();
  auto b = pool.take();
  assert(a.has_value() && b.has_value());

  // 归还（move back）
  pool.add(std::move(*a));
  auto c = pool.take();
  assert(c.has_value());
  // 复用旧槽位，不会触发新构造
}

static void test_graves_multiple_add_take()
{
  Graves<TestItem> pool;
  for (int i = 0; i < 5; ++i)
    pool.add(TestItem(i, "Item"));

  assert(pool.available() == 5);

  int taken = 0;
  while (auto v = pool.take())
    ++taken;
  assert(taken == 5);
  assert(pool.empty());
}

// ========================================================================
void run_graves_tests()
{
  std::cout << "  --- Graves ---\n";

  test_graves_empty();
  test_graves_add_and_take();
  test_graves_reuse();
  test_graves_multiple_add_take();

  std::cout << "  PASS: Graves (4 subtests)\n";
}
