#ifndef LFW_CORE_DEFINES_ISTAGE_OBJECT_INFO_HPP
#define LFW_CORE_DEFINES_ISTAGE_OBJECT_INFO_HPP

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#include <optional>
#include <string>
#include <vector>

/// IStageObjectInfo — 关卡物件信息
struct IStageObjectInfo
{
  std::optional<std::string> id_method;
  std::vector<std::string> id;
  double x = 0;
  std::optional<double> y, z;
  std::optional<std::string> act;
  std::optional<int> facing;
  std::optional<double> hp, mp;
};


LFW_NS_END

#endif
