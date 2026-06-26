#ifndef LFW_CORE_DEFINES_IFRAME_INFO_HPP
#define LFW_CORE_DEFINES_IFRAME_INFO_HPP

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "IBdyInfo.hpp"
#include "IBpointInfo.hpp"
#include "IChaseInfo.hpp"
#include "ICpointInfo.hpp"
#include "IEntityInfo.hpp"
#include "IFramePictureInfo.hpp"
#include "IItrInfo.hpp"
#include "INextFrame.hpp"
#include "IOpointInfo.hpp"
#include "IQubePair.hpp"
#include "IVelocityInfo.hpp"
#include "IWpointInfo.hpp"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IFrameInfo — 帧信息
/// 对应 TS IFrameInfo extends Partial<IWorldDataset>, IVelocityInfo
struct IFrameInfo : IVelocityInfo
{
  // === 核心标识 ===
  std::string id;   ///< 帧ID（TS 必填，不可重复）
  std::string name; ///< 帧名（TS 必填）

  // === 表现 ===
  std::optional<IFramePictureInfo> pic; ///< 帧切图
  std::optional<std::string> sound;     ///< 进入帧时播放的音效

  // === 状态 ===
  int state = 0;   ///< 状态枚举（TS 必填: number | StateEnum）
  double wait = 0; ///< 帧持续时间（TS 必填）
  TNextFrame next; ///< 下一帧过渡（TS 必填）

  // === 位置与尺寸 ===
  double centerx = 0; ///< 脚点 X（相对切图）
  double centery = 0; ///< 脚点 Y（相对切图）
  double width = 0;   ///< 帧宽度
  double height = 0;  ///< 帧高度

  // === 朝向 ===
  std::optional<int> facing; ///< @see FacingFlag

  // === 交互体 ===
  std::optional<std::vector<IItrInfo>> itr;       ///< 攻击碰撞体
  std::optional<std::vector<IBdyInfo>> bdy;       ///< 受击碰撞体
  std::optional<IWpointInfo> wpoint;              ///< 武器持有点
  std::optional<IBpointInfo> bpoint;              ///< 身体绑定点
  std::optional<std::vector<IOpointInfo>> opoint; ///< 发射点
  std::optional<ICpointInfo> cpoint;              ///< 抓取点

  // === 按键集合 ===
  std::optional<std::unordered_map<std::string, TNextFrame>> hold;
  std::optional<std::unordered_map<std::string, TNextFrame>> hit;
  std::optional<std::unordered_map<std::string, TNextFrame>> key_down;
  std::optional<std::unordered_map<std::string, TNextFrame>> key_up;

  // === 过渡（死亡/气竭/落地） ===
  std::optional<TNextFrame> on_dead;
  std::optional<TNextFrame> on_exhaustion;
  std::optional<TNextFrame> on_landing;
  std::optional<std::unordered_map<std::string, TNextFrame>> seqs; ///< 按键→帧映射

  // === 物理 ===
  std::optional<int> invisible;        ///< 隐身帧数
  std::optional<int> no_shadow;        ///< 1=有影子 0=没影子
  std::optional<int> jump_flag;        ///< 起跳标志（角色专用）
  std::optional<bool> gravity_enabled; ///< 是否响应重力
  std::optional<int> landable;         ///< 0=穿透 1=落地

  // === 行为 ===
  std::optional<int> behavior;     ///< @see FrameBehavior
  std::optional<IChaseInfo> chase; ///< 跟踪行为

  // === 特殊 ===
  std::optional<std::vector<std::string>> broadcasts; ///< 广播消息
  std::optional<double> hp_max;                       ///< 每帧HP消耗（TS: number?）

  // === 属性覆盖（继承 Partial<IWorldDataset>） ===
  std::optional<IEntityInfo> data; ///< 本帧覆盖实体属性

  // === 运行时字段 ===
  std::optional<IQubePair> indicator_info;                            ///< 调试可视化
  double __aabb_x1 = 0, __aabb_x2 = 0, __aabb_z1 = 0, __aabb_z2 = 0;  ///< 碰撞 AABB
  std::optional<std::unordered_map<std::string, TNextFrame>> seq_map; ///< seqs 构建的查找表
};

LFW_NS_END

#endif
