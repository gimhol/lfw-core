#ifndef LFW_CORE_FIELDS_HPP
#define LFW_CORE_FIELDS_HPP

#include <algorithm>
#include <any>
#include <cstddef>
#include <functional>
#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <vector>

// ============================================================
// FieldKind — 字段类型枚举
// ============================================================

#include "lfw-core/defines/EnumHelper.hpp"

#define FIELD_KIND_ITEMS(X)                         \
  X(FieldKind, Int, "int", "整数", = 0)             \
  X(FieldKind, Flt, "float", "浮点", = 1)           \
  X(FieldKind, Str, "string", "字符串", = 2)        \
  X(FieldKind, Bool, "bool", "布尔", = 3)           \
  X(FieldKind, Strs, "string[]", "字符串数组", = 4) \
  X(FieldKind, Flt2, "float[2]", "浮点对", = 5)     \
  X(FieldKind, Flt3, "float[3]", "浮点三元组", = 6) \
  X(FieldKind, Map, "map", "映射", = 7)             \
  X(FieldKind, Var, "variant", "变体", = 8)         \
  X(FieldKind, Obj, "object", "对象", = 9)

enum class FieldKind : uint8_t
{
  FIELD_KIND_ITEMS(ENUM_ITEM)
};
GEN_ENUM_STR_MAP(FieldKindStringMap, FIELD_KIND_ITEMS, FieldKind)
GEN_ENUM_NAME_MAP(FieldKindNameMap, FIELD_KIND_ITEMS, FieldKind)
GEN_ENUM_DESC_MAP(FieldKindDescMap, FIELD_KIND_ITEMS, FieldKind)
#undef FIELD_KIND_ITEMS
DEFINE_ENUM_TO_STR(field_kind_name, FieldKind, FieldKindStringMap)

// ============================================================
// FieldInfo — 单个字段的元数据（运行时反射信息）
// ============================================================

/// 提取 map 类型的 key_type / mapped_type（非 map 类型返回 void）
template <typename T, typename = void>
struct map_traits
{
  using key_type = void;
  using mapped_type = void;
};
template <typename T>
struct map_traits<T, std::void_t<typename T::key_type, typename T::mapped_type>>
{
  using key_type = typename T::key_type;
  using mapped_type = typename T::mapped_type;
};

struct FieldInfo
{
  std::string key; // 字段名
  FieldKind kind = FieldKind::Int;
  int order = 0;     // 显示顺序
  std::string title; // 显示名称
  std::string desc;  // 描述

  bool nullable = false;
  bool array = false;

  // Map 约束
  std::type_index value_type = typeid(void);  // map 值类型，非 map 为 void

  // Object 约束：记录复杂对象的 C++ 具体类型，供序列化层按类型分发。
  //
  // 用法：在 field() 中用成员指针声明时，add_entry 自动填充 typeid(U)。
  //       序列化层（to_json / from_json）根据此值分发：
  //
  //   if (info.object_type == typeid(std::optional<TNextFrame>))
  //       { /* 序列化为 JSON 数组 */ }
  //   else if (info.object_type == typeid(std::optional<IQubePair>))
  //       { /* 序列化为 {left, right} */ }
  //
  // 新增 Object 类型时，只需在序列化函数中加 else if 分支，无需修改 FieldInfo。
  std::type_index object_type = typeid(void);

  // 数值约束 (Int / Float)
  bool has_min = false;
  bool has_max = false;
  double min_val = 0;
  double max_val = 0;
  double step_val = 1;
  bool bit_flag = false;

  // 字符串约束 (String)
  int max_length = 0;

  // 选项列表
  struct Option
  {
    std::any value;
    std::string label;
    std::string desc;
  };
  std::vector<Option> options;
};

template <typename T, typename U>
class FieldDef;

struct CustomField;

// ============================================================
// Fields — 结构体的字段映射（反射容器）
//
// 对应 TypeScript 中 Map<keyof T, IFieldInfo<T>>
// 支持运行时按名称 get/set 字段值。
//
// 用法:
//   struct Player { int hp; float speed; std::string name; };
//
//   auto fs = fields<Player>(
//       field("hp", FieldKind::Int,    &Player::hp,    "生命值").min(0).max(9999),
//       field("speed", FieldKind::Flt, &Player::speed, "速度").min(0).max(100),
//       field("name", FieldKind::Str,&Player::name,  "名称")
//   );
//
//   // 反射访问:
//   auto hp = fs.get(player, "hp");           // std::any
//   fs.set(player, "hp", std::any(80));
// ============================================================
template <typename T>
class Fields
{
public:
  using Getter = std::function<std::any(const T &)>;
  using Setter = std::function<void(T &, const std::any &)>;

