#ifndef LFW_CORE_DEFINES_ISCHEMA_HPP
#define LFW_CORE_DEFINES_ISCHEMA_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "lfw-core/core.hpp"

LFW_NS_BEGIN

// ============================================================
// IClazz — 类型构造函数标签，对应 TS IClazz<C, A>
// ============================================================
template <typename C = void, typename... Args>
struct IClazz
{
  using type = C;
};

// ============================================================
// SchemaPropertyType — 对应 TS ISchemaPropertyTypes
// ============================================================
/// 字符串约束
struct SchemaStringMeta
{
  std::optional<bool> not_empty;
  std::optional<bool> not_blank;
};

/// 数值约束
struct SchemaNumberMeta
{
  std::optional<bool> integer;
  std::optional<bool> negative;
  std::optional<bool> positive;
  std::optional<bool> nan;
};

/// 基础类型标签
enum class SchemaPrimitive : uint8_t
{
  Array,
  Boolean,
  Null,
  Number,
  Integer,
  Object,
  String,
};

/// 属性类型：基础类型 | 类型索引（对应 TS IClazz / 构造函数）
using SchemaPropertyType = std::variant<
    SchemaPrimitive,
    std::string // 自定义类型名（替代 IClazz/构造函数）
    >;

// ============================================================
// ISchemaMeta — 对应 TS ISchemaMeta<T>
// ============================================================
struct ISchemaMeta
{
  std::optional<std::string> key;
  std::optional<std::string> description;
  std::optional<SchemaPropertyType> type;
  std::optional<std::string> path;

  /// 字符串约束
  std::optional<SchemaStringMeta> string_meta;

  /// 数值约束
  std::optional<SchemaNumberMeta> number_meta;

  /// 是否可为空
  std::optional<bool> nullable;

  /// 跳过校验
  std::optional<bool> dont_validate;

  /// 枚举值（oneof）
  using OneofValue = std::variant<std::string, double, bool>;
  std::optional<std::vector<OneofValue>> oneof;
};

/// IPropsMeta — 对应 TS IPropsMeta<T>: Record<keyof T, ISchemaMeta | ISchemaPropertyType>
using IPropsMeta = std::unordered_map<std::string, std::variant<ISchemaMeta, SchemaPropertyType>>;

// ============================================================
// ISchema — 对应 TS ISchema<T>
// ============================================================

/// 前向声明
struct ISchema;

// items 可以是 ISchema 或 SchemaPropertyType
using SchemaItems = std::variant<ISchema, SchemaPropertyType>;

struct ISchema : ISchemaMeta
{
  SchemaPropertyType type;

  /// 子属性 schema（对应 TS properties: Record<keyof T, ISchema>）
  std::optional<std::unordered_map<std::string, ISchema>> properties;

  /// items schema（对应 TS items?: ISchema | ISchemaPropertyTypes）
  std::optional<SchemaItems> items;
};

LFW_NS_END

#endif
