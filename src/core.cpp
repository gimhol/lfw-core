#include "lfw-core/core.hpp"

namespace lfw
{

  auto version() noexcept -> std::string_view
  {
    return "0.1.0";
  }

  auto description() noexcept -> std::string_view
  {
    return "lfw-core - A C++23 core library";
  }

} // namespace lfw
