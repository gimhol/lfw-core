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

// 队伍/朝向
#include "TeamEnum.hpp"
#include "FacingFlag.hpp"

// 碰撞
#include "BdyKind.hpp"
#include "CPointKind.hpp"
#include "OpointKind.hpp"
#include "WpointKind.hpp"
#include "HitFlag.hpp"

// Itr
#include "ItrKind.hpp"
#include "ItrEffect.hpp"

// 行为/动作
#include "FrameBehavior.hpp"
#include "ArmorType.hpp"

// 速度/控制
#include "SpeedMode.hpp"
#include "SpeedCtrl.hpp"
#include "CtrlDevice.hpp"

// 按键
#include "GameKey.hpp"

// 世界/关卡
#include "Difficulty.hpp"
#include "SyncRender.hpp"
#include "StageGroup.hpp"
#include "StageVal.hpp"
#include "WorldVal.hpp"
#include "BackgroundGroup.hpp"

// 武器
#include "WeaponType.hpp"

// 动作/回调
#include "ActionType.hpp"
#include "BinOp.hpp"

// OID
#include "OID.hpp"

// AI
#include "BotState.hpp"
#include "BotVal.hpp"
#include "ChaseLost.hpp"

// 纹理
#include "TextureWrapping.hpp"

// 火花/关卡动作
#include "SparkType.hpp"
#include "StageAction.hpp"

// 作弊/指令
#include "CheatType.hpp"
#include "CMD.hpp"

// 碰撞判定值
#include "CollisionVal.hpp"

#endif // LFW_CORE_DEFINES_ENUMTYPES_HPP
