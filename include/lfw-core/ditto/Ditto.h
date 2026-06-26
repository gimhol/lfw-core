#ifndef LFW_CORE_DITTO_DITTO_H
#define LFW_CORE_DITTO_DITTO_H

#include <cstdio>
#include <string>

#include "lfw-core/core.hpp"
#include "lfw-core/defines/IVector3.hpp"

LFW_NS_BEGIN

/// Ditto — 平台抽象工厂（最小化实现）
/// 对应 TS Ditto，当前仅提供 Entity 等核心类所需的最小接口
/// TODO: 完整转换 pending
struct Ditto
{
  /// 创建三维向量 — 对应 TS Ditto.vec3
  static IVector3 vec3(double x = 0, double y = 0, double z = 0)
  {
    return IVector3(x, y, z);
  }

  /// 调试日志 — 对应 TS Ditto.debug
  static void debug(const std::string &msg)
  {
    std::fprintf(stderr, "[DEBUG] %s\n", msg.c_str());
  }

  /// 警告日志 — 对应 TS Ditto.warn
  static void warn(const std::string &msg)
  {
    std::fprintf(stderr, "[WARN] %s\n", msg.c_str());
  }

  /// 信息日志 — 对应 TS Ditto.Log
  static void log(const std::string &msg)
  {
    std::fprintf(stderr, "[INFO] %s\n", msg.c_str());
  }
};

LFW_NS_END

#endif
