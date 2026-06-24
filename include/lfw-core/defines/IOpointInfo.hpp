#ifndef LFW_CORE_DEFINES_IOPOINT_INFO_HPP
#define LFW_CORE_DEFINES_IOPOINT_INFO_HPP

#include <optional>
#include <string>

#include "IRect.hpp"

/// IOpointInfo — 生成物信息
struct IOpointInfo : IQube
{
  std::optional<std::string> id, name;
  std::optional<int> kind; // OpointKind | number
  std::optional<std::string> oid;
  std::optional<int> facing;
  std::optional<int> action;
  std::optional<double> dvx, dvy, dvz;
  std::optional<int> team;
  std::optional<int> hp;
  std::optional<int> mp;
  std::optional<int> spreading; // OpointSpreading
  std::optional<int> multi;     // OpointMulti
  std::optional<int> count;
  std::optional<std::string> test;
};

#endif
