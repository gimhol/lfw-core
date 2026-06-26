#ifndef LFW_CORE_FPS_H
#define LFW_CORE_FPS_H

#include "lfw-core/core.hpp"


#include <algorithm>
#include <cstddef>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN


// ============================================================
// FPS — 帧率计算（指数移动平均平滑）
//
// 用法:
//   FPS fps(0.9);         // retention=0.9, 平滑度较高
//   fps.update(dt_ms);    // 每帧传入毫秒间隔
//   float cur = fps.value();  // 获取当前平滑后的 fps
//   fps.reset();
// ============================================================
class FPS
{
public:
  /// @param retention 保留率 [0, 0.99]；越大 fps 波动越平缓
  explicit FPS(float retention = 0.99f)
      : _retention(std::clamp(retention, 0.0f, 0.99f))
  {
  }

  /// 每帧更新，dt 单位为**毫秒**
  void update(float dt_ms)
  {
    if (_duration > 0)
      _duration = _duration * _retention + dt_ms * (1.0f - _retention);
    else
      _duration = dt_ms;
    _value = 1000.0f / _duration;
  }

  /// 当前平滑后的 fps 值
  [[nodiscard]] float value() const { return _value; }

  /// 重置统计
  void reset()
  {
    _value = 0;
    _duration = 0;
  }

private:
  float _value = 0;       // 当前 fps
  float _duration = 0;    // 平滑后的帧间隔 (ms)
  float _retention = 0.99f; // 保留率 [0, 0.99]
};


LFW_NS_END

#endif // LFW_CORE_FPS_H
