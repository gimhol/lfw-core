#ifndef LFW_CORE_DEFINES_IPICTURE_HPP
#define LFW_CORE_DEFINES_IPICTURE_HPP

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#include <string>

/// IPicture — 图片信息
/// tex_id 为资源句柄，由外部 TextureCache 统一管理
struct IPicture
{
  std::string id;
  double w = 0;
  double h = 0;
  std::string tex_id;
};


LFW_NS_END

#endif
