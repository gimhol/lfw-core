#ifndef LFW_CORE_ENTITY_STAT_BAR_TYPE_H
#define LFW_CORE_ENTITY_STAT_BAR_TYPE_H

#include <cstdint>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// 状态栏类型 — 对应 TS StatBarType
enum class StatBarType : uint8_t
{
  None = 0,
  UI = 0b1,
  Float = 0b10
};

LFW_NS_END

#endif
