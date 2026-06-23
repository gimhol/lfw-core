#include <iostream>
#include <string>

#include "lfw-core/Signal.hpp"

// ============================================================
// 示例 1: 基本用法 — 成员函数作为监听器
// ============================================================
namespace demo_basic
{

  struct Player
  {
    std::string name;
    int hp = 100;

    explicit Player(std::string n) : name(std::move(n)) {}

    void on_attack(int /*attacker_id*/, int damage)
    {
      hp -= damage;
      std::cout << "  [Player \"" << name << "\"] takes " << damage
                << " damage (HP=" << hp << ")\n";
    }

    void on_die()
    {
      std::cout << "  [Player \"" << name << "\"] has died!\n";
    }
  };

  void run()
  {
    std::cout << "--- demo_basic: 成员函数监听器 ---\n";

    Signal<int, int> on_attack; // void(int attackerId, int damage)
    Signal<> on_die;            // void()

    Player alice("Alice");
    Player bob("Bob");

    // 注册成员函数监听器
    on_attack.on(&alice, &Player::on_attack);
    on_attack.on(&bob, &Player::on_attack);
    on_die.on(&alice, &Player::on_die);
    on_die.on(&bob, &Player::on_die);

    // 触发信号 → 所有注册的监听器都会被调用
    std::cout << "  Emit on_attack(1, 30)...\n";
    on_attack.emit(1, 30);
    std::cout << "  Emit on_die()...\n";
    on_die.emit();

    std::cout << "\n";
  }

} // namespace demo_basic

// ============================================================
// 示例 2: 函数指针监听器 + once 一次性
// ============================================================
namespace demo_fnptr
{

  // 普通函数
  void global_health_log(float hp)
  {
    std::cout << "  [GlobalLogger] health changed to " << hp << "\n";
  }

  void run()
  {
    std::cout << "--- demo_fnptr: 函数指针 + once ---\n";

    Signal<float> on_health_change;

    // 注册函数指针（持久）
    auto id = on_health_change.on_fn(global_health_log);

    // 注册一次性的 lambda（通过 add + IListener）
    struct PrintOnce : Signal<float>::IListener
    {
      void invoke(float hp) override
      {
        std::cout << "  [PrintOnce] One-time notification: HP=" << hp << "\n";
      }
    };
    on_health_change.add(std::make_unique<PrintOnce>(), true);

    std::cout << "  First emit(80.5):\n";
    on_health_change.emit(80.5f);

    std::cout << "  Second emit(50.0):\n";
    on_health_change.emit(50.0f); // PrintOnce 不会被再次调用

    // 按 id 取消注册
    on_health_change.disconnect(id);
    std::cout << "  Third emit(10.0), after disconnect:\n";
    on_health_change.emit(10.0f); // 没有输出

    std::cout << "\n";
  }

} // namespace demo_fnptr

// ============================================================
// 示例 3: 重入安全 — emit 中再次 emit
// ============================================================
namespace demo_reentrant
{

  struct ReentrantTrigger
  {
    Signal<int> *outer_signal;
    int id;

    void on_trigger(int value)
    {
      std::cout << "  [Listener " << id << "] received " << value;
      if (value < 3)
      {
        std::cout << " → re-emitting " << (value + 1);
        outer_signal->emit(value + 1);
      }
      std::cout << "\n";
    }
  };

  void run()
  {
    std::cout << "--- demo_reentrant: emit 中再 emit ---\n";

    Signal<int> sig;

    ReentrantTrigger t1{&sig, 1};
    ReentrantTrigger t2{&sig, 2};

    sig.on(&t1, &ReentrantTrigger::on_trigger);
    sig.on(&t2, &ReentrantTrigger::on_trigger);

    std::cout << "  Initial emit(1):\n";
    sig.emit(1); // 触发后会递归 emit(2), emit(3)，全部排队有序处理

    std::cout << "\n";
  }

} // namespace demo_reentrant

// ============================================================
// 示例 4: SignalOwner 使用
// ============================================================
namespace demo_owner
{

  struct PlayerEvents
  {
    Signal<int, int> on_attack;
    Signal<> on_death;
    Signal<float> on_health_change;
  };

  struct Player : SignalOwner<void(PlayerEvents)>
  {
    std::string name;
    int hp = 100;

    explicit Player(std::string n) : name(std::move(n)) {}

    auto &events() { return std::get<PlayerEvents>(_signals); }

    void take_damage(int /*attacker_id*/, int damage)
    {
      hp -= damage;
      std::cout << "  [Player \"" << name << "\"] HP=" << hp << "\n";
      events().on_health_change.emit(static_cast<float>(hp));
      if (hp <= 0)
      {
        events().on_death.emit();
      }
    }
  };

  void run()
  {
    std::cout << "--- demo_owner: SignalOwner ---\n";

    Player player("Hero");
    auto &events = player.events();

    events.on_health_change.on_fn([](float hp)
                                  { std::cout << "  [Monitor] HP changed to " << hp << "\n"; });

    player.take_damage(1, 30);
    player.take_damage(2, 80);

    std::cout << "\n";
  }

} // namespace demo_owner

// ============================================================
// 统一入口
// ============================================================
void run_signal_demos()
{
  demo_basic::run();
  demo_fnptr::run();
  demo_reentrant::run();
  demo_owner::run();
}
