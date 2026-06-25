#ifndef LFW_CORE_UTILS_STRING_PARSER_TAKE_SECTIONS_HPP
#define LFW_CORE_UTILS_STRING_PARSER_TAKE_SECTIONS_HPP

#include <any>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "match_colon_value.hpp"
#include "take_blocks.hpp"
#include "lfw-core/base/Fields.h"

namespace string_parser
{

  template <typename T = std::unordered_map<std::string, std::string>>
  struct TakeSectionsResult
  {
    std::vector<T> sections;
    std::string remains;
  };

  /// 提取块并解析为 map（默认）或任意 numeric map 类型
  template <typename T = std::unordered_map<std::string, std::string>>
  TakeSectionsResult<T> take_sections(const std::string &text,
                                      const std::string &start,
                                      const std::string &end)
  {
    auto [blocks, remains] = take_blocks(text, start, end);
    TakeSectionsResult<T> result;
    result.remains = std::move(remains);
    for (auto &content : blocks)
    {
      T item;
      for (auto &[k, v] : match_colon_value(content))
      {
        if constexpr (std::is_arithmetic_v<typename T::mapped_type>)
        {
          try
          {
            if constexpr (std::is_same_v<typename T::mapped_type, double>)
              item[k] = std::stod(v);
            else if constexpr (std::is_same_v<typename T::mapped_type, int>)
              item[k] = std::stoi(v);
            else
              item[k] = static_cast<typename T::mapped_type>(std::stod(v));
          }
          catch (...)
          {
            item[k] = typename T::mapped_type{};
          }
        }
        else
        {
          item[k] = v;
        }
      }
      result.sections.push_back(std::move(item));
    }
    return result;
  }

  /// 提取块并通过 Fields<T> 反射解析为自定义结构体
  template <typename T>
  TakeSectionsResult<T> take_sections(const std::string &text,
                                      const std::string &start,
                                      const std::string &end,
                                      const Fields<T> &fs)
  {
    auto [blocks, remains] = take_blocks(text, start, end);
    TakeSectionsResult<T> result;
    result.remains = std::move(remains);
    for (auto &content : blocks)
    {
      T item{};
      for (auto &[k, v] : match_colon_value(content))
      {
        // 按字段类型转换字符串值
        auto *e = fs.find(k);
        if (!e)
          continue;

        switch (e->info.kind)
        {
        case FieldKind::Int:
          try
          {
            e->set(item, std::any(std::stoi(v)));
          }
          catch (...)
          {
          }
          break;
        case FieldKind::Flt:
          try
          {
            e->set(item, std::any(std::stod(v)));
          }
          catch (...)
          {
          }
          break;
        case FieldKind::Str:
          e->set(item, std::any(v));
          break;
        case FieldKind::Bool:
          e->set(item, std::any(v == "true" || v == "1"));
          break;
        }
      }
      result.sections.push_back(std::move(item));
    }
    return result;
  }

} // namespace string_parser

#endif
