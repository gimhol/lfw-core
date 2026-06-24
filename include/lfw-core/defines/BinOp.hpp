#ifndef LFW_CORE_DEFINES_BINOP_HPP
#define LFW_CORE_DEFINES_BINOP_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "EnumHelper.hpp"

#define ENUM_ITEMS(X)                    \
  X(BinOp, LESS, "<", "", )              \
  X(BinOp, LESS_OR_EQUAL, "<=", "", )    \
  X(BinOp, EQUAL, "==", "", )            \
  X(BinOp, GREATER_OR_EQUAL, ">=", "", ) \
  X(BinOp, GREATER, ">", "", )           \
  X(BinOp, NOT_EQUAL, "!=", "", )        \
  X(BinOp, IncludedBy, "}}", "", )       \
  X(BinOp, Include, "{{", "", )          \
  X(BinOp, NotIncludedBy, "!}", "", )    \
  X(BinOp, NotInclude, "!{", "", )

enum class BinOp : uint8_t
{
  ENUM_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(BinOpStringMap, ENUM_ITEMS, BinOp)
GEN_ENUM_NAME_MAP(BinOpNameMap, ENUM_ITEMS, BinOp)
GEN_ENUM_DESC_MAP(BinOpDescMap, ENUM_ITEMS, BinOp)
#undef ENUM_ITEMS
DEFINE_ENUM_STR_CONVERTERS(bin_op_to_string, bin_op_from_string, BinOp, BinOpStringMap)
DEFINE_ENUM_STR_CONVERTERS(bin_op_to_name, bin_op_from_name, BinOp, BinOpNameMap)
DEFINE_ENUM_TO_STR(bin_op_to_desc, BinOp, BinOpDescMap)
#endif // LFW_CORE_DEFINES_BINOP_HPP
