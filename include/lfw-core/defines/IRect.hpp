#ifndef LFW_CORE_DEFINES_IRECT_HPP
#define LFW_CORE_DEFINES_IRECT_HPP

/// IRect — 矩形区域
struct IRect
{
  double x = 0;
  double y = 0;
  double w = 0;
  double h = 0;
};

/// IQube — 立方体区域（继承矩形 + z/l）
struct IQube : IRect
{
  double z = 0;
  double l = 0;
};

#endif
