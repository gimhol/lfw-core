#ifndef LFW_CORE_ENTITY_FIND_FRAME_DIRECTION_H
#define LFW_CORE_ENTITY_FIND_FRAME_DIRECTION_H

#include <string>
#include <vector>

#include "lfw-core/core.hpp"
#include "lfw-core/defines/IFrameInfo.hpp"

LFW_NS_BEGIN

/// 帧方向对（-1 方向帧ID列表, 1 方向帧ID列表）
/// 对应 TS TFrameIdListPair / TFrameIdPair
struct FrameIdDirectionPair
{
  std::vector<std::string> neg; // -1 方向
  std::vector<std::string> pos; // 1 方向
};

/// 查找当前帧属于哪个方向 — 对应 TS find_direction
/// @return -1=反向帧, 1=正向帧, 0=未匹配
inline int find_direction(const IFrameInfo &f, const FrameIdDirectionPair *pair)
{
  if (!pair || !f.id.has_value())
    return 0;

  const auto &fid = *f.id;
  for (const auto &v : pair->neg)
    if (v == fid)
      return -1;
  for (const auto &v : pair->pos)
    if (v == fid)
      return 1;
  return 0;
}

LFW_NS_END

#endif
