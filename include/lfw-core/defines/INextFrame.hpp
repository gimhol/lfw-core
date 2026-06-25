#ifndef LFW_CORE_DEFINES_INEXT_FRAME_HPP
#define LFW_CORE_DEFINES_INEXT_FRAME_HPP

#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "IFrameInfo.hpp"
#include "IVelocityInfo.hpp"
#include "lfw-core/base/Fields.h"

/// StrOrNum — 字符串或数字
using StrOrNum = std::variant<std::string, double>;

// 前向声明（TNextFrame 在 struct 定义之前需要）
struct INextFrame;

/// TNextFrame — 帧过渡数组
/// @note TS: `INextFrame | INextFrame[]`，C++ 简化为 `vector<INextFrame>`（单元素 = 1 项数组）
using TNextFrame = std::vector<INextFrame>;

/// INextFrame — 下一帧过渡信息（继承 IVelocityInfo）
/// @note 与 TS 差异：
///   - id:    TS `string | string[]` → C++ `vector<string>`（简化为纯数组）
///   - judger: TS `IExpression<any>` → C++ `void*`（避免模板耦合）
///   - facing: TS `number | FacingFlag` → C++ `int`（FacingFlag 是 int 枚举）
struct INextFrame : IVelocityInfo
{
  /// 目标帧 ID（TS: `string | string[]`，C++ 简化为数组）
  std::optional<std::vector<std::string>> id;

  std::optional<std::string> desc;

  /// 持续时间策略："i"=保持, "d"=差值, 正数=固定值
  std::optional<StrOrNum> wait;

  /// 转向标志
  std::optional<int> facing;

  /// 判定表达式（字符串）
  std::optional<std::string> expression;

  /// 运行时生成的判定器
  void *judger = nullptr;

  /// 消耗 MP（正=消耗, 负=补充）
  std::optional<double> mp;

  /// MP 不足模式：1=允许进入&归零
  std::optional<int> mp_mode;

  /// 消耗 HP
  std::optional<double> hp;

  /// 进入时播放音效
  std::optional<std::vector<std::string>> sounds;

  /// 闪烁时长
  std::optional<double> blink_time;
};

/// INextFrameResult — 下一帧判定结果
struct INextFrameResult
{
  std::optional<IFrameInfo> frame;
  INextFrame which;
};

inline const auto &next_frame_fields()
{
  static const auto fs = fields<INextFrame>(
      field("id", FieldKind::Strs, &INextFrame::id, "目标帧ID"),
      field("desc", FieldKind::Str, &INextFrame::desc, "描述"),
      field("wait", FieldKind::Var, [](const INextFrame &f) -> std::any
            { return f.wait; }, [](INextFrame &f, const std::any &val)
            { f.wait = std::any_cast<std::optional<StrOrNum>>(val); }, "持续策略"),
      field("facing", FieldKind::Int, &INextFrame::facing, "转向"), field("expression", FieldKind::Str, &INextFrame::expression, "判定式"), field("mp", FieldKind::Flt, &INextFrame::mp, "消耗MP"), field("mp_mode", FieldKind::Int, &INextFrame::mp_mode, "MP不足模式"), field("hp", FieldKind::Flt, &INextFrame::hp, "消耗HP"), field("sounds", FieldKind::Strs, &INextFrame::sounds, "音效"), field("blink_time", FieldKind::Flt, &INextFrame::blink_time, "闪烁时长"));
  return fs;
}

#endif
