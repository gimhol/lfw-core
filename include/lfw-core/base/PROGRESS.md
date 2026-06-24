# base/ 进度

> 基础组件，对应 TypeScript 的 `LFW/base/`

## 已完成

| 源文件 (TS) | C++ 产物 | 说明 |
| --- | --- | --- |
| `Callbacks.ts` | `Signal.hpp` | 信号/回调系统 |
| `Expression.ts` | `Expression.hpp` | 字符串表达式解析引擎 |
| `FPS.ts` | `FPS.hpp` | 帧率计算 |
| `FSM.ts` | `FSM.hpp` | 有限状态机 |
| `Graves.ts` | `Graves.hpp` | 对象池 |
| `InstFactory.ts` | `InstFactory.hpp` | 实例工厂 |
| `stage/Expressions.ts` | `ConditionChain.hpp` | 条件链步进器 |
| `stage/fields.ts` | `Fields.hpp` | 字段反射元数据 |

## 未完成

| 源文件 | 说明 |
| --- | --- |
| `get_short_file_size_txt.ts` | 文件大小格式化显示 |
| `get_team_shadow_color.ts` | 队伍阴影颜色映射 |
| `get_team_text_color.ts` | 队伍文字颜色映射 |
| `IActionHandler.ts` | 动作处理器接口 |

## 已跳过

| 源文件 | 原因 |
| --- | --- |
| `Debugging.ts` | 依赖 JS 运行时反射，改用宏 + `std::source_location` |
| `dedup.ts` | 依赖 JS Promise 异步 |
| `NoEmitCallbacks.ts` | 已被 Signal + SignalOwner 覆盖 |
