#ifndef LFW_CORE_DEFINES_IMODEL_INFO_HPP
#define LFW_CORE_DEFINES_IMODEL_INFO_HPP

#include <optional>
#include <string>
#include <vector>

/// IModelInfo — 3D模型信息
struct IModelInfo
{
  std::string id;
  std::string path;
  std::optional<std::vector<std::string>> variants;
  std::optional<double> scale_x, scale_y, scale_z;
};

#endif
