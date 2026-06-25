#ifndef LFW_CORE_DEFINES_ISTYLE_HPP
#define LFW_CORE_DEFINES_ISTYLE_HPP

#include <optional>
#include <string>

/// IStyle — Canvas 渲染样式
struct IStyle
{
  std::optional<double> padding_t;
  std::optional<double> padding_b;
  std::optional<double> padding_l;
  std::optional<double> padding_r;
  std::optional<std::string> line_cap;
  std::optional<double> line_dash_offset;
  std::optional<std::string> line_join;
  std::optional<double> line_width;
  std::optional<double> miter_limit;
  std::optional<double> shadow_blur;
  std::optional<std::string> shadow_color;
  std::optional<double> shadow_offset_x;
  std::optional<double> shadow_offset_y;
  std::optional<std::string> fill_style;
  std::optional<std::string> stroke_style;
  std::optional<std::string> direction;
  std::optional<std::string> font;
  std::optional<std::string> font_kerning;
  std::optional<std::string> font_stretch;
  std::optional<std::string> font_variant_caps;
  std::optional<std::string> letter_spacing;
  std::optional<std::string> text_align;
  std::optional<std::string> text_baseline;
  std::optional<std::string> text_rendering;
  std::optional<std::string> word_spacing;
  std::optional<bool> smoothing;
  std::optional<std::string> underline_color;
  std::optional<double> underline_width;
  std::optional<double> scale;
};

#endif
