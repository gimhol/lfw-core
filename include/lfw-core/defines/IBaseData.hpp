#ifndef LFW_CORE_DEFINES_IBASE_DATA_HPP
#define LFW_CORE_DEFINES_IBASE_DATA_HPP

#include <optional>
#include <string>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN
/// IBaseData — 数据基类，子类通过继承扩展 base 字段
/// 对应 TS 的 IBaseData<I>
struct IBaseData
{
  std::string id;
  /// @see IDataMap — 数据类型标识
  std::string type;
  std::optional<std::string> alias_id;
};
LFW_NS_END
#endif
