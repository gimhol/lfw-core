#ifndef LFW_CORE_DEFINES_IRECT_PAIR_HPP
#define LFW_CORE_DEFINES_IRECT_PAIR_HPP

#include "IPairByFace.hpp"
#include "IRect.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IRectPair — 按朝向区分的矩形对
using IRectPair = IPairByFace<IRect>;

LFW_NS_END

#endif
