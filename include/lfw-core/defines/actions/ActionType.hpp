#ifndef LFW_CORE_DEFINES_ACTIONTYPE_HPP
#define LFW_CORE_DEFINES_ACTIONTYPE_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "lfw-core/defines/EnumHelper.hpp"

#define ENUM_ITEMS(X)                                     \
  X(ActionType, A_SOUND, "A_SOUND", "", )                 \
  X(ActionType, A_NEXT_FRAME, "A_NEXT_FRAME", "", )       \
  X(ActionType, A_SET_PROP, "A_SET_PROP", "", )           \
  X(ActionType, A_DEFEND, "A_DEFEND", "", )               \
  X(ActionType, A_BROKEN_DEFEND, "A_BROKEN_DEFEND", "", ) \
  X(ActionType, V_SOUND, "V_SOUND", "", )                 \
  X(ActionType, V_NEXT_FRAME, "V_NEXT_FRAME", "", )       \
  X(ActionType, V_SET_PROP, "V_SET_PROP", "", )           \
  X(ActionType, V_DEFEND, "V_DEFEND", "", )               \
  X(ActionType, V_BROKEN_DEFEND, "V_BROKEN_DEFEND", "", ) \
  X(ActionType, A_REBOUND_VX, "A_REBOUND_VX", "", )       \
  X(ActionType, V_REBOUND_VX, "V_REBOUND_VX", "", )       \
  X(ActionType, V_TURN_FACE, "V_TURN_FACE", "", )         \
  X(ActionType, V_TURN_TEAM, "V_TURN_TEAM", "", )         \
  X(ActionType, FUSION, "FUSION", "", )                   \
  X(ActionType, BROADCAST, "BROADCAST", "", )             \
  X(ActionType, VALUE_STEAL, "VALUE_STEAL", "", )         \
  X(ActionType, A_BUFF, "A_BUFF", "", )                   \
  X(ActionType, V_BUFF, "V_BUFF", "", )                   \
  X(ActionType, ERROR, "ERROR", "", )

enum class ActionType : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(ActionTypeStringMap, ENUM_ITEMS, ActionType)
GEN_ENUM_NAME_MAP(ActionTypeNameMap, ENUM_ITEMS, ActionType)
GEN_ENUM_DESC_MAP(ActionTypeDescMap, ENUM_ITEMS, ActionType)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(action_type_to_string, action_type_from_string, ActionType, ActionTypeStringMap)
DEFINE_ENUM_STR_CONVERTERS(action_type_to_name, action_type_from_name, ActionType, ActionTypeNameMap)
DEFINE_ENUM_TO_STR(action_type_to_desc, ActionType, ActionTypeDescMap)
#endif // LFW_CORE_DEFINES_ACTIONTYPE_HPP
