#ifndef LFW_CORE_DEFINES_SYNC_RENDER_ENUM_HPP
#define LFW_CORE_DEFINES_SYNC_RENDER_ENUM_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                                      \
  X(SyncRenderEnum, Unlimited, "unlimited", "无限制", = 0) \
  X(SyncRenderEnum, Half, "half", "半速", = 1)             \
  X(SyncRenderEnum, Sync, "sync", "同步", = 2)             \
  X(SyncRenderEnum, FPS_60, "fps_60", "60帧", = 3)         \
  X(SyncRenderEnum, FPS_120, "fps_120", "120帧", = 4)

enum class SyncRenderEnum : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
constexpr auto SyncRenderEnum_MIN = SyncRenderEnum::Unlimited;
constexpr auto SyncRenderEnum_MAX = SyncRenderEnum::FPS_120;
GEN_ENUM_STR_MAP(SyncRenderEnumStringMap, ENUM_ITEMS, SyncRenderEnum)
GEN_ENUM_NAME_MAP(SyncRenderEnumNameMap, ENUM_ITEMS, SyncRenderEnum)
GEN_ENUM_DESC_MAP(SyncRenderEnumDescMap, ENUM_ITEMS, SyncRenderEnum)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(sync_render_enum_to_string, sync_render_enum_from_string, SyncRenderEnum, SyncRenderEnumStringMap)
DEFINE_ENUM_STR_CONVERTERS(sync_render_enum_to_name, sync_render_enum_from_name, SyncRenderEnum, SyncRenderEnumNameMap)
DEFINE_ENUM_TO_STR(sync_render_enum_to_desc, SyncRenderEnum, SyncRenderEnumDescMap)
#endif // LFW_CORE_DEFINES_SYNC_RENDER_ENUM_HPP
