#ifndef LFW_CORE_ANIMATION_LOOP_H
#define LFW_CORE_ANIMATION_LOOP_H

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

  int count() const;
  void set_count(int v);
  Loop &set_count_chain(int v);

  int times() const;
  void set_times(int v);
  Loop &set_times_chain(int v);

  Loop &set(int count_val, int times_val);
  Loop &reset();
  bool continue_loop();
  bool done() const;

private:
  int _times = 1;
  int _count = 0;
};

LFW_NS_END

#endif
