#ifndef LFW_CORE_UTILS_STRING_PARSER_TAKE_BLOCKS_HPP
#define LFW_CORE_UTILS_STRING_PARSER_TAKE_BLOCKS_HPP

#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "detail.hpp"

namespace string_parser
{

  /// 提取块并返回剩余文本
  struct TakeBlocksResult
  {
    std::vector<std::string> blocks;
    std::string remains;
  };

  inline TakeBlocksResult take_blocks(const std::string &text,
                                      const std::string &start,
                                      const std::string &end)
  {
    std::string s = detail::regex_escape(start);
    std::string e = detail::regex_escape(end);
    // trim after escape
    s.erase(0, s.find_first_not_of(" \t\n\r"));
    s.erase(s.find_last_not_of(" \t\n\r") + 1);
    e.erase(0, e.find_first_not_of(" \t\n\r"));
    e.erase(e.find_last_not_of(" \t\n\r") + 1);

    std::regex re(s + "([\\s\\S]*?)" + e);
    std::vector<std::pair<std::size_t, std::size_t>> positions;
    TakeBlocksResult result;

    auto begin = std::sregex_iterator(text.begin(), text.end(), re);
    auto end_it = std::sregex_iterator();
    for (auto it = begin; it != end_it; ++it)
    {
      result.blocks.push_back((*it)[1].str());
      positions.emplace_back(it->position(), it->position() + it->length());
    }

    if (!positions.empty())
    {
      std::size_t pos = 0;
      for (auto [from, to] : positions)
      {
        result.remains += text.substr(pos, from - pos);
        pos = to;
      }
      result.remains += text.substr(pos);
    }
    else
    {
      result.remains = text;
    }
    return result;
  }

} // namespace string_parser

#endif
