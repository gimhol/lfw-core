#ifndef LFW_CORE_LFW_HPP
#define LFW_CORE_LFW_HPP

#include <memory>

#include "lfw-core/World.h"
#include "lfw-core/utils/math/MT.hpp"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

struct LFWPrivate;

class LFW
{
public:
  LFW();
  ~LFW();

  MersenneTwister &mt();
  World &world();

private:
  std::unique_ptr<LFWPrivate> _;
};

LFW_NS_END

#endif
