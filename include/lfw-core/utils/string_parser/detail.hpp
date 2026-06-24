#ifndef LFW_CORE_UTILS_STRING_PARSER_DETAIL_HPP
#define LFW_CORE_UTILS_STRING_PARSER_DETAIL_HPP

#include <regex>
#include <string>

namespace string_parser
{
  namespace detail
  {

    inline void trim(std::string &s)
    {
      s.erase(0, s.find_first_not_of(" \t\n\r"));
      s.erase(s.find_last_not_of(" \t\n\r") + 1);
    }

    inline std::string regex_escape(const std::string &s)
    {
      static const std::regex special{R"([-[\]{}()*+?.,\^$|#\s])"};
      return std::regex_replace(s, special, R"(\$&)");
    }

  } // namespace detail
} // namespace string_parser

#endif
