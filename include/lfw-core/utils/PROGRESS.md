# utils/ 进度

> 工具模块，对应 TypeScript 的 `LFW/utils/`（61 个 TS 文件）

## 整体

| 子模块 | TS 文件 | C++ 状态 |
|---|---|---|
| `string_parser/` | 7 | ✅ 已转换 |
| `math/` | 13 | 🟡 部分转换 |
| `ease_method/` | 5 | [🔴 未转换](ease_method/PROGRESS.md) |
| `schema/` | 3 | [🔴 未转换](schema/PROGRESS.md) |
| 顶层 (`cross_bounding` 等) | 1 | 🔴 未转换 |
| `type_check/` | 7 | 🚫 跳过（C++ 静态类型） |
| `type_cast/` | 2 | 🚫 跳过（C++ `static_cast` 等） |
| `container_help/` | 15 | 🚫 跳过（C++ STL 等价） |
| `array/` | 4 | 🚫 跳过（C++ `std::vector` 等） |
| 其余 (`utf8`, `make_private_properties` 等) | 3 | 🚫 跳过（JS 专属） |

---

## ✅ 已完成

### string_parser/

| C++ | TS 源 | 说明 |
| --- | --- | --- |
| `detail.hpp` | — | 内部工具 |
| `match_all.hpp` | `match_all.ts` | 全量匹配 |
| `match_block.hpp` | `match_block.ts` | 块匹配 |
| `match_colon_value.hpp` | `match_colon_value.ts` | 冒号值匹配 |
| `match_hash_end.hpp` | `match_hash_end.ts` | `#end` 匹配 |
| `take_blocks.hpp` | `take_blocks.ts` | 块抽取 |
| `take_sections.hpp` | `take_sections.ts` | 段抽取 |

### math/（已转换）

| C++ | TS 源 | 说明 |
| --- | --- | --- |
| `Math.hpp` | `base.ts` 等多个 | 基础数学函数（部分合并） |
| `MT.hpp` | `MersenneTwister.ts` | 梅森旋转 |
| `Times.hpp` | `Times.ts` | 带上下限计数器 |

---

## 🟡 未完成

### math/ 待评估
>
> 以下函数可能已合并到 `Math.hpp`，需逐一确认。

| TS | 说明 |
| --- | --- |
| `clamp.ts` | 值钳制 |
| `clamp_add.ts` | 带钳位的加法 |
| `float_equal.ts` | 浮点近似相等 |
| `floor_float.ts` | 浮点取整 |
| `normalize.ts` | 向量归一化 |
| `probability.ts` | 概率计算 |
| `project_to_line.ts` | 点到线投影 |
| `range.ts` | 范围工具 |
| `round_float.ts` | 浮点四舍五入 |

### ease_method/（5 文件）

| TS | 说明 |
| --- | --- |
| `IEaseMethod.ts` | 缓动方法接口 |
| `ease_linearity.ts` | 线性缓动 |
| `ease_in_out_sine.ts` | 正弦缓动 |
| `ease_in_out_quint.ts` | 五次缓动 |

### schema/（3 文件）

| TS | 说明 |
| --- | --- |
| `validate_schema.ts` | Schema 校验 |
| `make_schema.ts` | Schema 构建 |

### 顶层

| TS | 说明 |
| --- | --- |
| `cross_bounding.ts` | 碰撞边界检测（矩形/线段相交） |

---

## 🚫 跳过

| 子模块 | 原因 |
| --- | --- |
| `type_check/` (7) | C++ 编译期类型检查 |
| `type_cast/` (2) | C++ `static_cast` / `dynamic_cast` |
| `container_help/` (15) | C++ STL 等价（`std::find` / `std::map` / `std::vector`） |
| `array/` (4) | C++ `std::vector` / `std::array` |
| `utf8.ts` | C++ `std::string` 天然 UTF-8 友好 |
| `make_private_properties.ts` | JS 运行时反射 |
| `list_writable_properties.ts` | JS 运行时反射 |
| `ITimesSnapshot.ts` | 已在 `Times.hpp` 中处理 |
| `src/Utils/` (8) | DOM/浏览器/JS 专属 |
