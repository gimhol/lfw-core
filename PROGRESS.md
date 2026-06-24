# lfw-core 开发进度

> 从 `little-fighter-j/src/LFW` 的 TypeScript 到 C++ 的转换追踪

## 整体进度

| 模块 | TS 文件数 | 已转换 | 详情 |
| --- | --- | --- | --- |
| **base/** | 13 | 8 | [→](include/lfw-core/base/PROGRESS.md) |
| **utils/** | — | 9 | [✅ 100%](include/lfw-core/utils/PROGRESS.md) |
| **defines/** | ~100 | 枚举+actions+Info | [→](include/lfw-core/defines/PROGRESS.md) |
| **ditto/** | ~30 | 0 | 🔴 |
| **state/** | ~30 | 0 | 🔴 |
| **entity/** | — | 0 | 🔴 |
| **controller/** | — | 0 | 🔴 |
| **animation/** | — | 0 | 🔴 |
| **collision/** | — | 0 | 🔴 |
| **bg/** | — | 0 | 🔴 |
| **buff/** | — | 0 | 🔴 |
| **bot/** | — | 0 | 🔴 |
| **dat_translator/** | — | 0 | 🔴 |
| **loader/** | — | 0 | 🔴 |
| **types/schema/** | — | 0 | 🔴 |
| **ui/** | — | 0 | 🔴 |
| **helper/** | — | 0 | 🔴 |
| **stage/** | — | 2 | 🟡 |
| **顶层文件** | ~15 | 0 | 🔴 |

## 额外功能

| 功能 | 说明 |
| --- | --- |
| CMake 构建 | MSVC + Ninja |
| nlohmann-json | vcpkg 管理 |
| JSON 反射 | `Fields<T>` 序列化/反序列化 |
| VS Code 调试 | launch.json / tasks.json |

## 各模块详情

- [base/](include/lfw-core/base/PROGRESS.md) — 信号、表达式、FSM、工厂
- [defines/](include/lfw-core/defines/PROGRESS.md) — 枚举、动作接口、Info 结构
- [utils/](include/lfw-core/utils/PROGRESS.md) — 数学、字符串解析器
