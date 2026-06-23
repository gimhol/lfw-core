#ifndef LFW_CORE_CORE_HPP
#define LFW_CORE_CORE_HPP

#include <string_view>

namespace lfw
{

  /// @brief Returns the version string of the lfw-core library.
  [[nodiscard]] auto version() noexcept -> std::string_view;

  /// @brief Returns the project description.
  [[nodiscard]] auto description() noexcept -> std::string_view;

} // namespace lfw

#endif // LFW_CORE_CORE_HPP
