# AGENTS.md — lfw-core 项目 Agent 指南

> 本文档为 AI Agent 提供 lfw-core 项目的编码规范、转换模式和工作指引。

---

## 项目概述

`lfw-core` 是将 `little-fighter-j/src/LFW` 从 **TypeScript → C++** 的移植项目。

- **TS 源目录**: `C:\Users\Gimho\little-fighter-j\src\LFW\`
- **C++ 目标**: `C:\Users\Gimho\lfw-core\`
- **构建**: CMake + vcpkg（依赖 nlohmann-json）
- **测试框架**: doctest（`tests/` 目录）

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
#include "lfw-core/base/Fields.hpp"

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

### 5. 头文件保护

```cpp
#ifndef LFW_CORE_DEFINES_IFOO_HPP
#define LFW_CORE_DEFINES_IFOO_HPP
// ...
#endif
```

命名规则: `LFW_CORE_<目录大写>_<文件名大写>_HPP`

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
