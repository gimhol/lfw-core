# lfw-core 开发进度

> 从 `little-fighter-j/src/LFW` 的 TypeScript 到 C++ 的转换追踪

---

## 整体进度

| 模块 | TS 文件数 | 已转换 | 状态 |
| --- | --- | --- | --- |
| **base/** — 基础组件 | 13 | 8 | 🟡 62% |
| **utils/math/** — 数学工具 | 12 | 1 (合并) | ✅ 100% |
| **defines/** — 类型定义/接口 | ~100 | 0 | 🔴 0% |
| **ditto/** — 引擎核心(缓存/渲染/输入等) | ~30 | 0 | 🔴 0% |
| **state/** — 状态机(角色/武器/子弹) | ~30 | 0 | 🔴 0% |
| **entity/** — 实体系统 | — | 0 | 🔴 0% |
| **controller/** — 控制器 | — | 0 | 🔴 0% |
| **animation/** — 动画 | — | 0 | 🔴 0% |
| **collision/** — 碰撞 | — | 0 | 🔴 0% |
| **bg/** — 背景 | — | 0 | 🔴 0% |
| **buff/** — 增益/减益 | — | 0 | 🔴 0% |
| **bot/** — AI | — | 0 | 🔴 0% |
| **dat_translator/** — DAT 解析 | — | 0 | 🔴 0% |
| **loader/** — 资源加载 | — | 0 | 🔴 0% |
| **types/** / **schema/** — 类型 | — | 0 | 🔴 0% |
| **ui/** — 界面 | — | 0 | 🔴 0% |
| **helper/** — 辅助 | — | 0 | 🔴 0% |
| **stage/** — 关卡 | — | 2 | 🟡 少量 |
| **顶层文件** (LFW.ts, World.ts, Factory.ts, …) | ~15 | 0 | 🔴 0% |

---

## 已完成（base/）

| 源文件 (TS) | C++ 产物 | 说明 |
| --- | --- | --- |
| `LFW/base/Callbacks.ts` | `lfw-core/base/Signal.hpp` | 信号/回调系统 ✅ |
| `LFW/base/Expression.ts` | `lfw-core/base/Expression.hpp` | 字符串表达式解析引擎 ✅ |
| `LFW/base/FPS.ts` | `lfw-core/base/FPS.hpp` | 帧率计算 ✅ |
| `LFW/base/FSM.ts` | `lfw-core/base/FSM.hpp` | 有限状态机，回调改用 Signal ✅ |
| `LFW/base/Graves.ts` | `lfw-core/base/Graves.hpp` | 对象池 ✅ |
| `LFW/base/InstFactory.ts` | `lfw-core/base/InstFactory.hpp` | 实例工厂，Kind 支持泛型 ✅ |
| `LFW/stage/Expressions.ts` | `lfw-core/base/ConditionChain.hpp` | 条件链步进器 ✅ |
| `LFW/stage/fields.ts` | `lfw-core/base/Fields.hpp` | 字段反射元数据 ✅ |

### base/ 未完成（5 个文件）

| 源文件 | 说明 |
| --- | --- |
| ~~`LFW/base/Debugging.ts`~~ | ~~调试工具~~ — 依赖 `Ditto` + JS 运行时反射，不适合 C++；改用宏 + `std::source_location` |
| ~~`LFW/base/dedup.ts`~~ | ~~async 调用去重~~ — 依赖 JS `Promise` 异步运行时，C++ 无直接等价物；改用 `std::shared_future` 或任务系统 |
| `LFW/base/get_short_file_size_txt.ts` | 文件大小格式化显示 |
| `LFW/base/get_team_shadow_color.ts` | 队伍阴影颜色映射 |
| `LFW/base/get_team_text_color.ts` | 队伍文字颜色映射 |
| `LFW/base/IActionHandler.ts` | 动作处理器接口 |
| ~~`LFW/base/NoEmitCallbacks.ts`~~ | ~~无触发回调~~ — 已被 `Signal` + `SignalOwner` 完整覆盖，不转换 |

> `index.ts` 仅为 re-export，不计入。

## 已完成（utils/）

| 源文件 (TS) | C++ 产物 | 说明 |
| --- | --- | --- |
| `utils/math/*.ts` (12 files) | `utils/math/Math.hpp` + `MT.hpp` | 数学工具 + 梅森旋转 ✅ |

## 额外功能

| 功能 | 说明 |
| --- | --- |
| CMake 构建系统 | MSVC + Ninja 支持 |
| nlohmann-json 集成 | 通过 vcpkg 管理 |
| JSON 反射序列化 | `Fields<T>` + `nlohmann/json` 自动序列化/反序列化 |
| VS Code 调试配置 | launch.json / tasks.json / IntelliSense 配置 |

---

## 待完成（按优先级）

### 🔴 P0 — 核心引擎

- `ditto/` — 引擎基础架构（Instance, IReadable, IRender, ITimeout, cache, xml/zip 解析）
- `LFW.ts` / `World.ts` — 引擎入口和世界管理
- `Factory.ts` — 全局工厂

### 🔴 P1 — 基础定义（defines/，~100 个接口）

- `IExpression.ts` ✅→ `IExpression` 已合并到 `ConditionChain` 中
- 其余 ~100 个接口类型（数据结构定义）

### 🔴 P2 — 状态机

- `state/` — 角色/武器/子弹各状态实现（~30 个文件）

### 🟡 P3 — 实体与碰撞

- `entity/` — 实体系统
- `collision/` — 碰撞检测
- `Transform.ts` / `ITransform.ts` — 变换

### 🟡 P4 — 输入与控制器

- `controller/` — 输入处理
- `Keys.ts` — 按键定义

### 🔵 P5 — 资源与渲染

- `loader/` — DAT/图片/音频加载
- `animation/` — 动画系统
- `bg/` — 背景系统
- `dat_translator/` — DAT 数据转换

### 🔵 P6 — 辅助与工具

- `helper/` — 工具函数
- `types/` / `schema/` — 类型系统
- `ui/` — UI 组件
- `bot/` — AI
- `buff/` — Buff 系统
- `stage/` — 关卡系统
