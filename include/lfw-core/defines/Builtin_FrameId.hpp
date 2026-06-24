#ifndef LFW_CORE_DEFINES_BUILTIN_FRAME_ID_HPP
#define LFW_CORE_DEFINES_BUILTIN_FRAME_ID_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

/// Builtin_FrameId — 内置帧 ID（字符串枚举）
#define ENUM_ITEMS(X)                             \
  X(Builtin_FrameId, None, "", "", = 0)           \
  X(Builtin_FrameId, Auto, "auto", "", )          \
  X(Builtin_FrameId, Self, "self", "", )          \
  X(Builtin_FrameId, Gone, "gone", "", )          \
  X(Builtin_FrameId, Invisible_Min, "1100", "", ) \
  X(Builtin_FrameId, Invisible_Max, "1299", "", ) \
  X(Builtin_FrameId, Respawn, "respawn", "", )

#define ENUM_ITEM(ENUM, NAME, STR, DESC, VAL) NAME VAL,
enum class Builtin_FrameId : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(Builtin_FrameIdStringMap, ENUM_ITEMS, Builtin_FrameId)
GEN_ENUM_NAME_MAP(Builtin_FrameIdNameMap, ENUM_ITEMS, Builtin_FrameId)
GEN_ENUM_DESC_MAP(Builtin_FrameIdDescMap, ENUM_ITEMS, Builtin_FrameId)
#undef ENUM_ITEM
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(builtin_frame_id_to_string, builtin_frame_id_from_string, Builtin_FrameId, Builtin_FrameIdStringMap)
DEFINE_ENUM_STR_CONVERTERS(builtin_frame_id_to_name, builtin_frame_id_from_name, Builtin_FrameId, Builtin_FrameIdNameMap)
DEFINE_ENUM_TO_STR(builtin_frame_id_to_desc, Builtin_FrameId, Builtin_FrameIdDescMap)

/// 别名
using BFID = Builtin_FrameId;

#endif
