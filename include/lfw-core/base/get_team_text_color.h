#ifndef LFW_CORE_BASE_GET_TEAM_TEXT_COLOR_H
#define LFW_CORE_BASE_GET_TEAM_TEXT_COLOR_H

#include <string>

#include "lfw-core/core.hpp"
#include "lfw-core/defines/Defines.hpp"

LFW_NS_BEGIN

/**
 * 获取队伍文字颜色 — 对应 TS get_team_text_color
 *
 * @param team     队伍枚举值
 * @param fallback 未找到时的回退颜色
 * @return         颜色字符串（如 "#ffffff"）
 */
inline std::string get_team_text_color(
    TeamEnum team,
    const std::string &fallback = Defines::TeamInfoMap.at(TeamEnum::Independent).txt_color)
{
  auto it = Defines::TeamInfoMap.find(team);
  if (it == Defines::TeamInfoMap.end() || !it->second.txt_color)
    return fallback;
  return it->second.txt_color;
}

/**
 * 获取队伍文字颜色（按字符串名称查找）— 对应 TS get_team_text_color
 */
inline std::string get_team_text_color(
    const std::string &team_name,
    const std::string &fallback = Defines::TeamInfoMap.at(TeamEnum::Independent).txt_color)
{
  for (const auto &[k, v] : Defines::TeamInfoMap)
  {
    if (v.i18n == team_name && v.txt_color)
      return v.txt_color;
  }
  return fallback;
}

LFW_NS_END

#endif
