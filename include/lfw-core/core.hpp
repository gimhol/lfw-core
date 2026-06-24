#ifndef LFW_CORE_CORE_HPP
#define LFW_CORE_CORE_HPP

#include <string_view>

/// 命名空间宏（所有 lfw-core 头文件统一使用）
#define LFW_NS lfw
#define LFW_NS_BEGIN \
  namespace LFW_NS   \
  {
#define LFW_NS_END }

LFW_NS_BEGIN

/// @brief Returns the version string of the lfw-core library.
[[nodiscard]] auto version() noexcept -> std::string_view;

/// @brief Returns the project description.
[[nodiscard]] auto description() noexcept -> std::string_view;

LFW_NS_END

#endif // LFW_CORE_CORE_HPP
