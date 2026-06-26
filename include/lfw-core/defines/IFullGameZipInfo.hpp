#ifndef LFW_CORE_DEFINES_IFULL_GAME_ZIP_INFO_HPP
#define LFW_CORE_DEFINES_IFULL_GAME_ZIP_INFO_HPP

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

#include <string>
#include <vector>

/// IBaseZipInfo — ZIP 基础信息
struct IBaseZipInfo
{
  std::string title;
  double version = 0;
  std::string description;
  std::string author;
};

/// IGameZipInfo — 完整版 ZIP
struct IGameZipInfo : IBaseZipInfo
{
  std::string type = "FULL";
  std::vector<std::string> paths;
};

/// IPrelZipInfo — 前奏版 ZIP
struct IPrelZipInfo : IBaseZipInfo
{
  std::string type = "PREL";
};

/// IDataZipInfo — 数据版 ZIP
struct IDataZipInfo : IBaseZipInfo
{
  std::string type = "DATA";
};


LFW_NS_END

#endif
