#include <cstdio>
#include <string>
#include <utility>

#include "lfw-core/base/Graves.hpp"

// ============================================================
// 模拟一个"子弹"类型，构造/析构时打印日志
// ============================================================
struct Bullet
{
  int id = 0;
  std::string label;

  Bullet() = default;

  Bullet(int id, std::string label)
      : id(id), label(std::move(label))
  {
    std::printf("    [构造] Bullet#%d (%s)\n", id, this->label.c_str());
  }

  Bullet(const Bullet &) = delete;
  Bullet &operator=(const Bullet &) = delete;

  Bullet(Bullet &&other) noexcept
      : id(other.id), label(std::move(other.label))
  {
    other.id = -1;
  }

  Bullet &operator=(Bullet &&other) noexcept
  {
    if (this != &other)
    {
      id = other.id;
      label = std::move(other.label);
      other.id = -1;
    }
    return *this;
  }

  ~Bullet()
  {
    if (id >= 0)
      std::printf("    [析构] Bullet#%d (%s)\n", id, this->label.c_str());
  }

  void fire() const
  {
    std::printf("    [发射] Bullet#%d (%s) 咻～\n", id, this->label.c_str());
  }
};

// ============================================================
// 示例运行
// ============================================================
void run_graves_demo()
{
  std::printf("--- Graves 对象池示例 ---\n\n");

  Graves<Bullet> pool;

  // ① 创建 3 颗子弹并放入池中
  std::printf("  第 1 步: 创建 3 颗子弹并归还池\n");
  pool.add(Bullet(1, "火焰弹"));
  pool.add(Bullet(2, "冰霜弹"));
  pool.add(Bullet(3, "雷电弹"));
  std::printf("  池中可用: %zu\n\n", pool.available());

  // ② 从池中取出使用
  std::printf("  第 2 步: 取出 2 颗子弹发射\n");
  if (auto b = pool.take())
    b->fire();
  if (auto b = pool.take())
    b->fire();
  std::printf("  池中可用: %zu\n\n", pool.available());

  // ③ 发射后归还，对象被复用（不会触发构造）
  std::printf("  第 3 步: 归还 1 颗子弹（复用已有槽位）\n");
  pool.add(Bullet(4, "治疗弹"));
  std::printf("  池中可用: %zu\n", pool.available());

  // ④ 再次取出
  std::printf("  第 4 步: 取出发射\n");
  if (auto b = pool.take())
    b->fire();
  std::printf("  池中可用: %zu\n\n", pool.available());

  // ⑤ 取到池空
  std::printf("  第 5 步: 取空池\n");
  while (auto b = pool.take())
    b->fire();
  std::printf("  池空: %s\n\n", pool.empty() ? "是" : "否");

  std::printf("  【说明】对象池复用已分配的内存，减少构造/析构开销\n");
  std::printf("         可以看到第 3 步归还时没有触发构造日志\n");
  std::printf("         （因为 move 构造不打印日志）\n");

  std::printf("\n--- Graves 示例结束 ---\n\n");
}
