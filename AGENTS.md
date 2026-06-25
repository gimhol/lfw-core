# AGENTS.md — lfw-core 项目 Agent 指南

> 本文档为 AI Agent 提供 lfw-core 项目的编码规范、转换模式和工作指引。

---

## 项目概述

`lfw-core` 是将 `little-fighter-j/src/LFW` 从 **TypeScript → C++** 的移植项目。

- **TS 源目录**: `C:\Users\Gimho\little-fighter-j\src\LFW\`
- **C++ 目标**: `C:\Users\Gimho\lfw-core\`
- **构建**: CMake + vcpkg（依赖 nlohmann-json）
- **测试框架**: doctest（`tests/` 目录）

> 📌 **移植策略**：当前 C++ 移植为渐进式，逐步添加成员。每个 struct/class
> 先从 TS 源码中最核心的成员开始移植，后续按需扩展，而非一次性完整复制所有字段。

---

## 目录结构

```
lfw-core/
├── include/lfw-core/      # 头文件（公开 API）
│   ├── base/              #   基础库（Fields, Signal, FSM, Expression）
│   ├── defines/           #   枚举 + 接口定义（TS defines/ → C++ struct/enum）
│   │   └── actions/       #     动作接口子目录
│   ├── entity/            #   实体
│   ├── state/             #   状态机
│   └── utils/             #   工具（数学、字符串解析器）
├── src/                   # 实现文件
│   ├── base/
│   ├── state/
│   └── utils/
├── tests/                 # 单元测试
├── CMakeLists.txt
├── PROGRESS.md            # 整体进度追踪
└── AGENTS.md              # 本文件
```

---

## TS → C++ 转换规范

### 1. 接口转换：`interface` → `struct` + Fields 反射

```typescript
// TypeScript
export interface IFoo {
  id?: string;
  value?: number;
  name?: string;
}
```

```cpp
// C++
#include <optional>
#include <string>
#include "lfw-core/base/Fields.h"

struct IFoo {
  std::optional<std::string> id;
  std::optional<double> value;
  std::optional<std::string> name;
};

inline const auto &foo_fields() {
  static const auto fs = fields<IFoo>(
      field("id",    FieldKind::Str, &IFoo::id,    "ID"),
      field("value", FieldKind::Flt, &IFoo::value,  "数值"),
      field("name",  FieldKind::Str, &IFoo::name,   "名称"));
  return fs;
}
```

**规则**:

- TS `?` 可选 → `std::optional<T>`
- TS `number` → `double`（默认）或 `int`
- TS `string` → `std::string`
- TS `string[]` → `std::vector<std::string>`
- 每个 struct 必须配套 `xxx_fields()` 函数，用于 JSON 序列化/反序列化

### 2. 枚举转换：TS `enum` → C++ X-macro `enum class`

```cpp
#define ENUM_ITEMS(X) \
  X(MyEnum, Value1, "str_val", "描述", = 0) \
  X(MyEnum, Value2, "",        "描述", = 1)

