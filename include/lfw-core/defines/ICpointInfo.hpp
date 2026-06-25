#ifndef LFW_CORE_DEFINES_ICPOINT_INFO_HPP
#define LFW_CORE_DEFINES_ICPOINT_INFO_HPP

#include <optional>
#include <string>

#include "INextFrame.hpp"
#include "IPairByFace.hpp"
#include "IRect.hpp"
#include "lfw-core/base/Fields.hpp"

/// IQubePair — Qube 对（按朝向区分）
using IQubePair = IPairByFace<IQube>;

/// ICpointInfo — 抓取点信息
struct ICpointInfo
{
  int kind = 1;
  std::optional<double> x;
  std::optional<double> y;
  std::optional<double> z;
  /// 被抓者动作
  std::optional<TNextFrame> vaction;
  std::optional<int> injury;
  std::optional<int> hurtable;
  std::optional<double> decrease;
  std::optional<double> throwvx;
  std::optional<double> throwvy;
  std::optional<double> throwvz;
  /// 被丢者落地受伤量，-1=抓人者变被抓者
  std::optional<double> throwinjury;
  std::optional<std::string> fronthurtact;
  std::optional<std::string> backhurtact;
  std::optional<double> shaking;
  /// 方向指示器
  std::optional<IQubePair> indicator_info;
};

inline const auto &cpoint_info_fields()
{
  static const auto fs = fields<ICpointInfo>(
      field("kind", FieldKind::Int, &ICpointInfo::kind, "类型"),
      field("x", FieldKind::Float, &ICpointInfo::x, "X"),
      field("y", FieldKind::Float, &ICpointInfo::y, "Y"),
      field("z", FieldKind::Float, &ICpointInfo::z, "Z"),
      field("vaction", FieldKind::Object, [](const ICpointInfo &c) -> std::any
            { return c.vaction; }, [](ICpointInfo &c, const std::any &val)
            { c.vaction = std::any_cast<std::optional<TNextFrame>>(val); }, "被抓动作"),
      field("injury", FieldKind::Int, &ICpointInfo::injury, "伤害"), field("hurtable", FieldKind::Int, &ICpointInfo::hurtable, "可受伤"), field("decrease", FieldKind::Float, &ICpointInfo::decrease, "衰减"), field("throwvx", FieldKind::Float, &ICpointInfo::throwvx, "投掷VX"), field("throwvy", FieldKind::Float, &ICpointInfo::throwvy, "投掷VY"), field("throwvz", FieldKind::Float, &ICpointInfo::throwvz, "投掷VZ"), field("throwinjury", FieldKind::Float, &ICpointInfo::throwinjury, "投掷伤害"), field("fronthurtact", FieldKind::String, &ICpointInfo::fronthurtact, "前受伤动作"), field("backhurtact", FieldKind::String, &ICpointInfo::backhurtact, "后受伤动作"), field("shaking", FieldKind::Float, &ICpointInfo::shaking, "震动"), field("indicator_info", FieldKind::Object, [](const ICpointInfo &c) -> std::any
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            { return c.indicator_info; }, [](ICpointInfo &c, const std::any &val)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            { c.indicator_info = std::any_cast<std::optional<IQubePair>>(val); }, "指示器"));
  return fs;
}

#endif
