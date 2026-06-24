#ifndef LFW_CORE_UTILS_STRING_PARSER_MATCH_COLON_VALUE_HPP
#define LFW_CORE_UTILS_STRING_PARSER_MATCH_COLON_VALUE_HPP

#include <functional>
#include <regex>
#include <string>
#include <utility>
#include <vector>

namespace string_parser
{

  /// 解析 key: value 对，返回 vector<pair>
  inline std::vector<std::pair<std::string, std::string>> match_colon_value(const std::string &text)
  {
    std::regex re(R"(\s*(\S*)\s*:\s*(\S*))");
    std::vector<std::pair<std::string, std::string>> results;
    auto begin = std::sregex_iterator(text.begin(), text.end(), re);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it)
      results.push_back(std::make_pair((*it)[1].str(), (*it)[2].str()));
    return results;
  }

  /// 对每对调用回调
  inline void match_colon_value(const std::string &text,
                                const std::function<void(const std::string &, const std::string &)> &func)
  {
    for (const auto &[k, v] : match_colon_value(text))
      func(k, v);
  }

} // namespace string_parser

#endif
