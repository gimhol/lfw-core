#ifndef LFW_CORE_DEFINES_OPOINTKIND_HPP
#define LFW_CORE_DEFINES_OPOINTKIND_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

// === OpointKind ===
#define OPOINT_KIND_ITEMS(X)                     \
  X(OpointKind, Normal, "normal", "普通", = 1)    \
  X(OpointKind, Pick, "pick", "拾取", = 2)

enum class OpointKind : uint8_t
{
  OPOINT_KIND_ITEMS(ENUM_ITEM)
};
constexpr auto OpointKind_MIN = OpointKind::Normal;
constexpr auto OpointKind_MAX = OpointKind::Pick;
GEN_ENUM_STR_MAP(OpointKindStringMap, OPOINT_KIND_ITEMS, OpointKind)
GEN_ENUM_NAME_MAP(OpointKindNameMap, OPOINT_KIND_ITEMS, OpointKind)
GEN_ENUM_DESC_MAP(OpointKindDescMap, OPOINT_KIND_ITEMS, OpointKind)
#undef OPOINT_KIND_ITEMS
DEFINE_ENUM_STR_CONVERTERS(opoint_kind_to_string, opoint_kind_from_string, OpointKind, OpointKindStringMap)
DEFINE_ENUM_STR_CONVERTERS(opoint_kind_to_name, opoint_kind_from_name, OpointKind, OpointKindNameMap)
DEFINE_ENUM_TO_STR(opoint_kind_to_desc, OpointKind, OpointKindDescMap)

// === OpointSpreading ===
#define OPOINT_SPREADING_ITEMS(X)                            \
  X(OpointSpreading, Normal, "normal", "普通", = 0)           \
  X(OpointSpreading, Spreading, "spreading", "扩散", = 1)     \
  X(OpointSpreading, FloatRange, "float_range", "浮动范围", = 2) \
  X(OpointSpreading, AngelBlessing, "angel_blessing", "天使祝福", = 4)

enum class OpointSpreading : uint8_t
{
  OPOINT_SPREADING_ITEMS(ENUM_ITEM)
};
constexpr auto OpointSpreading_MIN = OpointSpreading::Normal;
constexpr auto OpointSpreading_MAX = OpointSpreading::AngelBlessing;
GEN_ENUM_STR_MAP(OpointSpreadingStringMap, OPOINT_SPREADING_ITEMS, OpointSpreading)
GEN_ENUM_NAME_MAP(OpointSpreadingNameMap, OPOINT_SPREADING_ITEMS, OpointSpreading)
GEN_ENUM_DESC_MAP(OpointSpreadingDescMap, OPOINT_SPREADING_ITEMS, OpointSpreading)
#undef OPOINT_SPREADING_ITEMS
DEFINE_ENUM_STR_CONVERTERS(opoint_spreading_to_string, opoint_spreading_from_string, OpointSpreading, OpointSpreadingStringMap)
DEFINE_ENUM_STR_CONVERTERS(opoint_spreading_to_name, opoint_spreading_from_name, OpointSpreading, OpointSpreadingNameMap)
DEFINE_ENUM_TO_STR(opoint_spreading_to_desc, OpointSpreading, OpointSpreadingDescMap)

// === OpointMulti ===
#define OPOINT_MULTI_ITEMS(X)                                        \
  X(OpointMulti, AccordingEnemies, "according_enemies", "按敌人", = 0) \
  X(OpointMulti, AccordingAllies, "according_allies", "按队友", = 1)

enum class OpointMulti : uint8_t
{
  OPOINT_MULTI_ITEMS(ENUM_ITEM)
};
constexpr auto OpointMulti_MIN = OpointMulti::AccordingEnemies;
constexpr auto OpointMulti_MAX = OpointMulti::AccordingAllies;
GEN_ENUM_STR_MAP(OpointMultiStringMap, OPOINT_MULTI_ITEMS, OpointMulti)
GEN_ENUM_NAME_MAP(OpointMultiNameMap, OPOINT_MULTI_ITEMS, OpointMulti)
GEN_ENUM_DESC_MAP(OpointMultiDescMap, OPOINT_MULTI_ITEMS, OpointMulti)
#undef OPOINT_MULTI_ITEMS
DEFINE_ENUM_STR_CONVERTERS(opoint_multi_to_string, opoint_multi_from_string, OpointMulti, OpointMultiStringMap)
DEFINE_ENUM_STR_CONVERTERS(opoint_multi_to_name, opoint_multi_from_name, OpointMulti, OpointMultiNameMap)
DEFINE_ENUM_TO_STR(opoint_multi_to_desc, OpointMulti, OpointMultiDescMap)
#endif // LFW_CORE_DEFINES_OPOINTKIND_HPP
