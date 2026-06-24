#ifndef LFW_CORE_DEFINES_ENUMHELPER_HPP
#define LFW_CORE_DEFINES_ENUMHELPER_HPP

#include <cctype>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#define DEFINE_ENUM_TO_STR(TO_STR, ENUM, MAP) \
  inline std::string_view TO_STR(ENUM v)      \
  {                                           \
    auto it = MAP.find(v);                    \
    if (it != MAP.end())                      \
      return it->second;                      \
    return "";                                \
  }

/** 通过 X-macro 条目列表生成一个 unordered_map
 *  ENTRIES:  X-macro 条目列表宏（如 BOTVAL_ENTRIES）
 *  MAP_NAME: 生成的 map 变量名
 *  ENUM_TYPE: 枚举类型
 *  MAPPER:    条目 → {key, value} 的映射宏（内部使用）
 */
#define GEN_ENUM_MAP(ENTRIES, MAP_NAME, ENUM_TYPE, MAPPER) \
  inline auto MAP_NAME = std::unordered_map<ENUM_TYPE, std::string>{ENTRIES(MAPPER)};

/* ---- 内部映射器（GEN_ENUM_*_MAP 专用，第5参数 val 忽略）---- */
#define _MAP_STR(ENUM, e, str, desc, val) {ENUM::e, str},
#define _MAP_NAME(ENUM, e, str, desc, val) {ENUM::e, #e},
#define _MAP_DESC(ENUM, e, str, desc, val) {ENUM::e, desc},

/** 生成 StringMap: 枚举 → 字符串值 */
#define GEN_ENUM_STR_MAP(MAP_NAME, ENTRIES, ENUM_TYPE) \
  GEN_ENUM_MAP(ENTRIES, MAP_NAME, ENUM_TYPE, _MAP_STR)

/** 生成 NameMap: 枚举 → 枚举名（如 "Desire"） */
#define GEN_ENUM_NAME_MAP(MAP_NAME, ENTRIES, ENUM_TYPE) \
  GEN_ENUM_MAP(ENTRIES, MAP_NAME, ENUM_TYPE, _MAP_NAME)

/** 生成 DescMap: 枚举 → 描述文本 */
#define GEN_ENUM_DESC_MAP(MAP_NAME, ENTRIES, ENUM_TYPE) \
  GEN_ENUM_MAP(ENTRIES, MAP_NAME, ENUM_TYPE, _MAP_DESC)

/** 生成枚举 ↔ 字符串的双向转换函数（大小写不敏感） */
#define DEFINE_ENUM_STR_CONVERTERS(TO_STR, FROM_STR, ENUM, MAP)            \
  inline std::string_view TO_STR(ENUM v)                                   \
  {                                                                        \
    auto it = MAP.find(v);                                                 \
    if (it != MAP.end())                                                   \
      return it->second;                                                   \
    return "";                                                             \
  }                                                                        \
  inline std::optional<ENUM> FROM_STR(std::string_view s)                  \
  {                                                                        \
    static const auto rmap = []                                            \
    {                                                                      \
      std::unordered_map<std::string, ENUM> r;                             \
      for (const auto &[k, v] : MAP)                                       \
      {                                                                    \
        std::string lower = v;                                             \
        for (auto &c : lower)                                              \
          c = static_cast<char>(::tolower(static_cast<unsigned char>(c))); \
        r[lower] = k;                                                      \
      }                                                                    \
      return r;                                                            \
    }();                                                                   \
    std::string lower{s};                                                  \
    for (auto &c : lower)                                                  \
      c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));     \
    auto it = rmap.find(lower);                                            \
    if (it != rmap.end())                                                  \
      return it->second;                                                   \
    return std::nullopt;                                                   \
  }

/** 生成枚举 ↔ 字符串的双向转换函数（大小写敏感）
 *  用于 "D"/"d" 这样大小写区分不同枚举值的场景
 */
#define DEFINE_ENUM_STR_CONVERTERS_EXACT(TO_STR, FROM_STR, ENUM, MAP) \
  inline std::string_view TO_STR(ENUM v)                              \
  {                                                                   \
    auto it = MAP.find(v);                                            \
    if (it != MAP.end())                                              \
      return it->second;                                              \
    return "";                                                        \
  }                                                                   \
  inline std::optional<ENUM> FROM_STR(std::string_view s)             \
  {                                                                   \
    static const auto rmap = []                                       \
    {                                                                 \
      std::unordered_map<std::string, ENUM> r;                        \
      for (const auto &[k, v] : MAP)                                  \
        r[v] = k;                                                     \
      return r;                                                       \
    }();                                                              \
    auto it = rmap.find(std::string{s});                              \
    if (it != rmap.end())                                             \
      return it->second;                                              \
    return std::nullopt;                                              \
  }

#endif // LFW_CORE_DEFINES_ENUMHELPER_HPP
