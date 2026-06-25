#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "lfw-core/base/InstFactory.h"

// ========================================================================
// InstFactory 测试
// ========================================================================

struct BaseItem
{
  std::string kind;
  int value = 0;

  virtual ~BaseItem() = default;
  virtual const char *name() const = 0;
};

struct ItemA : BaseItem
{
  ItemA() { value = 10; }
  const char *name() const override { return "A"; }
};

struct ItemB : BaseItem
{
  ItemB() { value = 20; }
  const char *name() const override { return "B"; }
};

class TestFactory : public InstFactory<BaseItem>
{
public:
  std::string tag() const override { return "TestFactory"; }

  Kind get_kind(const BaseItem &inst) const override { return inst.kind; }
  void set_kind(BaseItem &inst, Kind k) override { inst.kind = std::move(k); }

  template <typename T>
  void register_type(const Kind &k)
  {
    Creator creator;
    creator.create = []() -> std::unique_ptr<BaseItem>
    { return std::make_unique<T>(); };
    creator.reset = [](BaseItem &) {};
    register_kind(k, std::move(creator));
  }
};

static void test_instfactory_create()
{
  TestFactory factory;
  factory.register_type<ItemA>("a");
  factory.register_type<ItemB>("b");

  auto *a = factory.get("a");
  assert(a != nullptr);
  assert(a->name() == std::string("A"));
  assert(a->value == 10);

  auto *b = factory.get("b");
  assert(b != nullptr);
  assert(b->name() == std::string("B"));
  assert(b->value == 20);
}

static void test_instfactory_unknown_kind()
{
  TestFactory factory;
  factory.register_type<ItemA>("a");

  try
  {
    factory.get("nonexistent");
    assert(false);
  }
  catch (const std::runtime_error &)
  {
  }
}

static void test_instfactory_reset()
{
  TestFactory factory;
  factory.register_type<ItemA>("a");

  auto *a = factory.get("a");
  a->value = 999;

  auto *a2 = factory.get("a");
  assert(a2->value == 10);
}

void run_instfactory_tests()
{
  std::cout << "  --- InstFactory ---\n";

  test_instfactory_create();
  test_instfactory_unknown_kind();
  test_instfactory_reset();

  std::cout << "  PASS: InstFactory (3 subtests)\n";
}
