# TS 枚举 → C++ 转换规范

> 本文档描述将 TypeScript `enum` 转换为 C++ X-macro `enum class` 的标准流程。

---

## 一、TS 枚举模式

```typescript
// 模式1：数字枚举
export enum Difficulty { Easy, Normal, Hard, Crazy }

// 模式2：字符串枚举（TS 独有）
export enum DatTypeEnum {
  Fighter = "0",
  Background = "bg",
}

// 模式3：const enum
export const enum CMD { Attack = 0, Jump = 1, ... }
```

## 二、C++ X-macro 模板

```cpp
#ifndef LFW_CORE_DEFINES_XXX_HPP
#define LFW_CORE_DEFINES_XXX_HPP

#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

/* 格式: X(枚举类型, 枚举名, "字符串值", "描述", 值) */
#define ENUM_ITEMS(X)                          \
  X(MyEnum, Value1, "string_val", "描述", = 0) \
  X(MyEnum, Value2, "",           "描述", = 1)

enum class MyEnum : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(MyStringMap, ENUM_ITEMS, MyEnum)
GEN_ENUM_NAME_MAP(MyNameMap, ENUM_ITEMS, MyEnum)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(my_to_string, my_from_string, MyEnum, MyStringMap)
DEFINE_ENUM_STR_CONVERTERS(my_to_name, my_from_name, MyEnum, MyNameMap)

#endif
```

### X-macro 字段说明

| 字段 | 含义 | 示例 |
| --- | --- | --- |
| 枚举类型 | C++ enum class 名 | `Difficulty` |
| 枚举名 | 条目标识符 | `Easy` |
| 字符串值 | TS 中的字符串值（数字枚举用 `""`） | `"bg"`, `"0"` |
| 描述 | 中文说明 | `"简单"` |
| 值 | 数字值 | `= 0`, `= 1` |

### 宏速查

| 宏 | 生成内容 |
| --- | --- |
| `ENUM_ITEM` | 枚举条目展开（`Value = 0,`） |
| `GEN_ENUM_STR_MAP(MAP, ITEMS, ENUM)` | `unordered_map<ENUM, string>` — 枚举→字符串值 |
| `GEN_ENUM_NAME_MAP(MAP, ITEMS, ENUM)` | `unordered_map<ENUM, string>` — 枚举→C++ 枚举名 |
| `DEFINE_ENUM_STR_CONVERTERS(to, from, ENUM, MAP)` | `string_view to(ENUM)` + `optional<ENUM> from(string_view)` |
| `DEFINE_ENUM_TO_STR(fn, ENUM, MAP)` | `string_view fn(ENUM)`（单向查找） |

---

## 三、转换步骤

### 步骤 1：确定 C++ 命名

- 去掉 TS 中冗余的 `Enum` 后缀：`BotStateEnum` → `BotState`
- 用 `Type` 替代 `Enum`：`EntityEnum` → `EntityType`、`StateEnum` → `StateType`
- 修正 TS 拼写错误：`ChaseStratedy` → `ChaseStrategy`、`Gaint` → `Giant`
- 文件命名：`MyEnum.hpp`

### 步骤 2：填写 X-macro 条目

TS 为数字枚举时，字符串值填 `""`：

```cpp
X(Difficulty, Easy,   "", "简单", = 0)
```

TS 为字符串枚举时，字符串值填 TS 的值：

```cpp
X(DatEnum, Background, "bg", "背景", = 8)
```

### 步骤 3：选择整数基类型

| 条目数 | 类型 |
| --- | --- |
| ≤ 256 | `uint8_t` |
| ≤ 65536 | `uint16_t` |
| 其他 | `int`（默认） |

### 步骤 4：附加函数/数据

TS 中的辅助常量/函数在 C++ 中按需添加：

```cpp
// TS: export const ALL_ARMORS = [Defend, Fall, ...];
inline constexpr ArmorEnum ALL_ARMORS[] = { ArmorEnum::Defend, ... };

// TS: Record<Enum, string> → 另建 X-macro
#define SUFFIX_ITEMS(X) ...
GEN_ENUM_STR_MAP(MySuffixMap, SUFFIX_ITEMS, MyEnum)
DEFINE_ENUM_TO_STR(my_suffix, MyEnum, MySuffixMap)
```

### 步骤 5：更新 PROGRESS.md

在枚举"已完成"表末尾添加条目。

---

## 四、完整示例

### TS 源

```typescript
export enum Difficulty {
  Easy   = 0,
  Normal = 1,
  Hard   = 2,
  Crazy  = 3,
}
export const DifficultyNames: Record<Difficulty, string> = {
  [Difficulty.Easy]:   "简单",
  [Difficulty.Normal]: "普通",
  [Difficulty.Hard]:   "困难",
  [Difficulty.Crazy]:  "疯狂",
};
```

### C++ 转换

```cpp
#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                       \
  X(Difficulty, Easy,   "", "简单", = 0)   \
  X(Difficulty, Normal, "", "普通", = 1)   \
  X(Difficulty, Hard,   "", "困难", = 2)   \
  X(Difficulty, Crazy,  "", "疯狂", = 3)

enum class Difficulty : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(DifficultyStringMap, ENUM_ITEMS, Difficulty)
GEN_ENUM_NAME_MAP(DifficultyNameMap, ENUM_ITEMS, Difficulty)
GEN_ENUM_DESC_MAP(DifficultyDescMap, ENUM_ITEMS, Difficulty)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(difficulty_to_string, difficulty_from_string, Difficulty, DifficultyStringMap)
DEFINE_ENUM_STR_CONVERTERS(difficulty_to_name, difficulty_from_name, Difficulty, DifficultyNameMap)
DEFINE_ENUM_TO_STR(difficulty_to_desc, Difficulty, DifficultyDescMap)
```

---

## 五、命名变更对照（已积累）

| TS 原名 | C++ 新名 | 原因 |
| --- | --- | --- |
| `BotStateEnum` | `BotState` | 去冗余后缀 |
| `CheatEnum` | `CheatType` | Enum→Type |
| `EntityEnum` | `EntityType` | Enum→Type |
| `SparkEnum` | `SparkType` | Enum→Type |
| `StageActions` | `StageAction` | 单数命名 |
| `StateEnum` | `StateType` | Enum→Type |
| `WeaponEnum` | `WeaponType` | Enum→Type |
| `DatTypeEnum` | `DatEnum` | 去冗余 Type |
| `ChaseStratedy` | `ChaseStrategy` | 修正拼写 |
| `Gaint` | `Giant` | 修正拼写 |

---

## 六、文件合并规则

以下 TS 独立枚举在 C++ 中合并到关联头文件：

| TS 文件 | 合并到 | 内容 |
| --- | --- | --- |
| `ChaseStratedy.ts` | `ChaseLost.hpp` | `ChaseStrategy` |
| `OpointMultiEnum.ts` | `OpointKind.hpp` | `OpointMulti` |
| `OpointSpreading.ts` | `OpointKind.hpp` | `OpointSpreading` |
| `MagnificationTextureFilter.ts` | `TextureWrapping.hpp` | `MagnFilter` |
| `MinificationTextureFilter.ts` | `TextureWrapping.hpp` | `MinFilter` |

---

## 七、当前进度

- ✅ 已完成：42 个枚举
- ⚠️ 部分完成：2 个
- ❌ 未转换：1 个（`LF2Val.ts`）

详见 [PROGRESS.md](PROGRESS.md)。
