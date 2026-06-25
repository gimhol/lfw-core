#include "lfw-core/entity/LFW.hpp"
#include <chrono>

LFW_NS_BEGIN

/// LFW 私有成员，仅在 LFW.cpp 中定义（Pimpl 模式）
struct LFWPrivate
{
  /// 梅森旋转随机数生成器 — 对应 TS lfw._mt
  MersenneTwister _mt;

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

LFW_NS_END
