#ifndef LFW_CORE_UTILS_STRING_PARSER_MATCH_ALL_HPP
#define LFW_CORE_UTILS_STRING_PARSER_MATCH_ALL_HPP

#include <functional>
#include <regex>
#include <string>
#include <vector>

namespace string_parser
{

  /// 返回所有正则匹配的完整字符串
  inline std::vector<std::string> match_all(const std::string &text, const std::regex &re)
  {
    std::vector<std::string> results;
    auto begin = std::sregex_iterator(text.begin(), text.end(), re);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it)
      results.push_back(it->str());
    return results;
  }

  /// 对每个匹配调用回调
  inline void match_all(const std::string &text, const std::regex &re,
                        const std::function<void(const std::smatch &)> &func)
  {
    auto begin = std::sregex_iterator(text.begin(), text.end(), re);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it)
      func(*it);
  }

} // namespace string_parser

#endif
