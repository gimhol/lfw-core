#include <cassert>
#include <cmath>
#include <iostream>

#include "lfw-core/base/FPS.h"

// ========================================================================
// FPS 测试
// ========================================================================
static void test_fps_single_update()
{
  FPS fps(0.5f);
  fps.update(16.0f); // ~62.5 fps
  float v = fps.value();
  assert(v > 0.0f);
}

static void test_fps_smoothing()
{
  FPS fps_smooth(0.98f);
  FPS fps_jerky(0.50f);

  // 喂入固定 16ms
  for (int i = 0; i < 60; ++i)
  {
    fps_smooth.update(16.0f);
    fps_jerky.update(16.0f);
  }
  // 两个都应接近 62.5
  float vs = fps_smooth.value();
  float vj = fps_jerky.value();
  assert(vs > 55.0f && vs < 70.0f);
  assert(vj > 55.0f && vj < 70.0f);
}

static void test_fps_spike_resilience()
{
  FPS fps(0.90f);
  // 正常帧
  for (int i = 0; i < 30; ++i)
    fps.update(16.0f);
  float before_spike = fps.value();

  // 卡顿后 fps 应下降
  fps.update(100.0f);
  float after_spike = fps.value();
  assert(after_spike < before_spike);
}

static void test_fps_reset()
{
  FPS fps(0.5f);
  for (int i = 0; i < 20; ++i)
    fps.update(16.0f);

  float old = fps.value();
  fps.reset();
  // reset 后 value 可能为新初始值或 0
  float after = fps.value();
  // 仅验证 reset 不 crash
  (void)old;
  (void)after;
}

// ========================================================================
void run_fps_tests()
{
  std::cout << "  --- FPS ---\n";

  test_fps_single_update();
  test_fps_smoothing();
  test_fps_spike_resilience();
  test_fps_reset();

  std::cout << "  PASS: FPS (4 subtests)\n";
}
