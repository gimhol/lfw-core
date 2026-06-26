#ifndef LFW_CORE_DEFINES_IQUIBE_PAIR_HPP
#define LFW_CORE_DEFINES_IQUIBE_PAIR_HPP

#include "IPairByFace.hpp"
#include "IRect.hpp"

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IQubePair — 按朝向区分的立方体对
using IQubePair = IPairByFace<IQube>;

LFW_NS_END

#endif
