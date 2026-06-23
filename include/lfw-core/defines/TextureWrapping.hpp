#ifndef LFW_CORE_DEFINES_TEXTUREWRAPPING_HPP
#define LFW_CORE_DEFINES_TEXTUREWRAPPING_HPP

#include <cstdint>

enum class TextureWrapping : uint8_t
{
  Repeat = 0,
  ClampToEdge = 1
};

enum class MagnFilter : uint8_t
{
  Linear = 0,
  Nearest = 1
};

enum class MinFilter : uint8_t
{
  LinearMipmapLinear = 0,
  LinearMipmapNearest = 1,
  NearestMipmapLinear = 2,
  NearestMipmapNearest = 3,
  Linear = 4,
  Nearest = 5
};

#endif // LFW_CORE_DEFINES_TEXTUREWRAPPING_HPP
