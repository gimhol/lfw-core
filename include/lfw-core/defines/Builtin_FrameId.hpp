#ifndef LFW_CORE_DEFINES_BUILTIN_FRAME_ID_HPP
#define LFW_CORE_DEFINES_BUILTIN_FRAME_ID_HPP

#include <cstdint>
#include <optional>
#include <string_view>

/// Builtin_FrameId — 内置帧 ID（字符串枚举）
enum class Builtin_FrameId : uint8_t
{
  None,
  Auto,
  Self,
  Gone,
  Invisible_Min, // 1100 ~ 1299 隐身
  Invisible_Max,
  Respawn
};

inline std::string_view builtin_frame_id_to_string(Builtin_FrameId v)
{
  switch (v)
  {
  case Builtin_FrameId::None:
    return "";
  case Builtin_FrameId::Auto:
    return "auto";
  case Builtin_FrameId::Self:
    return "self";
  case Builtin_FrameId::Gone:
    return "gone";
  case Builtin_FrameId::Invisible_Min:
    return "1100";
  case Builtin_FrameId::Invisible_Max:
    return "1299";
  case Builtin_FrameId::Respawn:
    return "respawn";
  }
  return "";
}

inline std::optional<Builtin_FrameId> builtin_frame_id_from_string(std::string_view s)
{
  if (s == "")
    return Builtin_FrameId::None;
  if (s == "auto")
    return Builtin_FrameId::Auto;
  if (s == "self")
    return Builtin_FrameId::Self;
  if (s == "gone")
    return Builtin_FrameId::Gone;
  if (s == "1100")
    return Builtin_FrameId::Invisible_Min;
  if (s == "1299")
    return Builtin_FrameId::Invisible_Max;
  if (s == "respawn")
    return Builtin_FrameId::Respawn;
  return std::nullopt;
}

/// 别名
using BFID = Builtin_FrameId;

#endif
