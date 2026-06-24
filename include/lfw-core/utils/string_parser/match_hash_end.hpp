#ifndef LFW_CORE_UTILS_STRING_PARSER_MATCH_HASH_END_HPP
#define LFW_CORE_UTILS_STRING_PARSER_MATCH_HASH_END_HPP

#include <optional>
#include <regex>
#include <string>

namespace string_parser
{

  /// 提取 # 后的内容（不含尾部换行）
  inline std::optional<std::string> match_hash_end(const std::string &text)
  {
    std::regex re(R"(#(.*)[\n\r]*)");
    std::smatch m;
    if (std::regex_search(text, m, re) && m.size() > 1)
      return m[1].str();
    return std::nullopt;
  }

} // namespace string_parser

#endif
