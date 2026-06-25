# defines/ 目录 C++ 化难度评估

> 对应源目录: `little-fighter-j/src/LFW/defines/`
> 文件总数: ~100 个 `.ts` 文件

---

## ✅ 完成进度

| 类别 | 已转换 | 总数 | 状态 |
|------|--------|------|------|
| 🟢 enum 定义 | **43** | ~43 | ✅ **100%** |
| 🟢 简单 interface | 0 | ~40 | 🔴 |
| 🟡 有方法的 interface | 0 | ~5 | 🔴 |
| 🟡 复杂 interface | 0 | ~20 | 🔴 |
| 🔴 含 fields 反射 | 0 | ~10 | 🔴 |

## 分类总览

| 类别 | 文件数 | 难度 | 工作量 |
|------|--------|------|--------|
| 🟢 enum 定义 | ~43 | **极低** | 1 行 = 1 个枚举值 |
| 🟢 简单 interface (纯数据) | ~40 | **低** | 直译为 struct |
| 🟡 简单 interface (有方法) | ~5 | **中等** | 需转为 class |
| 🟡 复杂 interface (嵌套/import) | ~20 | **中等** | 需处理依赖关系 |
| 🔴 复杂 interface (含 fields) | ~10 | **高** | 需处理 Fields 反射 |

---

## 详细评估

### ✅ enum 定义（43 个文件 → 已全部完成）

全部合并为单个头文件 `include/lfw-core/defines/EnumTypes.hpp`，每个枚举均含 `*_to_string()` / `*_from_string()` 转换函数。

