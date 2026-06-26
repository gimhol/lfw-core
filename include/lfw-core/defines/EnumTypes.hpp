#ifndef LFW_CORE_DEFINES_ENUMTYPES_HPP
#define LFW_CORE_DEFINES_ENUMTYPES_HPP

// ========================================================================
// 聚合头文件 — 包含所有拆分的枚举定义
// 直接 include 各独立文件即可使用对应枚举
// ========================================================================

// 实体/状态
#include "EntityType.hpp"
#include "EntityGroup.hpp"
#include "EntityVal.hpp"
#include "StateType.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 队伍/朝向
#include "TeamEnum.hpp"
#include "FacingFlag.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 碰撞
#include "BdyKind.hpp"
#include "CPointKind.hpp"
#include "OpointKind.hpp"
#include "WpointKind.hpp"
#include "HitFlag.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// Itr
#include "ItrKind.hpp"
#include "ItrEffect.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 行为/动作
#include "FrameBehavior.hpp"
#include "ArmorEnum.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 速度/控制
#include "SpeedMode.hpp"
#include "SpeedCtrl.hpp"
#include "CtrlDevice.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 按键
#include "GameKey.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 世界/关卡
#include "Difficulty.hpp"
#include "SyncRenderEnum.hpp"
#include "StageGroup.hpp"
#include "StageVal.hpp"
#include "WorldVal.hpp"
#include "BackgroundGroup.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 武器
#include "WeaponType.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 动作/回调
#include "actions/ActionType.hpp"
#include "BinOp.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// OID
#include "OID.hpp"
#include "Builtin_FrameId.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// AI
#include "BotState.hpp"
#include "BotVal.hpp"
#include "ChaseLost.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 纹理
#include "TextureWrapping.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 火花/关卡动作
#include "SparkType.hpp"
#include "StageAction.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 作弊/指令
#include "CheatType.hpp"
#include "CMD.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// 碰撞判定值
#include "CollisionVal.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

LFW_NS_END

#endif // LFW_CORE_DEFINES_ENUMTYPES_HPP
