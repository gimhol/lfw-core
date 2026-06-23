#ifndef LFW_CORE_UTILS_MATH_MT_HPP
#define LFW_CORE_UTILS_MATH_MT_HPP

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

#include "Math.hpp"

// ============================================================
// MersenneTwister — 梅森旋转伪随机数生成器
// 对应 MersenneTwister.ts
// ============================================================
class MersenneTwister
{
public:
  static constexpr std::size_t N = 624;
  static constexpr std::size_t M = 397;

  explicit MersenneTwister(std::uint32_t seed = 0)
  {
    // 用当前时间做默认种子
    if (seed == 0)
      seed = static_cast<std::uint32_t>(
          std::chrono::system_clock::now().time_since_epoch().count());
    reset(seed);
  }

  /// 重置生成器
  void reset(std::uint32_t seed)
  {
    _seed = seed;
    _times = 0;
    _matrix = 0x9908B0DF;
    _upper_mask = 0x80000000;
    _lower_mask = 0x7FFFFFFF;
    _index = N + 1;
    _mt[0] = seed;
    for (std::size_t i = 1; i < N; ++i)
    {
      std::uint32_t s = _mt[i - 1] ^ (_mt[i - 1] >> 30);
      _mt[i] = (((((s & 0xFFFF0000) >> 16) * 1812433253U) << 16) +
                (s & 0x0000FFFF) * 1812433253U) +
               static_cast<std::uint32_t>(i);
    }
  }

  /// 生成一个 [0, 2^32) 的随机整数 — 对应 int()
  std::uint32_t next_int()
  {
    if (_index >= N)
      twist();
    std::uint32_t y = _mt[_index++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= (y >> 18);
    ++_times;
    return y;
  }

  /// 生成 [0, 1) 的浮点数 — 对应 float()
  double next_float()
  {
    return math::floor_float(
        static_cast<double>(next_int()) / 4294967296.0); // 0xFFFFFFFF + 1
  }

  /// 生成 [min, max) 范围内的整数 — 对应 range()
  std::int64_t range(std::int64_t min, std::int64_t max)
  {
    return static_cast<std::int64_t>(std::floor(next_float() * static_cast<double>(max - min))) + min;
  }

  /// 等概率从数组中选取一个元素 — 对应 pick()
  template <typename T>
  const T *pick(const std::vector<T> &arr)
  {
    if (arr.empty())
      return nullptr;
    return &arr[static_cast<std::size_t>(range(0, static_cast<std::int64_t>(arr.size())))];
  }

  /// 等概率从数组中取出一个元素（会拷贝返回值）— 对应 take()
  template <typename T>
  std::optional<T> take(std::vector<T> &arr)
  {
    if (arr.empty())
      return std::nullopt;
    auto idx = static_cast<std::size_t>(range(0, static_cast<std::int64_t>(arr.size())));
    auto ret = std::move(arr[idx]);
    arr.erase(arr.begin() + static_cast<std::ptrdiff_t>(idx));
    return ret;
  }

  // --- 状态快照 (对应 IMersenneTwisterInfo / pure / load) ---
  struct State
  {
    std::uint32_t matrix;
    std::uint32_t seed;
    std::uint64_t times;
    std::size_t index;
    std::uint32_t mt[N];
    std::uint32_t upper_mask;
    std::uint32_t lower_mask;
  };

  State save() const
  {
    State s;
    s.matrix = _matrix;
    s.seed = _seed;
    s.times = _times;
    s.index = _index;
    s.upper_mask = _upper_mask;
    s.lower_mask = _lower_mask;
    std::copy_n(_mt, N, s.mt);
    return s;
  }

  void load(const State &s)
  {
    _matrix = s.matrix;
    _seed = s.seed;
    _times = s.times;
    _index = s.index;
    _upper_mask = s.upper_mask;
    _lower_mask = s.lower_mask;
    std::copy_n(s.mt, N, _mt);
  }

  // --- 属性访问 ---
  std::uint32_t seed() const { return _seed; }
  std::uint64_t times() const { return _times; }
  std::size_t index() const { return _index; }

private:
  void twist()
  {
    for (std::size_t i = 0; i < N; ++i)
    {
      std::uint32_t x = (_mt[i] & _upper_mask) |
                        (_mt[(i + 1) % N] & _lower_mask);
      std::uint32_t xA = x >> 1;
      if (x & 1)
        xA ^= _matrix;
      _mt[i] = _mt[(i + M) % N] ^ xA;
    }
    _index = 0;
  }

  std::uint32_t _matrix = 0x9908B0DF;
  std::uint32_t _upper_mask = 0x80000000;
  std::uint32_t _lower_mask = 0x7FFFFFFF;
  std::uint32_t _mt[N]{};
  std::size_t _index = N + 1;
  std::uint32_t _seed = 0;
  std::uint64_t _times = 0;
};

#endif // LFW_CORE_UTILS_MATH_MT_HPP
