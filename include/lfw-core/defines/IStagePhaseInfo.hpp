#ifndef LFW_CORE_DEFINES_ISTAGE_PHASE_INFO_HPP
#define LFW_CORE_DEFINES_ISTAGE_PHASE_INFO_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "lfw-core/base/Expression.h"
#include "lfw-core/defines/Difficulty.hpp"
#include "lfw-core/defines/IDialogInfo.hpp"
#include "lfw-core/defines/IStageObjectInfo.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// StageSoundInfo — 关卡音效信息
struct StageSoundInfo
{
  std::string path;
  std::optional<double> x, y, z;
};

/// IStagePhaseInfo — 关卡阶段信息，对应 TS IStagePhaseInfo
struct IStagePhaseInfo
{
  std::optional<std::string> title;
  double bound = 0; ///< @deprecated 已弃用

  // === 边界 ===
  std::optional<double> player_l, player_r; ///< 玩家边界
  std::optional<double> camera_l, camera_r; ///< 相机边界
  std::optional<double> enemy_l, enemy_r;   ///< 敌人边界
  std::optional<double> drink_l, drink_r;   ///< 饮料边界

  std::optional<std::string> desc; ///< 关卡描述

  // === 物件 / 对话框 ===
  std::optional<std::vector<IStageObjectInfo>> objects;
  std::optional<std::vector<IDialogInfo>> dialogs;

  // === 音频 ===
  std::optional<std::string> music; ///< 背景音乐（空串=停止当前）
  std::optional<std::vector<StageSoundInfo>> sounds;

  // === 重生 / 补给（按难度） ===
  using DiffMap = std::unordered_map<Difficulty, double>;
  std::optional<DiffMap> respawn, respawn_r, respawn_x;
  std::optional<DiffMap> health_up, mp_up;

  // === 跳转 ===
  std::optional<double> cam_jump_to_x;
  std::optional<double> player_jump_to_x, player_jump_to_z;
  std::optional<int> player_facing; ///< -1=左, 1=右

  // === 测试 / 动作 ===
  std::optional<std::vector<std::string>> end_test;                     ///< 结束判定表达式
  std::optional<std::vector<std::unique_ptr<IExpression>>> end_testers; ///< 结束测试器
  std::optional<std::vector<std::string>> on_start;                     ///< 开始时动作
  std::optional<std::vector<std::string>> on_end;                       ///< 结束时动作

  // === 开关 ===
  std::optional<int> hide_stats;           ///< 隐藏状态栏
  std::optional<int> world_pause;          ///< 世界暂停
  std::optional<int> control_disabled;     ///< 禁用控制
  std::optional<int> weapon_rain_disabled; ///< 禁用武器雨
};

LFW_NS_END

#endif
