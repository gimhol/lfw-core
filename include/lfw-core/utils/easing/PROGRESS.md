# easing/ 进度

> 缓动函数，对应 TypeScript 的 `LFW/utils/easing/` — ✅ 100% 完成

| TS | C++ | 说明 |
| --- | --- | --- |
| `IEasing.ts` | `IEasing.hpp` | 缓动函数概念 `EasingFunction<T>` |
| `ease_linearity.ts` | `EasingLinear.hpp` | 线性缓动（含 backward） |
| `ease_in_out_sine.ts` | `EasingSine.hpp` | 正弦缓动（含 backward） |
| `ease_in_out_quint.ts` | `EasingQuint.hpp` | 五次缓动（含 backward） |

> 共 4 个 C++ 文件（index.ts 为 barrel export，C++ 无需等价物）。
