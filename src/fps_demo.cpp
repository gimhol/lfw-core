#include <cstdio>
#include <cmath>
#include <random>

#include "lfw-core/base/FPS.hpp"

void run_fps_demo()
{
  std::printf("--- FPS 帧率计算示例 ---\n");

  // 模拟不同 retention 的对比
  FPS fps_smooth(0.98f); // 高平滑
  FPS fps_jerky(0.50f);  // 低平滑，跟随快

  // 模拟 60 帧的帧时间（毫秒），包含一些波动
  std::mt19937 rng(42);
  std::uniform_real_distribution<float> dist(8.0f, 28.0f); // 8~28ms ≈ 35~125 fps

  std::printf("  %-6s | %-10s | %-10s\n", "帧", "平滑(0.98)", "灵敏(0.50)");
  std::printf("  %-6s-+-%-10s-+-%-10s\n", "------", "----------", "----------");

  float spike_times[] = {10.0f, 5.0f, 50.0f}; // 突然卡顿的 dt

  for (int i = 0; i < 60; ++i)
  {
    float dt;

    // 第 20 帧模拟一次卡顿
    if (i == 20)
      dt = 50.0f;
    // 第 40 帧模拟一次极快帧
    else if (i == 40)
      dt = 5.0f;
    else
      dt = dist(rng);

    fps_smooth.update(dt);
    fps_jerky.update(dt);

    // 每 5 帧打印一次
    if (i % 5 == 0 || i == 20 || i == 40)
    {
      std::printf("  %-6d | %-10.1f | %-10.1f  (dt=%.1fms)\n",
                  i, fps_smooth.value(), fps_jerky.value(), dt);
    }
  }

  std::printf("\n  【说明】平滑(0.98): 波动小但响应慢\n");
  std::printf("          灵敏(0.50): 波动大但能快速反映真实帧率\n");

  std::printf("\n--- FPS 示例结束 ---\n\n");
}