  struct Entry
  {
    FieldInfo info;
    Getter get;
    Setter set;
  };

  // ----------------------------------------------------------
  /// 根据字段名查找条目
  const Entry *find(const std::string &key) const
  {
    auto it = _by_name.find(key);
    return it != _by_name.end() ? &_entries[it->second] : nullptr;
  }

  /// 通过反射读取字段值
  std::any get(const T &obj, const std::string &key) const
  {
    auto *e = find(key);
    if (!e)
      throw std::runtime_error("Fields::get: unknown field \"" + key + "\"");
    return e->get(obj);
  }

  /// 通过反射写入字段值
  void set(T &obj, const std::string &key, const std::any &val) const
  {
    auto *e = find(key);
    if (!e)
      throw std::runtime_error("Fields::set: unknown field \"" + key + "\"");
    e->set(obj, val);
  }

  /// 遍历所有字段
  const std::vector<Entry> &entries() const { return _entries; }
  std::size_t size() const { return _entries.size(); }

  /// 按 order 排序的 key 列表
  std::vector<std::string> ordered_keys() const
  {
    std::vector<std::string> keys;
    keys.reserve(_entries.size());
    for (auto &e : _entries)
      keys.push_back(e.info.key);
    return keys;
  }

  template <typename U>
  std::size_t add_entry(FieldDef<T, U> def);

  std::size_t add_entry(const CustomField &def);

private:
  std::vector<Entry> _entries;
  std::map<std::string, std::size_t> _by_name;

  template <typename U>
  static U resolve_any(const std::any &val)
  {
    // 尝试直接转换
    try
    {
      return std::any_cast<U>(val);
    }
    catch (const std::bad_any_cast &)
    {
    }

    // float ↔ double 互转
    if constexpr (std::is_same_v<U, float>)
    {
      try
      {
        return static_cast<float>(std::any_cast<double>(val));
      }
      catch (...)
      {
      }
    }
    if constexpr (std::is_same_v<U, double>)
    {
      try
      {
        return static_cast<double>(std::any_cast<float>(val));
      }
      catch (...)
      {
      }
    }
    // int → float/double
    if constexpr (std::is_floating_point_v<U>)
    {
      try
      {
        return static_cast<U>(std::any_cast<int>(val));
      }
      catch (...)
      {
      }
    }
    // float/double → int
    if constexpr (std::is_integral_v<U> && !std::is_same_v<U, bool>)
    {
      try
      {
        return static_cast<U>(std::any_cast<double>(val));
      }
      catch (...)
      {
      }
    }

    throw std::bad_any_cast();
  }
};

// ============================================================
// FieldDef — 字段定义（构建期，链式 API）
// ============================================================
template <typename T, typename U>
class FieldDef
{
public:
  FieldDef(std::string key, FieldKind kind, U T::*member)
      : _key(std::move(key)), _kind(kind), _member(member) {}

  FieldDef &title(std::string v)
  {
    _title = std::move(v);
    return *this;
  }
  FieldDef &desc(std::string v)
  {
    _desc = std::move(v);
    return *this;
  }
  FieldDef &order(int v)
  {
    _order = v;
    return *this;
  }
  FieldDef &nullable(bool v = true)
  {
    _nullable = v;
    return *this;
  }
  FieldDef &array(bool v = true)
  {
    _array = v;
    return *this;
  }

  // 数值约束
  FieldDef &min(double v)
  {
    _has_min = true;
    _min_val = v;
    return *this;
  }
  FieldDef &max(double v)
  {
    _has_max = true;
    _max_val = v;
    return *this;
  }
  FieldDef &step(double v)
  {
    _step_val = v;
    return *this;
  }
  FieldDef &bit_flag(bool v = true)
  {
    _bit_flag = v;
    return *this;
  }

  // 字符串约束
  FieldDef &max_length(int v)
  {
    _max_length = v;
    return *this;
  }

  // 添加选项
  template <typename V>
  FieldDef &option(V value, std::string label = "")
  {
    _options.push_back({std::any(value), std::move(label), ""});
    return *this;
  }

private:
  friend class Fields<T>;

