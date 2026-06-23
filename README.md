# lfw-core

> `little-fighter-j/src/LFW` 的 C++ 化项目

> 📋 开发进度请见 **[PROGRESS.md](./PROGRESS.md)**

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
│       ├── Math.hpp                # ✅ 数学工具
│       ├── MT.hpp                  # ✅ 梅森旋转
│       └── Times.hpp               # ✅ 带上下限计数器
├── src/                            # 源代码
│   ├── main.cpp
│   └── core.cpp
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
