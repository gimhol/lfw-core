#ifndef LFW_CORE_DEFINES_BINOP_HPP
#define LFW_CORE_DEFINES_BINOP_HPP

#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>

enum class BinOp : uint8_t
{
  LESS,
  LESS_OR_EQUAL,
  EQUAL,
  GREATER_OR_EQUAL,
  GREATER,
  NOT_EQUAL,
  IncludedBy,
  Include,
  NotIncludedBy,
  NotInclude,
};

inline std::string_view bin_op_to_string(BinOp v)
{
  switch (v)
  {
  case BinOp::LESS:
    return "<";
  case BinOp::LESS_OR_EQUAL:
    return "<=";
  case BinOp::EQUAL:
    return "==";
  case BinOp::GREATER_OR_EQUAL:
    return ">=";
  case BinOp::GREATER:
    return ">";
  case BinOp::NOT_EQUAL:
    return "!=";
  case BinOp::IncludedBy:
    return "}}";
  case BinOp::Include:
    return "{{";
  case BinOp::NotIncludedBy:
    return "!}";
  case BinOp::NotInclude:
    return "!{";
  }
  return "";
}

inline std::optional<BinOp> bin_op_from_string(std::string_view s)
{
  static const auto m = []
  {
    std::unordered_map<std::string_view, BinOp> r;
    for (uint8_t i = 0; i <= static_cast<uint8_t>(BinOp::NotInclude); ++i)
    {
      auto v = static_cast<BinOp>(i);
      r[bin_op_to_string(v)] = v;
    }
    return r;
  }();
  auto it = m.find(s);
  return it != m.end() ? std::optional{it->second} : std::nullopt;
}

#endif // LFW_CORE_DEFINES_BINOP_HPP
