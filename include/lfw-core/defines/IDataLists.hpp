#ifndef LFW_CORE_DEFINES_IDATA_LISTS_HPP
#define LFW_CORE_DEFINES_IDATA_LISTS_HPP

#include <vector>

#include "IDatIndex.hpp"

/// IDataLists — 数据列表（已处理的数据索引）
struct IDataLists
{
  std::vector<IDatIndex> objects;
  std::vector<IDatIndex> backgrounds;
  std::vector<IDatIndex> stages;
  std::vector<IDatIndex> bots;
};

/// ITempDataLists — 临时数据列表（含源文件路径的索引）
struct ITempDataLists
{
  std::vector<ITempDatIndex> objects;
  std::vector<ITempDatIndex> backgrounds;
  std::vector<ITempDatIndex> stages;
  std::vector<ITempDatIndex> bots;
};

#endif
