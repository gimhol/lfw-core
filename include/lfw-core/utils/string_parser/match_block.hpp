#ifndef LFW_CORE_UTILS_STRING_PARSER_MATCH_BLOCK_HPP
#define LFW_CORE_UTILS_STRING_PARSER_MATCH_BLOCK_HPP

#include <functional>
#include <optional>
#include <regex>
#include <string>
#include <vector>

#include "detail.hpp"

namespace string_parser
{

  /// 提取起始/结束标记之间的内容，返回所有匹配
  inline std::vector<std::string> match_block(const std::string &text,
                                              const std::string &start,
                                              const std::string &end)
  {
    std::string s = detail::regex_escape(start);
    std::string e = detail::regex_escape(end);
    detail::trim(s);
    detail::trim(e);
    std::regex re(s + "([\\s\\S]*?)" + e);

    std::vector<std::string> results;
    auto begin = std::sregex_iterator(text.begin(), text.end(), re);
    auto end_it = std::sregex_iterator();
    for (auto it = begin; it != end_it; ++it)
      results.push_back((*it)[1].str());
    return results;
  }

  /// 对每个匹配调用回调
  inline void match_block(const std::string &text,
                          const std::string &start,
                          const std::string &end,
                          const std::function<void(const std::string &)> &func)
  {
    for (const auto &b : match_block(text, start, end))
      func(b);
  }

  /// 只匹配第一个块
  inline std::optional<std::string> match_block_once(const std::string &text,
                                                     const std::string &start,
                                                     const std::string &end)
  {
    std::string s = detail::regex_escape(start);
    std::string e = detail::regex_escape(end);
    detail::trim(s);
    detail::trim(e);
    std::regex re(s + "([\\s\\S]*?)" + e);
    std::smatch m;
    if (std::regex_search(text, m, re) && m.size() > 1)
      return m[1].str();
    return std::nullopt;
  }

} // namespace string_parser

#endif
