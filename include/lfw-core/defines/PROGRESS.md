# defines/ 进度

> 枚举 + 接口定义，对应 TypeScript 的 `LFW/defines/`

| 类别 | 完成 |
|---|---|
| 枚举（X-macro + StringMap/NameMap/DescMap） | ✅ 20 文件，19 枚举 |
| Action 动作接口 | [✅ 17 文件](actions/PROGRESS.md) |
| Info 数据结构（含 Fields 元数据） | ✅ 21 文件 |
| 其余接口类型 | 🔴 ~35 文件未转换 |

## 已完成枚举

| 文件 | 枚举 | 条目数 |
|---|---|---|
| `ArmorType.hpp` | `ArmorType` | 4 |
| `BackgroundGroup.hpp` | `BackgroundGroup` | 2 |
| `BdyKind.hpp` | `BdyKind` | 4 |
| `BinOp.hpp` | `BinOp` | 10 |
| `BotState.hpp` | `BotState` | 6 |
| `BotVal.hpp` | `BotVal` | 9 |
| `Builtin_FrameId.hpp` | `Builtin_FrameId` | 7 |
| `CMD.hpp` | `CMD` | 24 |
| `CPointKind.hpp` | `CPointKind` | 2 |
| `ChaseLost.hpp` | `ChaseLost` + `ChaseStrategy` | 3+2 |
| `CheatType.hpp` | `CheatType` | 3 |
| `CollisionVal.hpp` | `CollisionVal` | 35 |
| `CtrlDevice.hpp` | `CtrlDevice` | 6 |
| `Difficulty.hpp` | `Difficulty` | 4 |
| `EntityGroup.hpp` | `EntityGroup` | 10 |
| `EntityType.hpp` | `EntityType` | 4 |
| `EntityVal.hpp` | `EntityVal` | 36 |
| `FacingFlag.hpp` | `FacingFlag` | 11 |
| `FrameBehavior.hpp` | `FrameBehavior` | 9 |
| `GameKey.hpp` | `GameKey` | 7 |

> 测试覆盖：263 个值，全部通过。
