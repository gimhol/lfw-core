# lfw-core

> `little-fighter-j/src/LFW` 的 C++ 化项目

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
| `utils/math/*.ts` (12 files) | `utils/math/Math.hpp` | 合并为单头文件 ✅ |

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

---

## 项目结构

```text
lfw-core/
├── CMakeLists.txt                  # CMake 构建
├── include/lfw-core/
│   ├── core.hpp                    # 库基本信息
│   ├── base/                       # ✅ 基础组件
│   │   ├── ConditionChain.hpp      # 条件链
│   │   ├── Expression.hpp          # 表达式引擎
│   │   ├── Fields.hpp              # 字段反射
│   │   ├── FPS.hpp                 # 帧率计算
│   │   ├── FSM.hpp                 # 有限状态机
│   │   ├── Graves.hpp              # 对象池
│   │   ├── InstFactory.hpp         # 实例工厂
│   │   └── Signal.hpp              # 信号系统
│   └── utils/math/
│       └── Math.hpp                # ✅ 数学工具
├── src/                            # 示例代码
│   ├── main.cpp
│   ├── condition_chain_demo.cpp
│   ├── expression_demo.cpp
│   ├── fields_demo.cpp
│   ├── fps_demo.cpp
│   ├── fsm_demo.cpp
│   ├── graves_demo.cpp
│   ├── instfactory_demo.cpp
│   ├── json_reflection_demo.cpp
│   ├── math_demo.cpp
│   └── signal_demo.cpp
├── tests/
└── .vscode/                        # VS Code 配置
```

## 设计决策

### Partial\<T\> + extends → 多层 Resolver 模式

回退链：`IFrameInfo` → `IEntityInfo` → `IWorldDataset`

每层只存自己关心的子集字段（`std::optional`），不持有完整配置。

```cpp
// ===== 数据层（只存值，无逻辑）=====
struct WorldConfig {              // 世界默认配置
    float gravity = 9.8f;
    float friction_x = 0.5f;
    // ... 全部字段
};

struct EntityInfo {               // 实体可覆盖字段
    std::optional<float> gravity;
    // ... 只列实体关心的
};

struct FrameInfo {                // 帧可覆盖字段（优先级最高）
    std::string id;
    int wait = 0;
    std::optional<float> gravity;
    std::optional<float> friction_x;
    // ...
};

// ===== Resolver 层（只查值，无数据）=====

// 第一层：实体回退到世界
struct EntityResolver {
    const EntityInfo& entity;
    const WorldConfig& world;

    float gravity()    const { return entity.gravity.value_or(world.gravity); }
    // ...
};

// 第二层：帧回退到实体（实体已回退到世界）
// 组合而非继承，不破坏封装
struct FrameResolver {
    const FrameInfo& frame;
    const EntityResolver& entity_resolver;  // 注入下一层

    float gravity()    const {
        if (frame.gravity) return *frame.gravity;       // 帧优先
        return entity_resolver.gravity();                // 否则回退
    }
    float friction_x() const {
        if (frame.friction_x) return *frame.friction_x;
        return entity_resolver.friction_x();
    }
    // ...
};

// ===== 使用 =====
WorldConfig world{/* 从 JSON 加载 */};
EntityInfo entity{/* 实体数据 */};
FrameInfo frame{/* 帧数据 */};

EntityResolver entity_res{entity, world};
FrameResolver  frame_res{frame, entity_res};

float g = frame_res.gravity();  // frame → entity → world 三级回退
```

**优点**：
·

| 特性 | 说明 |
| --- | --- |
| 零拷贝 | Resolver 只存引用，不复制数据 |
| 实时更新 | WorldConfig 修改后立即生效 |
| 可组合 | 新增层级只需新写一个 Resolver，注入即可 |
| 类型安全 | 编译期检查 |
| 每层职责明确 | 数据层（`*Info`）只存储，Resolver 只查询 |

---

## Markdown格式的注意事项，这是提醒你该注意什么 (不要移除此节，也不要修改此节)

请根据以下事项，每次编辑相关内容时，注意格式

- MD060/table-column-style（统一为 `| --- |` 风格）
- MD040/fenced-code-language（代码块加了 `text` 语言标识）