| # | C++ 枚举 | 对应 TS 文件 | 说明 |
|---|---------|-------------|------|
| 1 | `EntityType` | `EntityEnum.ts` | 实体类型位值 (Entity=4, Fighter=8, Weapon=16, Ball=32) |
| 2 | `EntityGroup` | `EntityGroup.ts` | 实体分组 (Hidden/Boss/Giant/Regular/...) |
| 3 | `EntityVal` | `EntityVal.ts` | 实体属性键 (TrendX/HP/MP/VX/...)，36 个值 |
| 4 | `StateType` | `StateEnum.ts` | 状态类型，~50 个值 |
| 5 | `TeamEnum` | `TeamEnum.ts` | 队伍 (Independent/Team_1~8) |
| 6 | `FacingFlag` | `FacingFlag.ts` | 朝向控制 (L/R/Ctrl/VX/Trend/...)，int8_t |
| 7 | `BdyKind` | `BdyKind.ts` | 身体碰撞类型 (Normal/Criminal/Defend/Ignore) |
| 8 | `CPointKind` | `CPointKind.ts` | 捕获点类型 (Attacker/Victim) |
| 9 | `OpointKind` | `OpointKind.ts` | 生成点类型 (Normal/Pick) |
| 10 | `OpointSpreading` | `OpointSpreading.ts` | 生成扩散模式 (Spreading/FloatRange/AngelBlessing) |
| 11 | `OpointMulti` | `OpointMulti.ts` | 生成倍数 (AccordingEnemies/AccordingAllies) |
| 12 | `WpointKind` | `WpointKind.ts` | 武器点类型 (None/Bearer/Holded/Drop) |
| 13 | `HitFlag` | `HitFlag.ts` | 攻击目标位域，支持 `\|` `&` 运算 |
| 14 | `ItrKind` | `ItrKind.ts` | 互动类型 (Normal/Catch/Pick/Heal/MagicFlute/...) |
| 15 | `ItrEffect` | `ItrEffect.ts` | 互动效果 (Sharp/Fire/Ice/Through/Explosion/...) |
| 16 | `FrameBehavior` | `FrameBehavior.ts` | 帧行为 (JohnChase/DennisChase/Boomerang/...) |
| 17 | `ArmorType` | `ArmorEnum.ts` | 装甲类型 (Defend/Fall/Times/Injury) |
| 18 | `SpeedMode` | `SpeedMode.ts` | 速度模式 (Acc/FixedLF2/FixedAcc/AccTo/...) |
| 19 | `SpeedCtrl` | `SpeedCtrl.ts` | 速度控制 (None/Control/Enable/Disable) |
| 20 | `CtrlDevice` | `CtrlDevice.ts` | 控制设备 (Keyboard/Gamepad1~4/TouchScreen) |
| 21 | `GameKey` | `GameKey.ts` | 按键枚举 (L/R/U/D/A/J/Z)，含冲突映射 |
| 22 | `Difficulty` | `Difficulty.ts` | 难度 (Easy=1/Normal/Difficult/Crazy) |
| 23 | `SyncRender` | `SyncRender.ts` | 渲染同步 (Unlimited/Half/Sync/FPS_60/FPS_120) |
| 24 | `StageGroup` | `StageGroup.ts` | 关卡分组 (Hidden/Dev) |
| 25 | `StageVal` | `StageVal.ts` | 关卡属性键 (EnemiesCleared/CurPhaseTime/PressAttack/...)，12 个值 |
| 26 | `WorldVal` | `WorldVal.ts` | 世界属性键 (test) |
| 27 | `BackgroundGroup` | `BackgroundGroup.ts` | 背景分组 (Regular/Hidden) |
| 28 | `WeaponType` | `WeaponType.ts` | 武器类型 (None/Stick/Heavy/Knife/Baseball/Drink) |
| 29 | `ActionType` | `ActionType.ts` | 动作回调类型 (a_sound/v_sound/fusion/broadcast/...)，19 个值 |
| 30 | `BinOp` | `BinOp.ts` | 条件运算符 (<, <=, ==, >=, >, !=, }}, {{, !}, !{) |
| 31 | `OID` | `OID.ts` | 内置对象 ID (Julian/Firzen/Davis/.../BrokenWeapon)，68 个值 |
| 32 | `BotState` | `BotStateEnum.ts` | AI 状态 (Idle/Avoiding/Chasing/Following/StageEnd/Dead) |
| 33 | `BotVal` | `BotVal.ts` | AI 属性键 (Desire/EnemyY/EnemyX/EnemyState/Safe/...)，9 个值 |
| 34 | `ChaseLost` | `ChaseLost.ts` | 追踪丢失行为 (Hover=1/Leave=2/End=4) |
| 35 | `ChaseStrategy` | `ChaseStrategy.ts` | 追踪策略 (Default/TillLost) |
| 36 | `TextureWrapping` | `TextureWrapping.ts` | 纹理环绕 (Repeat/ClampToEdge) |
| 37 | `MagnFilter` | `MagnFilter.ts` | 放大过滤 (Linear/Nearest) |
| 38 | `MinFilter` | `MinFilter.ts` | 缩小过滤 (LinearMipmapLinear/.../Nearest)，6 个值 |
| 39 | `SparkType` | `SparkEnum.ts` | 火花类型 (BrokenDefend/CriticalHit/Hit/Bleed/...)，10 个值 |
| 40 | `StageAction` | `StageActions.ts` | 关卡动作 (GoGoGoRight/EnterNextPhase/LoopGoGoGoRight) |
| 41 | `CheatType` | `CheatType.ts` | 作弊类型 (LF2_NET/HERO_FT/GIM_INK) |
| 42 | `CMD` | `CMD.ts` | 指令 (F1~F10/KILL_ENEMIES/CHANGE_BG/.../PAUSE)，24 个值 |
| 43 | `CollisionVal` | `CollisionVal.ts` | 碰撞判定键 (AttackerType/VictimState/BdyKind/...)，35 个值 |

---

### 🟢 简单 interface（纯数据，~40 个文件）

只有字段声明，无方法，无逻辑。直译为 C++ struct。

| 文件 | 关键字段 | 说明 |
|------|---------|------|
| `IPos.ts` | `x, y` | 2D 坐标 |
| `IVector2.ts` | `x, y` + 方法 | ⚠ 有方法，见下 |
| `IVector3.ts` | `x, y, z` + 方法 | ⚠ 有方法，见下 |
| `IVector4Like.ts` | `x, y, z, w` | 纯数据 |
| `IQuaternion.ts` | 四元数 + 方法 | ⚠ 有方法，见下 |
| `IRect.ts` | `x1, y1, x2, y2` | 矩形 |
| `IRectPair.ts` | 两个 rect | |
| `IBounding.ts` | 包围盒 | |
| `IQube.ts` | 3D 包围盒 | |
| `IQubePair.ts` | 两个 qube | |
| `IPairByFace.ts` | 按面配对 | |
| `IPicture.ts` | 图片引用 | |
| `IPictureInfo.ts` | 图片信息 | |
| `IFramePictureInfo.ts` | 帧图片信息 | |
| `ILegacyPictureInfo.ts` | 旧版图片信息 | |
| `IHitKeyCollection.ts` | 按键击中集合 | |
| `IHoldKeyCollection.ts` | 按键按住集合 | |
| `IBpointInfo.ts` | B 点信息 | |
| `ICpointInfo.ts` | C 点信息 | |
| `IOpointInfo.ts` | O 点信息 | |
| `IWpointInfo.ts` | W 点信息 | |
| `IBdyInfo.ts` | 身体碰撞信息 | |
| `IFrameIndexes.ts` | 帧索引集合 | |
| `INextFrame.ts` | 帧跳转信息 | |
| `IDeadJoin.ts` | 死亡连接 | |
| `IDialogInfo.ts` | 对话框信息 | |
| `IDrinkInfo.ts` | 饮酒信息 | |
| `TAction.ts` | 动作定义 | |
| `IStyle.ts` | 样式定义 | |
| `IModelInfo.ts` | 模型信息 | |
| `IFullGameZipInfo.ts` | 游戏包信息 | |
| `IBgData.ts` | 背景数据 | |
| `IBgInfo.ts` | 背景信息 | |
| `IBgLayerInfo.ts` | 背景层信息 | |
| `IChaseInfo.ts` | 追踪信息 | |
| `IArmorInfo.ts` | 装甲信息 | |
| `IBaseData.ts` | 基础数据 | |
| `IBotRay.ts` | AI 射线 | |
| `IRaycaster.ts` | 射线投射 | |
| `IDatContext.ts` | DAT 上下文 | |
| `IDatIndex.ts` | DAT 索引 | |
| `IDataLists.ts` | 数据列表 | |
| `IDataMap.ts` | 数据映射 | |
| `IEntityData.ts` | 实体数据 | |
| `IPurePlayerInfo.ts` | 纯玩家信息 | |
| `ISchema.ts` | Schema 定义 | |

**难度**: 🟢 极低 — 每文件 2~5 分钟，纯 struct

---

### 🟡 简单 interface（有方法，~5 个文件）

有字段 + 方法，需转为 class。

| 文件 | 方法 |
|------|------|
| `IVector2.ts` | `set()`, `add()`, `sub()`, `length()`, `clone()` |
| `IVector3.ts` | `set()`, `add()`, `sub()`, `length()`, `clone()` |
| `IQuaternion.ts` | 四元数运算 |
| `ITransform.ts` | 变换矩阵（可能在根目录） |

**难度**: 🟡 中等 — 可能需要 glm 或自定义数学库

---

### 🟡 复杂 interface（嵌套/import，~20 个文件）

引用了其他 interface 或 enum，需处理依赖关系。但本身无 fields 反射。

| 文件 | 依赖 | 说明 |
|------|------|------|
| `IItrInfo.ts` | `IQube`, `HitFlag`, `IExpression`, `TNextFrame`, `ItrKind`, `ItrEffect`, `TAction` | 碰撞交互信息，14 个可选字段 |
| `IFrameInfo.ts` | `IWorldDataset`, `IVelocityInfo` 等 ~20 个 import | 帧信息，最大最复杂的 interface |
| `IEntityInfo.ts` | `IWorldDataset` 等 | 实体信息 |
| `IStageInfo.ts` | 各类 stage 类型 | 关卡信息 |
| `IStageObjectInfo.ts` | | |
| `IStagePhaseInfo.ts` | | |
| `IBotData.ts` | `IBotAction` 等 | AI 数据 |
| `IBotDataSet.ts` | | AI 数据集 |
| `IBotAction.ts` | | AI 动作 |
| `IVelocityInfo.ts` | | 速度信息（被多处引用） |
| `Builtin_FrameId.ts` | | 内置帧 ID |
| `EMPTY_FRAME_INFO.ts` | `IFrameInfo` | 空帧常量 |
| `GONE_FRAME_INFO.ts` | `IFrameInfo` | 消失帧常量 |
| `defines.ts` | 各类 enum | 枚举汇总 re-export |

**难度**: 🟡 中等 — 需按依赖顺序转换，每文件 10~20 分钟

---

### 🔴 复杂 interface（含 fields 反射，~10 个文件）

除了类型定义外，还包含 `fields()` 调用（`int()`/`flt()`/`str()`/`any()` 等字段元数据）。

这些文件依赖 `Fields` 反射系统，转换后需要对接 `lfw-core/base/Fields.h`。

| 文件 | fields 调用体量 |
|------|----------------|
| `IWorldDataset.ts` | ~60+ 个字段，完整反射定义 |
| `IFrameInfo.ts` | ~40+ 个字段，含 velocity 字段 |
| `IEntityInfo.ts` | 中等 |
| `IItrInfo.ts` | 少量字段 |
| `IBdyInfo.ts` | 少量字段 |
| `IBpointInfo.ts` | 少量字段 |
| `ICpointInfo.ts` | 少量字段 |
| `IOpointInfo.ts` | 少量字段 |
| `IWpointInfo.ts` | 少量字段 |
| `IVelocityInfo.ts` | 少量字段 |

**难度**: 🔴 高 — 需要 `Fields.hpp` 支持，以及 `Partial<T>` → Resolver 模式

---

## 估算总工作量

| 类别 | 文件数 | 单文件 | 合计 |
|------|--------|--------|------|
| 🟢 enum | ~43 | 3 min | ~2 小时 |
| 🟢 简单 interface | ~40 | 3 min | ~2 小时 |
| 🟡 有方法的 interface | ~5 | 15 min | ~1 小时 |
| 🟡 复杂 interface | ~10 | 15 min | ~2.5 小时 |
| 🔴 含 fields 反射 | ~10 | 30 min | ~5 小时 |
| **合计** | **~108** | | **~12.5 小时** |

---

## 依赖顺序

```
                  ┌─────────────┐
                  │  enum 定义   │ ← 无依赖，最先转
                  └──────┬──────┘
                         │
                  ┌──────▼──────┐
                  │ 简单 interface │ ← 只依赖 enum
                  └──────┬──────┘
                         │
                  ┌──────▼──────┐
                  │ IWorldDataset │ ← 依赖 enum + Fields 反射
                  └──────┬──────┘
                         │
                  ┌──────▼──────┐
                  │ IFrameInfo    │ ← 依赖 IWorldDataset + IVelocityInfo
                  │ IEntityInfo   │    + 各类 sub-info
                  │ IItrInfo 等   │
                  └──────────────┘
```

---

## 建议策略

1. **先批量转 enum** — 43 个文件，写一个脚本或模板，批量生成 `enum class`
2. **再转简单 interface** — 纯 struct，可以直接写头文件
3. **`IWorldDataset` + `IVelocityInfo`** — 作为第一个含反射和回退模式的复杂类型，确定 Resolver 模式
4. **其余复杂类型** — 按依赖顺序逐个转换
5. **`IFrameInfo`** — 最复杂，放最后
