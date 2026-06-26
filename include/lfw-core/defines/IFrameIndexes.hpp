#ifndef LFW_CORE_DEFINES_IFRAME_INDEXES_HPP
#define LFW_CORE_DEFINES_IFRAME_INDEXES_HPP

#include <optional>
#include <string>
#include <vector>

#include "IPairByFace.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// TFrameIdPair — 按朝向区分的帧 ID 对
using TFrameIdPair = IPairByFace<std::string>;

/// TFrameIdListPair — 按朝向区分的帧 ID 列表对
using TFrameIdListPair = IPairByFace<std::vector<std::string>>;

/// IFrameIndexes — 帧索引（快速定位特定帧 ID 的索引表）
struct IFrameIndexes
{
  std::optional<std::string> standing;
  std::optional<std::vector<std::string>> heavy_obj_walk;
  std::optional<std::string> landing_2;
  std::optional<std::string> landing_1;

  /// 角色眩晕动作的首个帧 ID
  std::optional<std::string> dizzy;

  /// 角色举起重物的首个帧 ID
  std::optional<std::string> picking_heavy;

  /// 角色拿起轻物的首个帧 ID
  std::optional<std::string> picking_light;

  std::optional<std::vector<std::string>> in_the_skys;
  std::optional<std::vector<std::string>> throwings;
  std::optional<std::vector<std::string>> on_hands;

  std::optional<TFrameIdListPair> falling;

  /// 速度较快摔到地上时弹起（-1: 面朝上, 1: 面朝下）
  std::optional<TFrameIdListPair> bouncing;

  std::optional<TFrameIdListPair> critical_hit;

  /// 角色受伤的帧 ID
  std::optional<TFrameIdPair> injured;

  std::optional<TFrameIdListPair> grand_injured;

  /// 角色躺在地上的帧 ID（-1: 面朝上, 1: 面朝下）
  std::optional<TFrameIdPair> lying;

  std::optional<std::vector<std::string>> fire;
  std::optional<std::string> ice;

  std::optional<std::string> on_ground;
  std::optional<std::string> just_on_ground;

  /// 武器丢到地上的帧
  std::optional<std::string> throw_on_ground;
};

LFW_NS_END

#endif
