#ifndef LFW_CORE_BASE_GET_SHORT_FILE_SIZE_TXT_H
#define LFW_CORE_BASE_GET_SHORT_FILE_SIZE_TXT_H

#include <cmath>
#include <string>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

/**
 * 将字节数格式化为可读的短文本 — 对应 TS get_short_file_size_txt
 *
 * @param bytes 字节数
 * @return      如 "1.5KB"、"23MB"、"1GB"
 */
inline std::string get_short_file_size_txt(double bytes)
{
  if (bytes < 1024)
    return std::to_string(static_cast<int>(bytes)) + "B";

  bytes /= 1024;
  if (bytes < 1024)
  {
    double v = std::round(bytes * 10) / 10;
    std::string s = std::to_string(v);
    // 去掉 ".0"
    auto dot = s.find('.');
    if (dot != std::string::npos && s.substr(dot) == ".0")
      s = s.substr(0, dot);
    return s + "KB";
  }

  bytes /= 1024;
  if (bytes < 1024)
  {
    double v = std::round(bytes * 10) / 10;
    std::string s = std::to_string(v);
    auto dot = s.find('.');
    if (dot != std::string::npos && s.substr(dot) == ".0")
      s = s.substr(0, dot);
    return s + "MB";
  }

  bytes /= 1024;
  double v = std::round(bytes * 10) / 10;
  std::string s = std::to_string(v);
  auto dot = s.find('.');
  if (dot != std::string::npos && s.substr(dot) == ".0")
    s = s.substr(0, dot);
  return s + "GB";
}

LFW_NS_END

#endif
