# base/ 进度

> 基础组件，对应 TypeScript 的 `LFW/base/`

## 已完成

| 源文件 (TS) | C++ 产物 | 说明 |
| --- | --- | --- |
| `Callbacks.ts` + `NoEmitCallbacks.ts` | `Signal.h` | 信号/回调系统（Signal + SignalOwner 覆盖） |
| `Expression.ts` | `Expression.h` + `ConditionChain.h` | 表达式引擎 + 条件链，`void*` 消除模板 |
| `FPS.ts` | `FPS.h` | 帧率计算 |
| `FSM.ts` | `FSM.h` | 有限状态机 |
| `Graves.ts` | `Graves.h` (+ `TypedGraves<T>`) | 对象池，`void*` 消除模板，附类型安全包装 |
| `InstFactory.ts` | `InstFactory.h` | 实例工厂（保留 `template<T>`，需值语义） |
| `dedup.ts` | `dedup.h` | `std::future` + `std::mutex` 异步去重 |
| `get_short_file_size_txt.ts` | `get_short_file_size_txt.h` | 文件大小格式化 |
| `get_team_shadow_color.ts` | `get_team_shadow_color.h` | 队伍描边颜色 |
| `get_team_text_color.ts` | `get_team_text_color.h` | 队伍文字颜色 |
| `Fields`（utils 体系） | `Fields.h` | 字段反射元数据 |

## 未完成

| 源文件 | 原因 |
| --- | --- |
| `Debugging.ts` | 依赖 `Ditto`（日志系统，未转换） |
| `IActionHandler.ts` | 依赖大量 `defines/actions` 类型（未全部转换） |

## void* vs 模板取舍记录

| 类型 | 选择 | 原因 |
|------|:---:|------|
| `IExpression` / `IJudger` | `void*` | TS 存引用，需异构存储在 `IAction_Base` |
| `Graves<T>` | `void*` | TS 存 `T\|undefined` 引用，池不拥有对象 |
| `InstFactory<T>` | 保留模板 | 需 `new T`、`reset(T&)`，编译期类型安全 |
| `Signal<Args...>` | 保留模板 | 参数包类型是核心功能，无法消除 |
| `Fields<T>` | 保留模板 | 反射需编译期 `&T::member` |
