# TS IPairByFace → C++ 转换规范

> TS 泛型接口 `IPairByFace<T>` 的 C++ 转换指南。

---

## TS 源

```typescript
export interface IPairByFace<T> {
  1: T;    // 右（正朝向）
  [-1]: T; // 左（负朝向）
}
```

## C++ 目标

```cpp
template <typename T>
struct IPairByFace
{
  T left;   // -1（左）
  T right;  //  1（右）

  /// get(-1) → left, get(1) → right, get() → right（默认）
  [[nodiscard]] T &get(int face) { return face < 0 ? left : right; }
  [[nodiscard]] const T &get(int face) const { return face < 0 ? left : right; }
  [[nodiscard]] T &get() { return right; }
  [[nodiscard]] const T &get() const { return right; }
};
```

## 设计决策

| 问题 | 决策 | 理由 |
| --- | --- | --- |
| TS `[1]` / `[-1]` 索引 | 改为 `left` / `right` 命名成员 | C++ 不支持数字索引签名 |
| `pair[1]` 访问 | `pair.get(1)` | 通过方法封装，保持接口清晰 |
| 无参 `get()` | 返回 `right` | 大部分场景默认取右侧值 |
| 泛型 `T` | `template<typename T>` | 一一对应，零开销 |

## 子类型转换

TS 中 `extends IPairByFace<T>` 的子类型，在 C++ 中直接用 `using`：

```typescript
// TS
export interface IRectPair extends IPairByFace<IRect> {}
export interface IQubePair extends IPairByFace<IQube> {}
```

```cpp
// C++ — 无需新文件，直接在需要处声明：
using IRectPair = IPairByFace<IRect>;
using IQubePair = IPairByFace<IQube>;
```

## 不放入 Fields 反射

泛型模板 struct 无法直接使用 `fields()` 元编程（模板参数未确定时），因此 `IPairByFace` 不提供 `xxx_fields()` 函数。

---

> 实际文件：`include/lfw-core/defines/IPairByFace.hpp`
