#include <cstdio>
#include <string>
#include <vector>

#include "lfw-core/utils/math/Math.hpp"

void run_math_demo()
{
  std::printf("--- 数学工具示例 ---\n\n");

  // --- clamp ---
  std::printf("  clamp(5, 0, 10) = %d\n", math::clamp(5, 0, 10));
  std::printf("  clamp(-1, 0, 10) = %d\n", math::clamp(-1, 0, 10));
  std::printf("  clamp(99, 0, 10) = %d\n\n", math::clamp(99, 0, 10));

  // --- round_float / floor_float ---
  std::printf("  round_float(3.14159, 100) = %.2f\n", math::round_float(3.14159, 100.0));
  std::printf("  floor_float(3.14159, 100) = %.2f\n\n", math::floor_float(3.14159, 100.0));

  // --- float_equal ---
  std::printf("  float_equal(0.1+0.2, 0.3) = %s\n\n",
              math::float_equal(0.1 + 0.2, 0.3) ? "true" : "false");

  // --- between ---
  std::printf("  between(5, 0, 10) = %s\n", math::between(5, 0, 10) ? "true" : "false");
  std::printf("  between(15, 0, 10) = %s\n\n", math::between(15, 0, 10) ? "true" : "false");

  // --- clamp_add ---
  std::printf("  clamp_add(8, 5, 0, 10) = %.1f\n\n", math::clamp_add(8, 5, 0, 10));

  // --- normalize ---
  std::printf("  normalize(5) = %d\n", math::normalize(5));
  std::printf("  normalize(-5) = %d\n", math::normalize(-5));
  std::printf("  normalize(0) = %d\n\n", math::normalize(0));

  // --- probability ---
  double p = math::probability(10, 0.5);
  std::printf("  probability(10次, 50%%至少一次) -> 单次概率 = %.4f\n\n", p);

  // --- project_to_line ---
  auto [proj_x, proj_y] = math::project_to_line(3.0, 4.0, 1.0, 0.0);
  std::printf("  project (3,4) onto line dir=(1,0) = (%.1f, %.1f)\n\n", proj_x, proj_y);

  // --- range ---
  auto seq = math::range(0, 10, 2);
  std::printf("  range(0, 10, 2):");
  for (auto v : seq)
    std::printf(" %d", v);
  std::printf("\n\n");

  // --- MersenneTwister ---
  std::printf("  --- MersenneTwister ---\n");
  MersenneTwister mt(12345);

  std::printf("  5 个随机整数:\n  ");
  for (int i = 0; i < 5; ++i)
    std::printf(" %u", mt.next_int());
  std::printf("\n");

  std::printf("  5 个 [0,1) 浮点数:\n  ");
  for (int i = 0; i < 5; ++i)
    std::printf(" %.4f", mt.next_float());
  std::printf("\n");

  std::printf("  5 个 [10, 20) 范围内的整数:\n  ");
  for (int i = 0; i < 5; ++i)
    std::printf(" %lld", static_cast<long long>(mt.range(10, 20)));
  std::printf("\n");

  // pick / take
  std::vector<std::string> fruits = {"苹果", "香蕉", "橘子", "葡萄", "西瓜"};
  std::printf("  从 [苹果,香蕉,橘子,葡萄,西瓜] 中 pick:\n  ");
  for (int i = 0; i < 3; ++i)
  {
    auto *f = mt.pick(fruits);
    if (f)
      std::printf(" %s", f->c_str());
  }
  std::printf("\n");

  std::printf("  从 [苹果,香蕉,橘子,葡萄,西瓜] 中 take（会移除）:\n  ");
  while (!fruits.empty())
  {
    auto f = mt.take(fruits);
    if (f)
      std::printf(" %s", f->c_str());
  }
  std::printf("\n");
  std::printf("  取完后数组长度 = %zu\n\n", fruits.size());

  // save / load
  std::printf("  save/load 状态恢复:\n");
  mt.reset(42);
  auto a1 = mt.next_int();
  auto a2 = mt.next_int();
  auto state = mt.save();
  auto a3 = mt.next_int();
  mt.load(state);
  auto a3_again = mt.next_int();
  std::printf("  a1=%u a2=%u a3=%u restore->a3=%u\n",
              a1, a2, a3, a3_again);
  std::printf("  (a3 == restore) = %s\n\n", a3 == a3_again ? "true" : "false");

  std::printf("--- 数学工具示例结束 ---\n\n");
}
