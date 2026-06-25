#include "lfw-core/LFW.hpp"
#include <chrono>

LFW_NS_BEGIN

/// LFW 私有成员，仅在 LFW.cpp 中定义（Pimpl 模式）
struct LFWPrivate
{
  MersenneTwister _mt;
  World _world; // 最小化实现，为 Buff 等系统提供依赖

  LFWPrivate()
      : _mt(static_cast<uint32_t>(
            std::chrono::system_clock::now().time_since_epoch().count()))
  {
  }
};

LFW::LFW()
    : _(std::make_unique<LFWPrivate>())
{
}

LFW::~LFW() = default;

MersenneTwister &LFW::mt()
{
  return _->_mt;
}

World &LFW::world()
{
  return _->_world;
}

LFW_NS_END