enum class MyEnum : uint8_t {
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(MyStrMap, ENUM_ITEMS, MyEnum)
GEN_ENUM_NAME_MAP(MyNameMap, ENUM_ITEMS, MyEnum)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(my_to_string, my_from_string, MyEnum, MyStrMap)
```

详见 `include/lfw-core/defines/ENUM_CONVERSION.md`。

### 3. FieldKind 速查表

| FieldKind | JSON 类型 | C++ 类型 |
|-----------|----------|---------|
| `Str` | string | `std::string` |
| `Flt` | number | `double` |
| `Int` | integer | `int` |
| `Bool` | boolean | `bool` |
| `Strs` | string[] | `std::vector<std::string>` |
| `Flt2` | [number,number] | `std::array<double,2>` |
| `Flt3` | [number,number,number] | `std::array<double,3>` |
| `Map` | object | `std::map<K,V>` |
| `Var` | any | `std::any` / variant |
| `Obj` | object | nested struct |

### 4. 命名规范

| TS | C++ | 说明 |
|----|-----|------|
| `IThingInfo.ts` | `IThingInfo.hpp` | 文件名一致 |
| `interface IThingInfo` | `struct IThingInfo` | interface → struct |
| `enum FooBar` | `enum class FooBar` | 枚举 → enum class |
| `FooEnum` | `FooType` 或 `Foo` | 去掉冗余 Enum 后缀 |
| `camelCase` | `snake_case` | 函数/变量命名（已有风格保持一致） |

> ⚠️ **大小写敏感**：本项目目标跨平台编译（Windows / Linux / macOS）。
> 文件名和 `#include` 路径必须**严格保持与 TS 源文件一致的大小写**，因为 Linux/macOS 文件系统区分大小写。
> 使用 `git mv` 进行重命名以确保版本控制正确追踪。

### 5. 头文件格式与保护

**文件扩展名**：统一使用 `.h`（不使用 `.hpp`）。若某 class/struct 同时有 `.h` 和 `.cpp`，则：

- `.h` 中**仅保留声明**（成员函数声明、成员变量声明）
- `.cpp` 中放置**所有函数实现**（包括之前内联在头文件的简单 getter/setter）

```cpp
// ===== Foo.h（仅声明）=====
#ifndef LFW_CORE_DEFINES_IFOO_H
#define LFW_CORE_DEFINES_IFOO_H
// ...
#endif
```

命名规则: `LFW_CORE_<目录大写>_<文件名大写>_H`

### 6. Class 转换：Pimpl 模式

TS 中以 `class` 声明的核心容器（如 `LFW`），其私有成员数量多且会持续扩展，
使用 **Pimpl（Pointer to Implementation）** 模式隔离实现细节。

```cpp
// ===== LFW.hpp（公开头文件）=====
struct LFWPrivate;  // 仅前向声明，无定义

class LFW
{
public:
  LFW();
  ~LFW();           // 必须显式声明，定义在 .cpp（LFWPrivate 完整类型之后）

  // 公开接口 — getter 委托给 _->member
  MersenneTwister &mt();

private:
  std::unique_ptr<LFWPrivate> _;  // 命名约定：下划线单字符
};
```

```cpp
// ===== LFW.cpp（私有实现）=====
struct LFWPrivate
{
  MersenneTwister _mt;  // 真正的成员都放在这里

  LFWPrivate() : _mt(/* seed */) {}
};

LFW::LFW()  : _(std::make_unique<LFWPrivate>()) {}
LFW::~LFW() = default;  // 必须在 LFWPrivate 完整定义之后

MersenneTwister &LFW::mt()       { return _->_mt; }
```

**规则**：

- `XXXPrivate` 在 `.hpp` 中仅前向声明，定义放在 `.cpp`
- `LFW` 通过 `std::unique_ptr<XXXPrivate> _` 持有私有实现
- 析构函数必须在 `.hpp` 声明、在 `.cpp` 定义（`= default`），确保 `unique_ptr` 析构时 `XXXPrivate` 已是完整类型
- 所有公开 getter 委托给 `_->` 访问实际成员
- 后续新增私有成员只需修改 `XXXPrivate`，头文件无需变动

### 7. 命名空间

所有 lfw-core 代码统一使用 `lfw` 命名空间，通过宏简化书写：

```cpp
// 定义于 include/lfw-core/core.hpp
#define LFW_NS        lfw
#define LFW_NS_BEGIN  namespace lfw {
#define LFW_NS_END    }
```

**规则**：

- 每个 `.hpp` / `.cpp` 文件内容包裹在 `LFW_NS_BEGIN` / `LFW_NS_END` 之间
- 仅在 `core.hpp` 中使用 `using namespace` 或 `namespace lfw {}` 直接形式
- 不要在头文件中使用 `using namespace`（污染客户命名空间）

```cpp
// 正确示例
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

struct Foo { /* ... */ };

LFW_NS_END
```

### 8. `void*` vs 模板取舍

TS 泛型 `class Foo<T>` / `interface IBar<T>` 转 C++ 时，优先考虑 **`void*` 消除模板**，仅在以下情况保留模板：

#### 优先使用 `void*`（消除模板）

| 条件 | 示例 |
|------|------|
| TS 存储的是**引用/指针**语义（非值拷贝） | `Graves<T>` 存 `T \| undefined` → `void*` |
| 需要在**非模板容器**中异构存储 | `IAction_Base.tester` → `IExpression*` |
| 类型 `T` 仅作为上下文传递，内部 `static_cast` 还原 | `IJudger::run(void* ctx)` |
| 调用方始终知道具体类型 | `auto* p = static_cast<Bullet*>(pool.take())` |

```cpp
// ✅ void* 消除模板 — 对象池只存指针，不拥有对象
class Graves {
  void add(void *obj);
  void *take();           // 调用方 static_cast 还原
  std::vector<void *> _l; // 零模板开销
};
```

#### 保留模板

| 条件 | 示例 |
|------|------|
| 需要**值语义**（存储对象本身、非指针） | `Signal<Args...>` 存储参数包 |
| 需要**编译期类型安全**，避免错误 cast | `Fields<T>` 反射系统 |
| 编译期需要 `sizeof(T)` 或调用 `T` 的成员 | `std::vector<T>` |

```cpp
// ✅ 保留模板 — 反射系统需要编译期类型信息
template <typename T>
const auto &foo_fields() {
  static const auto fs = fields<T>(field("id", FieldKind::Str, &T::id));
  return fs;
}
```

#### 决策流程

```
TS 有 template<T>
    │
    ├─ T 是引用/指针语义？ ──是──→ 用 void* 消除模板
    │
    ├─ 需要存到非模板容器？ ──是──→ 用 void* 消除模板
    │
    └─ 需要值语义/类型安全？ ──是──→ 保留 template<T>
```

### 9. 依赖未转换文件时的最小化实现策略

当转换一个文件时，若其依赖的 TS 文件尚未转为 C++，**不应使用 `void*` 占位**，
而应创建一个**最小化 stub**，包含当前转换所需的最小接口。

#### 规则

1. 创建最小化 stub（仅含当前编译所需成员），标注 `/// TODO: 完整转换 pending`
2. stub 放在与被依赖 TS 文件对应的位置（`include/lfw-core/xxx/`）
3. stub 应能直接编译通过，后续逐步增补成员
4. 优先添加纯虚的 getter/setter，避免实现细节

#### 示例：Buff 依赖 Entity + World

```cpp
// ✅ 最小化 Entity stub（entity/Entity.hpp — 在已有基础上添加）
class Entity {
public:
  virtual const std::string &id() const = 0;  // Buff 需要
  // ... 已有成员保持不变
};

// ✅ 最小化 World stub（World.h — 新建）
class World {
public:
  Entity *find_entity(const std::string &eid);         // Buff.loop() 需要
  std::map<std::string, Buff *> buffs;                 // Buff.mount() 需要
};

// ❌ 错误：用 void* 占位
void *world = nullptr;
void *attacker() const;
```

#### 已有的最小化 stub

| 文件 | 说明 |
|------|------|
| `entity/Entity.hpp` | 实体基类（State_Base + Buff 共用，渐进式添加） |
| `World.h` | 游戏世界（Buff 系统所需的最小接口） |

---

## 构建与测试

```powershell
# 配置（Windows + vcpkg）
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="C:/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake"

# 编译
cmake --build build --config Debug

# 运行测试
.\build\tests\Debug\lfw-core-tests.exe
```

---

## 进度追踪

- 总体进度: [PROGRESS.md](./PROGRESS.md)
- defines 模块: [include/lfw-core/defines/PROGRESS.md](include/lfw-core/defines/PROGRESS.md)
- base 模块: [include/lfw-core/base/PROGRESS.md](include/lfw-core/base/PROGRESS.md)
- utils 模块: [include/lfw-core/utils/PROGRESS.md](include/lfw-core/utils/PROGRESS.md)

当前整体进度: **83/107 (78%)** defines 文件已转换。

---

## 新增文件 CheckList

转换一个新的 TS 文件时，按以下步骤操作:

1. [ ] 在 `include/lfw-core/defines/` 创建对应的 `.hpp`
2. [ ] 将 TS `interface` 字段逐一映射为 `std::optional<T>` 成员
3. [ ] 编写 `xxx_fields()` 反射函数
4. [ ] 更新 `defines/PROGRESS.md` 状态
5. [ ] 如需测试，在 `tests/` 添加对应 `test_xxx.cpp`
6. [ ] 编译验证: `cmake --build build --config Debug`
