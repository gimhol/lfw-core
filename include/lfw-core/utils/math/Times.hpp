#ifndef LFW_CORE_UTILS_MATH_TIMES_HPP
#define LFW_CORE_UTILS_MATH_TIMES_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>

// ============================================================
// Times — 带上下限和生命周期的计数器
// 对应 Times.ts
// ============================================================
class Times
{
public:
  static constexpr double MIN = 0.0;
  static constexpr double MAX = 1e308; // ≈ Number.MAX_SAFE_INTEGER (实际用 double 范围)
  static constexpr double LIFES = 1e308;

  /// 快照 — 对应 ITimesSnapshot
  struct Snapshot
  {
    std::array<double, 5> nums{}; // [value, min, max, lifes, remains]
  };

  explicit Times(double _min = MIN, double _max = MAX)
  {
    set_range(_min, _max);
  }

  /// 重置到初始状态
  Times &reborn()
  {
    _max = MAX;
    _value = _min = MIN;
    _lifes = _remains = LIFES;
    return *this;
  }

  /// 设定范围：a,b 中较小者为 min，较大者为 max，value 初始设为 a
  Times &set_range(double a, double b)
  {
    _min = std::min(std::floor(a), std::floor(b));
    _max = std::max(std::floor(a), std::floor(b));
    _value = std::floor(a);
    return *this;
  }

  /// 设定生命次数
  Times &set_lifes(double value = -1)
  {
    _lifes = std::floor(value);
    _remains = _lifes;
    return *this;
  }

  /// 重置到范围最小值，剩余次数也还原
  Times &reset()
  {
    _value = _min;
    _remains = _lifes;
    return *this;
  }

  /// 增加值 d，返回是否达到或超过 max
  bool add(double d = 1.0)
  {
    if (_remains == 0)
      return false;

    _value = std::round((_value + d) * 1000.0) / 1000.0; // 等效 round_float
    bool ret = _value >= _max;

    if (ret && _remains > 0)
      --_remains;
    if (_value > _max)
      _value = _min;
    if (_value < _min)
      _value = _max;

    return ret;
  }

  // --- getters ---
  double value() const { return _value; }
  double min() const { return _min; }
  double max() const { return _max; }
  double lifes() const { return _lifes; }
  double remains() const { return _remains; }
  bool is_max() const { return _value >= _max; }
  bool is_min() const { return _value <= _min; }

  // --- setters ---
  void set_value(double v) { _value = std::floor(v); }
  void set_min(double v) { _min = std::floor(v); }
  void set_max(double v) { _max = std::floor(v); }

  // --- 快照 ---
  Snapshot to_snapshot() const
  {
    return Snapshot{std::array<double, 5>{_value, _min, _max, _lifes, _remains}};
  }

  Times &read_snapshot(const Snapshot &s)
  {
    _value = s.nums[0];
    _min = s.nums[1];
    _max = s.nums[2];
    _lifes = s.nums[3];
    _remains = s.nums[4];
    return *this;
  }

private:
  double _value = MIN;
  double _min = MIN;
  double _max = MAX;
  double _lifes = LIFES;
  double _remains = LIFES;
};

#endif // LFW_CORE_UTILS_MATH_TIMES_HPP
