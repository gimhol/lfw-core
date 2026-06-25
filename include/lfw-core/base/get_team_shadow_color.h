#ifndef LFW_CORE_BASE_GET_TEAM_SHADOW_COLOR_H
#define LFW_CORE_BASE_GET_TEAM_SHADOW_COLOR_H

#include <string>

#include "lfw-core/core.hpp"
#include "lfw-core/defines/Defines.hpp"

LFW_NS_BEGIN

/**
 * 获取队伍描边颜色 — 对应 TS get_team_outline_color
 *
 * @param team 队伍枚举值或名称
 * @return     颜色字符串（如 "#000000"）
 */
inline std::string get_team_outline_color(TeamEnum team)
{
  auto it = Defines::TeamInfoMap.find(team);
  if (it == Defines::TeamInfoMap.end())
    it = Defines::TeamInfoMap.find(TeamEnum::Independent);
  return it->second.txt_outline_color;
}

/**
 * 获取队伍描边颜色（按字符串名称查找）— 对应 TS get_team_outline_color
 */
inline std::string get_team_outline_color(const std::string &team_name)
{
  for (const auto &[k, v] : Defines::TeamInfoMap)
  {
    if (v.i18n == team_name)
      return v.txt_outline_color;
  }
  auto it = Defines::TeamInfoMap.find(TeamEnum::Independent);
  return it->second.txt_outline_color;
}

LFW_NS_END

#endif