  std::string _key;
  FieldKind _kind;
  U T::*_member = nullptr;
  std::string _title;
  std::string _desc;
  int _order = -1;
  bool _nullable = false;
  bool _array = false;
  bool _has_min = false;
  bool _has_max = false;
  double _min_val = 0;
  double _max_val = 0;
  double _step_val = 1;
  bool _bit_flag = false;
  int _max_length = 0;
  std::vector<typename FieldInfo::Option> _options;
};

// ============================================================
// field() — 创建字段定义
// ============================================================

/// 版本1：成员指针（默认）
template <typename T, typename U>
FieldDef<T, U> field(std::string key, FieldKind kind, U T::*member,
                     std::string title = "")
{
  return FieldDef<T, U>(std::move(key), kind, member).title(std::move(title));
}

/// 版本2：自定义 getter/setter（无成员指针，T 由 fields<T>() 确定）
struct CustomField
{
  std::string key;
  FieldKind kind = FieldKind::Int;
  std::any getter_any;
  std::any setter_any;
  std::string title;
  std::string desc;
  int order = -1;

  CustomField &set_title(std::string v)
  {
    title = std::move(v);
    return *this;
  }
  CustomField &set_desc(std::string v)
  {
    desc = std::move(v);
    return *this;
  }
  CustomField &set_order(int v)
  {
    order = v;
    return *this;
  }
};

/// field() — 自定义 getter/setter，G/S 从 lambda 推导
template <typename G, typename S>
CustomField field(std::string key, FieldKind kind,
                  G getter, S setter, std::string title = "")
{
  CustomField cf;
  cf.key = std::move(key);
  cf.kind = kind;
  cf.getter_any = std::function(getter);
  cf.setter_any = std::function(setter);
  cf.title = std::move(title);
  return cf;
}

// ============================================================
// fields() — 根据字段定义列表构建 Fields<T>（对应 TS fields 函数）
// ============================================================
template <typename T, typename... Defs>
Fields<T> fields(Defs &&...defs)
{
  Fields<T> result;
  // 用折叠表达式依次添加每个字段
  (result.add_entry(std::forward<Defs>(defs)), ...);
  return result;
}

// 内部实现：FieldDef → Fields::Entry
template <typename T>
template <typename U>
std::size_t Fields<T>::add_entry(FieldDef<T, U> def)
{
  FieldInfo info;
  info.key = std::move(def._key);
  info.kind = def._kind;
  info.order = def._order >= 0 ? def._order : static_cast<int>(_entries.size());
  info.title = std::move(def._title);
  info.desc = std::move(def._desc);
  info.nullable = def._nullable;
  info.array = def._array;
  info.has_min = def._has_min;
  info.has_max = def._has_max;
  info.min_val = def._min_val;
  info.max_val = def._max_val;
  info.step_val = def._step_val;
  info.bit_flag = def._bit_flag;
  info.max_length = def._max_length;
  info.options = std::move(def._options);
  info.value_type = typeid(typename map_traits<U>::mapped_type);
  info.object_type = typeid(U);

  Getter getter = [member = def._member](const T &obj) -> std::any
  { return static_cast<U>(obj.*member); };

  Setter setter = [member = def._member](T &obj, const std::any &val)
  {
    obj.*member = resolve_any<std::decay_t<U>>(val);
  };

  _by_name[info.key] = _entries.size();
  _entries.push_back({std::move(info), std::move(getter), std::move(setter)});
  return _entries.size() - 1;
}

// 内部实现：CustomField → Fields::Entry（自定义 getter/setter）
template <typename T>
std::size_t Fields<T>::add_entry(const CustomField &def)
{
  FieldInfo info;
  info.key = def.key;
  info.kind = def.kind;
  info.order = def.order >= 0 ? def.order : static_cast<int>(_entries.size());
  info.title = def.title;
  info.desc = def.desc;

  auto getter = std::any_cast<Getter>(def.getter_any);
  auto setter = std::any_cast<Setter>(def.setter_any);

  _by_name[info.key] = _entries.size();
  _entries.push_back({std::move(info), std::move(getter), std::move(setter)});
  return _entries.size() - 1;
}

// ============================================================
// reorder_keys — 按 field order 重排对象成员（对应 TS reorder_keys）
// 对 POD 结构体意义不大，但保留 API 兼容
// ============================================================
template <typename T>
void reorder_keys(T & /*obj*/, const Fields<T> & /*fields_map*/)
{
  // C++ 结构体内存布局由编译器决定，无法真正重排
  // 此函数保留作为 API 占位
}

#endif // LFW_CORE_FIELDS_HPP
