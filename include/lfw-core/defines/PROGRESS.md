# defines/ 进度

> 枚举 + 接口定义，对应 TypeScript 的 `LFW/defines/`
>
> **TS 源目录**: `C:\Users\Gimho\little-fighter-j\src\LFW\defines\`（共 107 个 .ts 文件，不含 actions/）
> **C++ 目标目录**: `C:\Users\Gimho\lfw-core\include\lfw-core\defines\`

---

## 📊 总体统计

| 类别 | TS 文件数 | ✅ 已完成 | ⚠️ 部分完成 | ❌ 未转换 |
|---|---|---|---|---|
| 枚举 (Enum) | 44 | 42 (95%) | 2 (5%) | 1 (2%) |
| 接口 (Interface) | 59 | 32 (54%) | 9 (15%) | 16 (27%) |
| 特殊/工具文件 | 4 | 1 (25%) | 1 (25%) | 2 (50%) |
| **合计** | **107** | **75 (70%)** | **12 (11%)** | **20 (19%)** |

> Action 动作接口子目录：**17/17 文件 ✅ 全部完成**（详见 [actions/PROGRESS.md](actions/PROGRESS.md)）

---

## 一、枚举文件 (TS `enum` → C++ X-macro `enum class`)

### ✅ 已完成 (42)

| # | TS 文件 | TS 枚举名 | 条目 | C++ 文件 | C++ 枚举名 | 备注 |
|---|---|---|---|---|---|---|
| 1 | `ArmorEnum.ts` | `ArmorEnum` | 4 | `ArmorEnum.hpp` | `ArmorEnum` | + ALL_*, LABEL_MAP, DESC_MAP |
| 2 | `BackgroundGroup.ts` | `BackgroundGroup` | 2 | `BackgroundGroup.hpp` | `BackgroundGroup` | |
| 3 | `BdyKind.ts` | `BdyKind` | 4 | `BdyKind.hpp` | `BdyKind` | TS 有 OLD_* 常量，C++ 省略 |
| 4 | `BinOp.ts` | `BinOp` | 10 | `BinOp.hpp` | `BinOp` | TS 有 TBinOp 类型别名 |
| 5 | `BotStateEnum.ts` | `BotStateEnum` | 6 | `BotState.hpp` | `BotState` | 重命名：BotStateEnum→BotState |
| 6 | `BotVal.ts` | `BotVal` | 9 | `BotVal.hpp` | `BotVal` | 别名均为 BotStatus |
| 7 | `Builtin_FrameId.ts` | `Builtin_FrameId` | 7 | `Builtin_FrameId.hpp` | `Builtin_FrameId` | 别名 BFID 两边一致 |
| 8 | `ChaseLost.ts` | `ChaseLost` | 3(位标志) | `ChaseLost.hpp` | `ChaseLost` | |
| 9 | `ChaseStratedy.ts` | `ChaseStratedy` | 2 | `ChaseLost.hpp` | `ChaseStrategy` | ⚡ 合并到 ChaseLost.hpp |
| 10 | `CheatType.ts` | `CheatEnum` | 3 | `CheatType.hpp` | `CheatType` | 重命名：CheatEnum→CheatType |
| 11 | `CMD.ts` | `CMD`(const) | 24 | `CMD.hpp` | `CMD` | TS 有 CMD_NAMES，C++ 有 NameMap |
| 12 | `CollisionVal.ts` | `CollisionVal` | 35 | `CollisionVal.hpp` | `CollisionVal` | |
| 13 | `CPointKind.ts` | `CPointKind` | 2 | `CPointKind.hpp` | `CPointKind` | |
| 14 | `CtrlDevice.ts` | `CtrlDevice` | 6 | `CtrlDevice.hpp` | `CtrlDevice` | 字符串值差异：TS `gamepad_1`→C++ `gamepad1` |
| 15 | `Difficulty.ts` | `Difficulty` | 4 | `Difficulty.hpp` | `Difficulty` | TS 有 DifficultyNames |
| 16 | `EntityEnum.ts` | `EntityEnum` | 4(HitFlag位) | `EntityType.hpp` | `EntityType` | 重命名：EntityEnum→EntityType |
| 17 | `EntityGroup.ts` | `EntityGroup` | 10 | `EntityGroup.hpp` | `EntityGroup` | TS 有 Gaint 拼写错误，C++ 修正为 Giant |
| 18 | `EntityVal.ts` | `EntityVal` | 36 | `EntityVal.hpp` | `EntityVal` | TS: CAUGHT→C++: Caught; Holding_W_Type→HoldingWType |
| 19 | `FacingFlag.ts` | `FacingFlag` | 11 | `FacingFlag.hpp` | `FacingFlag` | 两边都有别名常量 |
| 20 | `FrameBehavior.ts` | `FrameBehavior` | 9 | `FrameBehavior.hpp` | `FrameBehavior` | |
| 21 | `GameKey.ts` | `GK` | 7 | `GameKey.hpp` | `GameKey` | TS 有 GKLabels, CONFLICTS_KEY_MAP, AGK；C++ 有 GameKeyLabelMap, GameKeyConflictMap |
| 22 | `HitFlag.ts` | `HitFlag` | ~20(位标志) | `HitFlag.hpp` | `HitFlag` | C++ 有 operator\|/\&, hit_flag_names |
| 23 | `ItrEffect.ts` | `ItrEffect` | 13 | `ItrEffect.hpp` | `ItrEffect` | ⚠️ TS 缺少 Explosion=23, Ice2=30, Ignore=10000 |
| 24 | `ItrKind.ts` | `ItrKind` | 13 | `ItrKind.hpp` | `ItrKind` | 值一致 |
| 25 | `OID.ts` | `OID` | ~64 | `OID.hpp` | `OID` | C++ 添加了中文描述 |
| 26 | `OpointKind.ts` | `OpointKind` | 2 | `OpointKind.hpp` | `OpointKind` | |
| 27 | `OpointMultiEnum.ts` | `OpointMultiEnum` | 2 | `OpointKind.hpp` | `OpointMulti` | ⚡ 合并到 OpointKind.hpp |
| 28 | `OpointSpreading.ts` | `OpointSpreading` | 4 | `OpointKind.hpp` | `OpointSpreading` | ⚡ 合并到 OpointKind.hpp |
| 29 | `SparkEnum.ts` | `SparkEnum` | 10 | `SparkType.hpp` | `SparkType` | 重命名：SparkEnum→SparkType |
| 30 | `SpeedCtrl.ts` | `SpeedCtrl` | 4 | `SpeedCtrl.hpp` | `SpeedCtrl` | |
| 31 | `SpeedMode.ts` | `SpeedMode` | 8 | `SpeedMode.hpp` | `SpeedMode` | |
| 32 | `StageActions.ts` | `StageActions` | 3 | `StageAction.hpp` | `StageAction` | 重命名：StageActions→StageAction |
| 33 | `StageGroup.ts` | `StageGroup` | 2 | `StageGroup.hpp` | `StageGroup` | |
| 34 | `StageVal.ts` | `StageVal` | 12 | `StageVal.hpp` | `StageVal` | |
| 35 | `StateEnum.ts` | `StateEnum` | ~50 | `StateType.hpp` | `StateType` | 重命名：StateEnum→StateType；TS 有 ATTCKING_STATES，C++ 有 attacking_states() |
| 36 | `SyncRenderEnum.ts` | `SyncRenderEnum` | 5 | `SyncRenderEnum.hpp` | `SyncRenderEnum` | |
| 37 | `TeamEnum.ts` | `TeamEnum` | 9 | `TeamEnum.hpp` | `TeamEnum` | TS 有 is_independent() |
| 38 | `TextureWrapping.ts` | `TextureWrapping` | 3 | `TextureWrapping.hpp` | `TextureWrapping` | TS 值来自 Three.js (1000,1001,1002)，C++ 用 0,1 |
| 39 | `WeaponType.ts` | `WeaponEnum` | 6 | `WeaponType.hpp` | `WeaponType` | 重命名：WeaponEnum→WeaponType |
| 40 | `WorldVal.ts` | `WorldVal` | 1(test) | `WorldVal.hpp` | `WorldVal` | |
| 41 | `WpointKind.ts` | `WpointKind` | 4 | `WpointKind.hpp` | `WpointKind` | |
| 42 | `IDatIndex.ts` | `DatTypeEnum` | 11 | `DatTypeEnum.hpp` | `DatTypeEnum` | + `dat_type_suffix()` 函数 |

### ⚠️ 部分完成 (2)

| # | TS 文件 | TS 导出 | C++ 文件 | C++ 导出 | 差异说明 |
|---|---|---|---|---|---|
| 43 | `MagnificationTextureFilter.ts` | `enum MagnificationTextureFilter` (2 值, WebGL 1003/1006) | `TextureWrapping.hpp` | `MagnFilter` (0/1) | ⚡ 合并到 TextureWrapping.hpp，值体系不同 |
| 44 | `MinificationTextureFilter.ts` | `enum MinificationTextureFilter` (6 值, WebGL 常量) | `TextureWrapping.hpp` | `MinFilter` (0-5) | ⚡ 合并到 TextureWrapping.hpp，值体系不同 |

### ❌ 未转换 (1)

| # | TS 文件 | TS 导出 | 说明 |
|---|---|---|---|
| 45 | `LF2Val.ts` | `enum LF2Val` (1 值: `test2`) | 低优先级，仅含一个值 |

---

## 二、接口文件 (TS `interface` → C++ `struct` with Fields)

### ✅ 已完成 (32)

| # | TS 文件 | TS 导出 | 字段数 | C++ 文件 | 备注 |
|---|---|---|---|---|---|
| 1 | `IArmorInfo.ts` | `interface IArmorInfo` | 13 | `IArmorInfo.hpp` | C++ 额外添加 hit_sounds, dead_sounds |
| 2 | `IBgInfo.ts` | `interface IBgInfo` | ~12 | `IBgInfo.hpp` | C++ 省略已弃用字段 shadowsize, zoom |
| 3 | `IBgLayerInfo.ts` | `interface IBgLayerInfo` | ~18 | `IBgLayerInfo.hpp` | TS 有 Schema_IBgLayerInfo |
| 4 | `IBpointInfo.ts` | `interface IBpointInfo` | ~5 | `IBpointInfo.hpp` | C++ 缺少 indicator_info |
| 5 | `IChaseInfo.ts` | `interface IChaseInfo` | 4 | `IChaseInfo.hpp` | 两边都有 new/factory 函数 |
| 6 | `IDeadJoin.ts` | `interface IDeadJoin` | 2 | `IDeadJoin.hpp` | |
| 7 | `IFramePictureInfo.ts` | `interface IFramePictureInfo` | 5 | `IFramePictureInfo.hpp` | 两边都有 fields 元数据 |
| 8 | `IModelInfo.ts` | `interface IModelInfo` | 5 | `IModelInfo.hpp` | TS: scale(IVector3Like), quaternion(IVector4Like)；C++: 扁平 scale_x/y/z，缺少 quaternion |
| 9 | `IPictureInfo.ts` | `interface IPictureInfo` | ~6 | `IPictureInfo.hpp` | |
| 10 | `IPos.ts` | `interface IPos` | 3 | —（已移除） | 改用 `IVector3Like` 替代，两者等价 |
| 11 | `IQube.ts` | `interface IQube extends IRect` | +2(z,l) | `IRect.hpp`(struct IQube:IRect) | ⚡ 定义在 IRect.hpp 中 |
| 12 | `IRect.ts` | `interface IRect` | 4 | `IRect.hpp` | |
| 13 | `ISchema.ts` | `IClazz`, `ISchemaPropertyTypes`, `IPropsMeta`, `ISchemaMeta`, `ISchema` | 复杂 | `ISchema.hpp` | 全面翻译 |
| 14 | `IStageInfo.ts` | `interface IStageInfo` | ~13 | `IStageInfo.hpp` | |
| 15 | `IStagePhaseInfo.ts` | `interface IStagePhaseInfo` | ~20 | `IStagePhaseInfo.hpp` | C++ 添加了回调字段 |
| 16 | `IVelocityInfo.ts` | `interface IVelocityInfo` | 12 | `IVelocityInfo.hpp` | |
| 17 | `IWpointInfo.ts` | `interface IWpointInfo` | ~10 | `IWpointInfo.hpp` | |
| 18 | `IWorldDataset.ts` | `interface IWorldDataset` | ~40 | `IWorldDataset.hpp` | 默认值对齐 |
| 19 | `IBaseData.ts` | `interface IBaseData<I>` (泛型, 4字段) | 3 | `IBaseData.hpp` | C++ 纯基类 struct（含 id/type/alias_id），子类继承扩展 |
| 20 | `IDatIndex.ts` | `DatTypeEnum`(11) + `IDatIndex`(8字段) + `ITempDatIndex` | 11+8+1 | `DatTypeEnum.hpp` + `IDatIndex.hpp` | 拆分为两个文件；`ITempDatIndex` 继承 `IDatIndex`；含 `fields()` 元数据 |
| 21 | `IBounding.ts` | `interface IBounding` | 6 | `IBounding.hpp` | 包围盒，含 `bounding_fields()` |
| 22 | `IVector2Like.ts` | `interface IVector2Like` | 2 | `IVector2Like.hpp` | 基础二维向量 |
| 23 | `IVector2.ts` | `interface IVector2 extends IVector2Like` | 2+6方法 | `IVector2.hpp` | 继承 IVector2Like，含 set/add/sub/length/clone/normalize/equals |
| 24 | `IVector3Like.ts` | `interface IVector3Like` | 3 | `IVector3Like.hpp` | 基础三维向量 |
| 25 | `IVector3.ts` | `interface IVector3 extends IVector3Like` | 3+7方法 | `IVector3.hpp` | 继承 IVector3Like，含 set/add/sub/copy/clone/normalize/equals |
| 26 | `IVector4Like.ts` | `interface IVector4Like` | 4 | `IVector4Like.hpp` | 基础四维向量 |
| 27 | `IDataMap.ts` | `interface IDataMap` (5个索引) | 5 | —（无需独立文件） | 使用 `std::map<std::string, T>` 替代 |
| 28 | `IExpression.ts` | `IJudger<T>`,`IValGetter<T>`,`IExpression<T1,T2>` | 复杂 | `IExpression.hpp` | 从 base/ 移至 defines/；`template<typename T> struct IExpression` |
| 29 | `IPairByFace.ts` | `interface IPairByFace<T>` (泛型) | 2 | `IPairByFace.hpp` | `template<typename T> struct IPairByFace { T left; T right; }`；-1=left, 1=right |
| 30 | `IPicture.ts` | `interface IPicture<T>` | 4 | `IPicture.hpp` | 非模板；`tex_id` 资源句柄，外部 TextureCache 管理 |
| 31 | `IBotRay.ts` | `interface IBotRay` | 8 | `IBotRay.hpp` | XZ 射线检测，含 `bot_ray_fields()` |
| 32 | `IBotAction.ts` | `interface IBotAction` | 9 | `IBotAction.hpp` | Bot 动作，含 `bot_action_fields()`；`judger` 用 `void*` |
| 33 | `IPurePlayerInfo.ts` | `interface IPurePlayerInfo` | 5 | `IPurePlayerInfo.hpp` | `keys` 用 `std::unordered_map<GameKey, string>` |

### ⚠️ 部分完成 (9)

| # | TS 文件 | TS 导出 | C++ 文件 | C++ 缺少的字段/差异 |
|---|---|---|---|---|
| 1 | `IBdyInfo.ts` | `interface IBdyInfo extends Partial<IQube>` (~14字段) | `IBdyInfo.hpp` | ❌ actions, code, tester, indicator_info, prefab_id |
| 2 | `ICpointInfo.ts` | `interface ICpointInfo` (~16字段) | `ICpointInfo.hpp` | ❌ vaction(TNextFrame), indicator_info |
| 3 | `IDialogInfo.ts` | `interface IDialogInfo` (~7字段) | `IDialogInfo.hpp` | ❌ hide_stats, end_test, end_testers；TS 有 DialogCloseBy 枚举 |
| 4 | `IDrinkInfo.ts` | `interface IDrinkInfo` (~12字段) | `IDrinkInfo.hpp` | ❌ hp_h_value, hp_h_ticks, hp_r_total, hp_r_value, hp_r_ticks, mp_h_value, mp_h_ticks（HP/MP 恢复详情） — C++ 高度简化，仅 5 个基础字段 |
| 5 | `IEntityInfo.ts` | `interface IEntityInfo extends Partial<IWorldDataset>` (~20字段) | `IEntityInfo.hpp` | ⚠️ 结构完全不同 — TS 是数据模板，C++ 是运行时实体状态 (id,name,oid,team,hp,mp,x/y/z,facing,state,weapons,is_bot) |
| 6 | `IFrameInfo.ts` | `interface IFrameInfo extends Partial<IWorldDataset>, IVelocityInfo` (~30字段) | `IFrameInfo.hpp` | ❌ 极度简化 — C++ 仅 6 字段: id, wait, pic, next, state, facing。缺少: name, centerx/y, width, height, sound, hp_max, hold, hit, key_down/up, seqs, bdy, itr, wpoint, bpoint, opoint, cpoint, invisible, no_shadow, jump_flag, on_dead, on_exhaustion, on_landing, behavior, chase + IWorldDataset 字段 |
| 7 | `IItrInfo.ts` | `interface IItrInfo extends Partial<IQube>` (~25字段) | `IItrInfo.hpp` | ❌ kind_name, effect_name, dvx/dvy/dvz, arest, catchingact, caughtact, on_hit_ground, actions, test, tester, code, ref, prefab_id, indicator_info, motionless, shaking |
| 8 | `IOpointInfo.ts` | `IOpointMulti`(4字段) + `IOpointInfo`(~15字段) | `IOpointInfo.hpp` | ❌ name, origin_type, action(TNextFrame), IOpointMulti 字段, facing 相关字段 |
| 9 | `IStageObjectInfo.ts` | `interface IStageObjectInfo` (~20字段) | `IStageObjectInfo.hpp` | ❌ hp_map, mp_map, times, ratio, is_boss, is_soldier, reserve, join, join_team, outline_color |

### ❌ 未转换 (16)

| # | TS 文件 | TS 导出 | 优先级 | 说明 |
|---|---|---|---|---|
| 1 | `IBgData.ts` | `interface IBgData` (6字段) | 高 | 背景数据结构；TS 有 bg_data_new(), Schema_IBgData |
| 2 | `IBotData.ts` | `interface IBotData` (5字段) | 高 | |
| 3 | `IBotDataSet.ts` | `interface IBotDataSet` (~25字段) | 中 | TS 有 fields 元数据 |
| 4 | `IDataLists.ts` | `IDataLists` + `ITempDataLists` (各4字段) | 高 | 数据列表结构 |
| 5 | `IDatContext.ts` | `interface IDatContext` (5字段) | 中 | 数据上下文 |
| 6 | `IEntityData.ts` | `IEntityData` + `TItrPrefabs` + `TBdyPrefabs` (9字段) | ⭐关键 | 核心实体数据结构；TS 有 entity_data_new() |
| 7 | `IFrameIndexes.ts` | `interface IFrameIndexes` (~20字段) | 高 | TS 有 frame_indexes_new() |
| 8 | `IFullGameZipInfo.ts` | `IBaseZipInfo`,`IGameZipInfo`,`IPrelZipInfo`,`IDataZipInfo`,`IAnyZipInfo` | 低 | ZIP 信息类型 |
| 9 | `IHitKeyCollection.ts` | `interface IHitKeyCollection` (~15字段) | 高 | 命中按键映射 |
| 10 | `IHoldKeyCollection.ts` | `interface IHoldKeyCollection` (9字段) | 高 | 按住按键映射 |
| 11 | `ILegacyPictureInfo.ts` | `interface ILegacyPictureInfo extends IPictureInfo` (+5字段) | 低 | TS 有 legacy_picture_info_fields |
| 12 | `INextFrame.ts` | `INextFrame extends IVelocityInfo`, `INextFrameResult`, `TNextFrame` (~12字段) | ⭐关键 | 核心帧过渡类型 |
| 13 | `IQubePair.ts` | `interface IQubePair extends IPairByFace<IQube>` | 中 | Qube 对类型 |
| 14 | `IRectPair.ts` | `interface IRectPair extends IPairByFace<IRect>` | 中 | Rect 对类型 |
| 15 | `IStyle.ts` | `interface IStyle` (~28字段) | 低 | Canvas 渲染样式 |

---

## 三、特殊/工具文件

| # | TS 文件 | TS 导出 | C++ 文件 | 状态 | 说明 |
|---|---|---|---|---|---|
| 1 | `index.ts` | Barrel re-exports (105 行) | `EnumTypes.hpp` | ✅ 完成 | 聚合头文件，包含所有枚举头文件 |
| 2 | `defines.ts` | `namespace Defines` (~60 常量、类型、VOID_BG, RANDOM_BG, VOID_STAGE, CheatInfos, Sounds 等) | `Defines.hpp` | ⚠️ 部分 | C++ 有: DATA_VERSION, 屏幕尺寸, 武器弹跳表, fall 值, armor 默认值, AI 常量, spreading 数组, Sounds, BuiltIn_*, Teams, TeamInfoMap, CheatInfo。缺少: VOID_BG, RANDOM_BG, VOID_STAGE, NEXT_FRAME_* 常量, DifficultyLabels, CheatInfos map |
| 3 | `EMPTY_FRAME_INFO.ts` | `const EMPTY_FRAME_INFO: IFrameInfo` | — | ❌ 未转换 | 帧信息常量 |
| 4 | `GONE_FRAME_INFO.ts` | `const GONE_FRAME_INFO: IFrameInfo` | — | ❌ 未转换 | 帧信息常量 |
| — | *(C++ only)* | — | `EnumHelper.hpp` | ✅ | X-macro 辅助宏 (GEN_ENUM_STR_MAP, DEFINE_ENUM_STR_CONVERTERS 等)，TS 无需对应 |

---

## 四、仅存在于 C++ 的文件（TS 无对应）

| # | C++ 文件 | 说明 |
|---|---|---|
| 1 | `EnumHelper.hpp` | X-macro 枚举-字符串转换辅助宏，C++ 基础设施 |

---

## 五、关键待办事项（按优先级）

### 🔴 关键（核心数据结构）

| 优先级 | TS 文件 | 原因 |
|---|---|---|
| ⭐⭐⭐ | `IEntityData.ts` | 核心实体数据模板，所有角色数据的基础 |
| ⭐⭐⭐ | `INextFrame.ts` | 核心帧过渡逻辑 |
| ⭐⭐⭐ | `IFrameInfo.ts` | 帧信息极度简化，C++ 仅 6/30 字段 |

### 🟡 高优先级

| TS 文件 | 原因 |
|---|---|
| `IBgData.ts` | 背景数据 |
| `IBotAction.ts`, `IBotData.ts` | Bot 系统 |
| `IDataLists.ts`, `IDataMap.ts` | 数据管理 |
| `IDatIndex.ts` | 数据索引 |
| `IFrameIndexes.ts` | 帧索引 |
| `IHitKeyCollection.ts`, `IHoldKeyCollection.ts` | 按键映射 |
| `IItrInfo.ts` (完善) | 交互信息缺失大量字段 |
| `IDrinkInfo.ts` (完善) | HP/MP 恢复详情缺失 |

### 🟢 中优先级

| TS 文件 | 原因 |
|---|---|
| `IBaseData.ts` | 泛型接口 |
| `IBotDataSet.ts`, `IBotRay.ts` | Bot 系统 |
| `IDatContext.ts` | 数据上下文 |
| `IPairByFace.ts` | 被多处使用的泛型 |
| `IQubePair.ts`, `IRectPair.ts` | 泛型对类型 |
| IVector 系列 (2/2Like/3/3Like/4Like) | 数学向量 |

### ⚪ 低优先级

| TS 文件 | 原因 |
|---|---|
| `LF2Val.ts` | 仅 1 个值 |
| `IBounding.ts` | 简单包围盒 |
| `IFullGameZipInfo.ts` | ZIP 信息 |
| `ILegacyPictureInfo.ts` | 遗留图片 |
| `IPicture.ts` | 图片接口 |
| `IStyle.ts` | Canvas 样式 |
| `EMPTY_FRAME_INFO.ts`, `GONE_FRAME_INFO.ts` | 常量数据 |

---

## 六、命名变更对照

| TS 原名 | C++ 新名 | 原因 |
|---|---|---|
| `BotStateEnum` | `BotState` | 简化 |
| `CheatEnum` | `CheatType` | 语义更清晰 |
| `EntityEnum` | `EntityType` | 语义更清晰 |
| `SparkEnum` | `SparkType` | 语义更清晰 |
| `StageActions` | `StageAction` | 单数命名 |
| `StateEnum` | `StateType` | 语义更清晰 |
| `WeaponEnum` | `WeaponType` | 语义更清晰 |
| `ChaseStratedy` (TS 拼写) | `ChaseStrategy` (C++ 修正) | 修正拼写错误 |
| `Gaint` (TS) | `Giant` (C++) | 修正拼写错误 |

## 七、合并文件对照

| TS 文件 (独立) | C++ 文件 (合并于) | 合并内容 |
|---|---|---|
| `ChaseStratedy.ts` | `ChaseLost.hpp` | ChaseLost + ChaseStrategy 枚举 |
| `OpointMultiEnum.ts` | `OpointKind.hpp` | OpointKind + OpointMulti 枚举 |
| `OpointSpreading.ts` | `OpointKind.hpp` | OpointKind + OpointSpreading 枚举 |
| `MagnificationTextureFilter.ts` | `TextureWrapping.hpp` | TextureWrapping + MagnFilter 枚举 |
| `MinificationTextureFilter.ts` | `TextureWrapping.hpp` | TextureWrapping + MinFilter 枚举 |

---

> 测试覆盖：263 个枚举值，全部通过。
