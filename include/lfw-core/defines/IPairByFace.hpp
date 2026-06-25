#ifndef LFW_CORE_DEFINES_IPAIR_BY_FACE_HPP
#define LFW_CORE_DEFINES_IPAIR_BY_FACE_HPP

/// IPairByFace — 按朝向（左/右）区分的泛型对
///   left  ← 对应 -1（左）
///   right ← 对应  1（右）
template <typename T>
struct IPairByFace
{
  T left;
  T right;

  /// get(-1) → left, get(1) → right, get() → right（默认）
  [[nodiscard]] T &get(int face) { return face < 0 ? left : right; }
  [[nodiscard]] const T &get(int face) const { return face < 0 ? left : right; }
  [[nodiscard]] T &get() { return right; }
  [[nodiscard]] const T &get() const { return right; }
};

#endif
