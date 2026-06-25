#ifndef LFW_CORE_DEFINES_IPURE_PLAYER_INFO_HPP
#define LFW_CORE_DEFINES_IPURE_PLAYER_INFO_HPP

#include <string>
#include <unordered_map>

#include "CtrlDevice.hpp"
#include "GameKey.hpp"
#include "lfw-core/base/Fields.hpp"

/// IPurePlayerInfo — 纯玩家信息（不含运行时状态）
struct IPurePlayerInfo
{
  std::string id;
  std::string name;
  /// 按键映射：GameKey → 键名
  std::unordered_map<GameKey, std::string> keys;
  double version = 0;
  CtrlDevice ctrl = CtrlDevice::Keyboard;
};

inline const auto &pure_player_info_fields()
{
  static const auto fs = fields<IPurePlayerInfo>(
      field("id", FieldKind::Str, &IPurePlayerInfo::id, "ID"),
      field("name", FieldKind::Str, &IPurePlayerInfo::name, "名称"),
      field("keys", FieldKind::Map, &IPurePlayerInfo::keys, "按键映射"),
      field("version", FieldKind::Flt, &IPurePlayerInfo::version, "版本"),
      field("ctrl", FieldKind::Int, &IPurePlayerInfo::ctrl, "控制器"));
  return fs;
}

#endif
