#ifndef LFW_CORE_DEFINES_IFRAME_INFO_HPP
#define LFW_CORE_DEFINES_IFRAME_INFO_HPP

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "IBdyInfo.hpp"
#include "IEntityInfo.hpp"
#include "IItrInfo.hpp"
#include "INextFrame.hpp"
#include "IVelocityInfo.hpp"

// 前向声明 — 待转换类型
struct IWpointInfo;
struct IBpointInfo;
struct IOpointInfo;
struct ICpointInfo;
struct IChaseInfo;
struct IHoldKeyCollection;
struct IHitKeyCollection;
struct IQubePair;

/// IFrameInfo — 帧信息
/// 对应 TS IFrameInfo extends Partial<IWorldDataset>, IVelocityInfo
struct IFrameInfo : IVelocityInfo
{
  // === 核心标识 ===
  std::optional<std::string> id;
  std::string name; ///< 帧名（TS 必填）

  // === 表现 ===
  std::optional<std::string> pic;   ///< 帧切图 ID（TODO: 完整 IFramePictureInfo 待转换）
  std::optional<std::string> sound; ///< 进入帧时播放的音效

  // === 状态 ===
  std::optional<int> state;   ///< 状态枚举（TS: number | StateEnum）
  std::optional<double> wait; ///< 帧持续时间
  std::optional<TNextFrame> next;      ///< 下一帧过渡

  // === 位置与尺寸 ===
  double centerx = 0; ///< 脚点 X（相对切图）
  double centery = 0; ///< 脚点 Y（相对切图）
  double width = 0;   ///< 帧宽度
  double height = 0;  ///< 帧高度

  // === 朝向 ===
  std::optional<int> facing; ///< @see FacingFlag

  // === 交互体 ===
  std::optional<std::vector<IItrInfo>> itr;   ///< 攻击碰撞体
  std::optional<std::vector<IBdyInfo>> bdy;   ///< 受击碰撞体
  IWpointInfo *wpoint = nullptr;              ///< 武器持有点（TODO: 待转换）
  IBpointInfo *bpoint = nullptr;              ///< 身体绑定点（TODO: 待转换）
  std::vector<IOpointInfo> *opoint = nullptr; ///< 发射点（TODO: 待转换）
  ICpointInfo *cpoint = nullptr;              ///< 抓取点（TODO: 待转换）

  // === 按键集合（TODO: 待转换） ===
  IHoldKeyCollection *hold = nullptr;
  IHitKeyCollection *hit = nullptr;
  IHoldKeyCollection *key_down = nullptr;
  IHoldKeyCollection *key_up = nullptr;

  // === 过渡（死亡/气竭/落地） ===
  std::optional<TNextFrame> on_dead;
  std::optional<TNextFrame> on_exhaustion;
  std::optional<TNextFrame> on_landing;
  std::optional<std::map<std::string, TNextFrame>> seqs;     ///< 按键→帧映射

  // === 物理 ===
  std::optional<int> invisible;        ///< 隐身帧数
  std::optional<int> no_shadow;        ///< 1=有影子 0=没影子
  std::optional<int> jump_flag;        ///< 起跳标志（角色专用）
  std::optional<bool> gravity_enabled; ///< 是否响应重力
  std::optional<int> landable;         ///< 0=穿透 1=落地

  // === 行为 ===
  std::optional<int> behavior; ///< @see FrameBehavior
  IChaseInfo *chase = nullptr; ///< 跟踪行为（TODO: 待转换）

  // === 特殊 ===
  std::optional<std::vector<std::string>> broadcasts; ///< 广播消息
  std::optional<std::string> hp_max;                  ///< 每帧HP消耗（字符串表达式）

  // === 属性覆盖（继承 Partial<IWorldDataset>） ===
  std::optional<IEntityInfo> data; ///< 本帧覆盖实体属性

  // === 运行时字段 ===
  IQubePair *indicator_info = nullptr;                               ///< 调试可视化（TODO: 待转换）
  double __aabb_x1 = 0, __aabb_x2 = 0, __aabb_z1 = 0, __aabb_z2 = 0; ///< 碰撞 AABB
  std::optional<std::map<std::string, TNextFrame>> seq_map;          ///< seqs 构建的查找表
};

#endif
