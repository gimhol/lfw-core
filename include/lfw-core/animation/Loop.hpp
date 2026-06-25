#ifndef LFW_CORE_ANIMATION_LOOP_HPP
#define LFW_CORE_ANIMATION_LOOP_HPP

#include <cstdint>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/**
 * 循环控制器 — 对应 TS Loop
 *
 * 控制动画的循环次数。times 为总循环次数，count 为已完成的循环次数。
 * 当 times <= 0 时表示无限循环。
 */
class Loop
{
public:
  Loop() = default;

  /// 已完成的循环次数
  int count() const { return _count; }
  void set_count(int v);
  Loop &set_count_chain(int v)
  {
    set_count(v);
    return *this;
  }

  /// 总循环次数（<=0 表示无限）
  int times() const { return _times; }
  void set_times(int v);
  Loop &set_times_chain(int v)
  {
    set_times(v);
    return *this;
  }

  /// 同时设置 count 和 times
  Loop &set(int count_val, int times_val);

  /// 重置循环计数
  Loop &reset();

  /// 推进一次循环，返回是否还可以继续
  bool continue_loop();

  /// 是否已完成所有循环
  bool done() const;

private:
  int _times = 1;
  int _count = 0;
};

LFW_NS_END

#endif // LFW_CORE_ANIMATION_LOOP_HPP
