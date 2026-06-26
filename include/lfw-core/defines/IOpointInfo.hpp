#ifndef LFW_CORE_DEFINES_IOPOINT_INFO_HPP
#define LFW_CORE_DEFINES_IOPOINT_INFO_HPP

#include <any>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "INextFrame.hpp"
#include "IQubePair.hpp"
#include "lfw-core/base/Fields.h"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/// IOpointMulti — 生成数量策略
/// 对应 TS IOpointMulti
struct IOpointMulti
{
  int type = 0;                  ///< OpointMultiEnum | number
  std::optional<bool> skip_zero; ///< 场上无敌人时跳过
  std::optional<int> min;        ///< 最少生成数
  std::optional<int> max;        ///< 最多生成数
};

/// Oid — 实体数据 ID（TS: string | string[]，C++ 简化为数组，单元素 = 1 项数组）
using Oid = std::vector<std::string>;

/// IOpointInfo — 生成物信息
/// 对应 TS IOpointInfo（不继承 IQube）
struct IOpointInfo
{
  std::optional<std::string> id;
  std::optional<std::string> name;

  int kind = 0; ///< OpointKind | number（TS 必填）
  double x = 0; ///< 生成 X（相对帧矩形左上角，TS 必填）
  double y = 0; ///< 生成 Y（相对帧矩形左上角，TS 必填）
  std::optional<int> origin_type;
  std::optional<double> z;

  Oid oid;           ///< 实体数据 ID（TS 必填: string | string[]）
  TNextFrame action; ///< 生成物初始帧（TS 必填）

  std::optional<double> dvx; ///< 发射初速度 X
  std::optional<double> dvy; ///< 发射初速度 Y
  std::optional<double> dvz; ///< 发射初速度 Z

  /// 生成数量（number | IOpointMulti）
  std::variant<int, IOpointMulti> multi = 1;

  std::optional<double> max_hp; ///< 覆盖最大血量
  std::optional<double> hp;     ///< 覆盖血量
  std::optional<double> max_mp; ///< 覆盖最大蓝量
  std::optional<double> mp;     ///< 覆盖蓝量

  std::optional<double> speedz; ///< 按上下键额外 Z 初速度
  std::optional<int> spreading; ///< OpointSpreading | number

  std::optional<bool> is_entity; ///< 是否直接生成实体

  std::optional<int> interval; ///< 生成间隔
  std::optional<std::string> interval_id;
  std::optional<int> interval_mode; ///< 1 | 0

  std::optional<IQubePair> indicator_info; ///< 调试可视化
  std::optional<int> motionless;           ///< 生成后停顿帧数
  std::optional<int> unimportant;          ///< 非重要标记
  std::optional<int> delay;                ///< 延迟帧数

  std::optional<std::vector<double>> spreading_x; ///< 扩散 X 坐标表
  std::optional<std::vector<double>> spreading_y; ///< 扩散 Y 坐标表
  std::optional<std::vector<double>> spreading_z; ///< 扩散 Z 坐标表

  std::optional<double> inherit_speed_x; ///< 从发射者继承速度 X
  std::optional<double> inherit_speed_y; ///< 从发射者继承速度 Y
  std::optional<double> inherit_speed_z; ///< 从发射者继承速度 Z
};

/// IOpointInfo 反射 — 对应 TS opoint_info_fields
inline const auto &opoint_info_fields()
{
  static const auto fs = fields<IOpointInfo>(
      field("id", FieldKind::Str, &IOpointInfo::id, "ID"),
      field("name", FieldKind::Str, &IOpointInfo::name, "名称"),
      field("kind", FieldKind::Int, &IOpointInfo::kind, "类型"),
      field("x", FieldKind::Int, &IOpointInfo::x, "X"),
      field("y", FieldKind::Int, &IOpointInfo::y, "Y"),
      field("origin_type", FieldKind::Var, [](const IOpointInfo &f) -> std::any
            { return f.origin_type; }, [](IOpointInfo &f, const std::any &val)
            { if (val.has_value()) f.origin_type = std::any_cast<std::optional<int>>(val); }, ""),
      field("z", FieldKind::Int, &IOpointInfo::z, "Z"), field("oid", FieldKind::Str, [](const IOpointInfo &f) -> std::any
                                                              { return f.oid; }, [](IOpointInfo &f, const std::any &val)
                                                              { f.oid = std::any_cast<Oid>(val); }, "实体数据ID"),
      field("action", FieldKind::Var, [](const IOpointInfo &f) -> std::any
            { return f.action; }, [](IOpointInfo &f, const std::any &val)
            { f.action = std::any_cast<TNextFrame>(val); }, ""),
      field("dvx", FieldKind::Flt, &IOpointInfo::dvx, "初速度X"), field("dvy", FieldKind::Flt, &IOpointInfo::dvy, "初速度Y"), field("dvz", FieldKind::Flt, &IOpointInfo::dvz, "初速度Z"), field("multi", FieldKind::Var, [](const IOpointInfo &f) -> std::any
                                                                                                                                                                                                { return f.multi; }, [](IOpointInfo &f, const std::any &val)
                                                                                                                                                                                                { f.multi = std::any_cast<std::variant<int, IOpointMulti>>(val); }, ""),
      field("max_hp", FieldKind::Flt, &IOpointInfo::max_hp, "最大血量"), field("hp", FieldKind::Flt, &IOpointInfo::hp, "血量"), field("max_mp", FieldKind::Flt, &IOpointInfo::max_mp, "最大蓝量"), field("mp", FieldKind::Flt, &IOpointInfo::mp, "蓝量"), field("speedz", FieldKind::Flt, &IOpointInfo::speedz, "额外Z速度"), field("spreading", FieldKind::Int, &IOpointInfo::spreading, "扩散模式"), field("is_entity", FieldKind::Bool, &IOpointInfo::is_entity, "直接生成实体"), field("interval", FieldKind::Int, &IOpointInfo::interval, "生成间隔"), field("interval_id", FieldKind::Str, &IOpointInfo::interval_id, "间隔ID"), field("motionless", FieldKind::Int, &IOpointInfo::motionless, "停顿帧数"), field("delay", FieldKind::Int, &IOpointInfo::delay, "延迟帧数"), field("inherit_speed_x", FieldKind::Flt, &IOpointInfo::inherit_speed_x, "继承速度X"), field("inherit_speed_y", FieldKind::Flt, &IOpointInfo::inherit_speed_y, "继承速度Y"), field("inherit_speed_z", FieldKind::Flt, &IOpointInfo::inherit_speed_z, "继承速度Z"));
  return fs;
}

LFW_NS_END

#endif
