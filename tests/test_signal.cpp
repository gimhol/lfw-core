#include <cassert>
#include <iostream>
#include <string>

#include "lfw-core/base/Signal.h"

// ========================================================================
// Signal 测试
// ========================================================================

static int g_call_count = 0;
static int g_last_value = 0;

static void global_counter(int v)
{
  ++g_call_count;
  g_last_value = v;
}

static void test_signal_basic_emit()
{
  g_call_count = 0;
  Signal<int> sig;
  auto id = sig.on_fn(global_counter);

  sig.emit(42);
  assert(g_call_count == 1);
  assert(g_last_value == 42);

  sig.emit(99);
  assert(g_call_count == 2);
  assert(g_last_value == 99);

  sig.disconnect(id);
}

static void test_signal_disconnect()
{
  g_call_count = 0;
  Signal<> sig;
  auto id = sig.on_fn([]
                      { ++g_call_count; });

  sig.emit();
  assert(g_call_count == 1);

  sig.disconnect(id);
  sig.emit();
  assert(g_call_count == 1); // 不再递增
}

static void test_signal_member_function()
{
  struct Obj
  {
    int val = 0;
    void set(int v) { val = v; }
  };

  Obj a, b;
  Signal<int> sig;
  sig.on(&a, &Obj::set);
  sig.on(&b, &Obj::set);

  sig.emit(7);
  assert(a.val == 7);
  assert(b.val == 7);
}

static void test_signal_once()
{
  g_call_count = 0;
  Signal<> sig;

  struct OnceListener : Signal<>::IListener
  {
    void invoke() override { ++g_call_count; }
  };

  sig.add(std::make_unique<OnceListener>(), true);
  sig.emit();
  assert(g_call_count == 1);

  sig.emit();
  assert(g_call_count == 1); // once 只触发一次
}

static void test_signal_reentrant()
{
  Signal<int> sig;
  int calls = 0;

  struct R : Signal<int>::IListener
  {
    Signal<int> *sig;
    int *calls;

    R(Signal<int> *s, int *c) : sig(s), calls(c) {}

    void invoke(int v) override
    {
      ++(*calls);
    }
  };

  sig.add(std::make_unique<R>(&sig, &calls), false);
  sig.add(std::make_unique<R>(&sig, &calls), false);

  sig.emit(42);
  assert(calls == 2);
}

static void test_signal_disconnect_in_emit()
{
  Signal<> sig;
  int count = 0;

  struct SelfDisconnect : Signal<>::IListener
  {
    Signal<> *sig;
    int *count;
    size_t id;

    SelfDisconnect(Signal<> *s, int *c, size_t i) : sig(s), count(c), id(i) {}

    void invoke() override
    {
      ++(*count);
      sig->disconnect(id);
    }
  };

  auto listener = std::make_unique<SelfDisconnect>(&sig, &count, 0);
  listener->sig = &sig;
  listener->count = &count;
  auto id = sig.add(std::move(listener), false);

  sig.emit();
  assert(count == 1);

  sig.emit();
  assert(count == 1); // 已断开，不再调用
}

// ========================================================================
// SignalGroup / SignalOwner 测试
// ========================================================================

struct PlayerEvents
{
  Signal<int> on_hit;
  Signal<> on_death;
};

// 普通函数（lambda 有捕获时无法转函数指针）
static int g_hit_val = 0;
static void on_hit_fn(int dmg) { g_hit_val = dmg; }

static int g_death_count = 0;
static void on_death_fn() { ++g_death_count; }

static void test_signal_group_composition()
{
  SignalGroup<PlayerEvents> group;

  g_hit_val = 0;
  group.signals.on_hit.on_fn(on_hit_fn);

  g_death_count = 0;
  group.signals.on_death.on_fn(on_death_fn);

  group.signals.on_hit.emit(25);
  assert(g_hit_val == 25);

  group.signals.on_death.emit();
  assert(g_death_count == 1);
}

static void test_signal_owner_inheritance()
{
  struct Player : SignalOwner<PlayerEvents>
  {
    int hp = 100;

    Player()
    {
      // 子类内可访问 protected signals
      signals.on_hit.on_fn(on_hit_fn);
      signals.on_death.on_fn(on_death_fn);
    }

    void take_damage(int dmg)
    {
      hp -= dmg;
      signals.on_hit.emit(dmg);
      if (hp <= 0)
        signals.on_death.emit();
    }
  };

  g_hit_val = 0;
  g_death_count = 0;

  Player p;
  p.take_damage(30);
  assert(g_hit_val == 30);
  assert(g_death_count == 0);
  assert(p.hp == 70);

  p.take_damage(80);
  assert(g_hit_val == 80);
  assert(g_death_count == 1);
  assert(p.hp == -10);
}

// ========================================================================
void run_signal_tests()
{
  std::cout << "  --- Signal ---\n";

  test_signal_basic_emit();
  test_signal_disconnect();
  test_signal_member_function();
  test_signal_once();
  test_signal_reentrant();
  test_signal_disconnect_in_emit();

  std::cout << "  PASS: Signal (6 subtests)\n";

  std::cout << "  --- SignalGroup / SignalOwner ---\n";

  test_signal_group_composition();
  test_signal_owner_inheritance();

  std::cout << "  PASS: SignalGroup & SignalOwner (2 subtests)\n";
}
