#ifndef LFW_CORE_EXPRESSION_H
#define LFW_CORE_EXPRESSION_H

#include <algorithm>
#include <any>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// ============================================================
// 比较辅助 — 处理 std::any 之间的比较
// ============================================================
namespace detail
{

  template <typename T>
  T any_cast_loose(const std::any &v)
  {
    // Try direct cast first
    try
    {
      return std::any_cast<T>(v);
    }
    catch (...)
    {
    }
    // Try number conversion
    if constexpr (std::is_arithmetic_v<T>)
    {
      try
      {
        if (v.type() == typeid(bool))
          return static_cast<T>(std::any_cast<bool>(v) ? 1 : 0);
        if (v.type() == typeid(int))
          return static_cast<T>(std::any_cast<int>(v));
        if (v.type() == typeid(float))
          return static_cast<T>(std::any_cast<float>(v));
        if (v.type() == typeid(double))
          return static_cast<T>(std::any_cast<double>(v));
        if (v.type() == typeid(long))
          return static_cast<T>(std::any_cast<long>(v));
        if (v.type() == typeid(long long))
          return static_cast<T>(std::any_cast<long long>(v));
      }
      catch (...)
      {
      }
    }
    throw std::bad_any_cast();
  }

  // 尝试转为 double 用于数值比较
  inline std::optional<double> to_number(const std::any &v)
  {
    // Try numeric any_cast first
    try
    {
      return any_cast_loose<double>(v);
    }
    catch (...)
    {
    }
    // Try parsing from string
    try
    {
      return std::stod(std::any_cast<std::string>(v));
    }
    catch (...)
    {
    }
    return std::nullopt;
  }

  // 尝试转为 string 用于字符串比较
  inline std::optional<std::string> to_string(const std::any &v)
  {
    try
    {
      return std::any_cast<std::string>(v);
    }
    catch (...)
    {
    }
    // Handle bool specifically
    try
    {
      if (v.type() == typeid(bool))
        return std::any_cast<bool>(v) ? "true" : "false";
    }
    catch (...)
    {
    }
    try
    {
      return std::to_string(any_cast_loose<double>(v));
    }
    catch (...)
    {
    }
    return std::nullopt;
  }

  // 将 std::any 转为 vector<any>
  inline std::optional<std::vector<std::any>> to_vec(const std::any &v)
  {
    try
    {
      return std::any_cast<std::vector<std::any>>(v);
    }
    catch (...)
    {
    }
    try
    {
      return std::vector<std::any>{v};
    }
    catch (...)
    {
    }
    return std::nullopt;
  }

} // namespace detail

// ============================================================
// 谓词映射 — 对应 TypeScript 的 predicate_maps
// ============================================================
using PredicateFn = std::function<bool(const std::any &, const std::any &)>;

/// 获取默认谓词表的 const 引用（避免重复构造）
inline const std::map<std::string, PredicateFn> &default_predicates()
{
  static const auto predicates = []() -> std::map<std::string, PredicateFn>
  {
    std::map<std::string, PredicateFn> m;

    m["=="] = [](const std::any &a, const std::any &b) -> bool
    {
      auto na = detail::to_number(a);
      auto nb = detail::to_number(b);
      if (na && nb)
        return *na == *nb;
      auto sa = detail::to_string(a);
      auto sb = detail::to_string(b);
      if (sa && sb)
        return *sa == *sb;
      return false;
    };

    m["!="] = [](const std::any &a, const std::any &b) -> bool
    {
      auto na = detail::to_number(a);
      auto nb = detail::to_number(b);
      if (na && nb)
        return *na != *nb;
      auto sa = detail::to_string(a);
      auto sb = detail::to_string(b);
      if (sa && sb)
        return *sa != *sb;
      return true;
    };

    m[">="] = [](const std::any &a, const std::any &b) -> bool
    {
      auto na = detail::to_number(a);
      auto nb = detail::to_number(b);
      if (na && nb)
        return *na >= *nb;
      auto sa = detail::to_string(a);
      auto sb = detail::to_string(b);
      if (sa && sb)
        return *sa >= *sb;
      return false;
    };

    m["<="] = [](const std::any &a, const std::any &b) -> bool
    {
      auto na = detail::to_number(a);
      auto nb = detail::to_number(b);
      if (na && nb)
        return *na <= *nb;
      auto sa = detail::to_string(a);
      auto sb = detail::to_string(b);
      if (sa && sb)
        return *sa <= *sb;
      return false;
    };

    m[">"] = [](const std::any &a, const std::any &b) -> bool
    {
      auto na = detail::to_number(a);
      auto nb = detail::to_number(b);
      if (na && nb)
        return *na > *nb;
      auto sa = detail::to_string(a);
      auto sb = detail::to_string(b);
      if (sa && sb)
        return *sa > *sb;
      return false;
    };

    m["<"] = [](const std::any &a, const std::any &b) -> bool
    {
      auto na = detail::to_number(a);
      auto nb = detail::to_number(b);
      if (na && nb)
        return *na < *nb;
      auto sa = detail::to_string(a);
      auto sb = detail::to_string(b);
      if (sa && sb)
        return *sa < *sb;
      return false;
    };

    // "{{" 用指针引用 "==" predicate
    m["{{"] = [](const std::any &a, const std::any &b) -> bool
    {
      auto va = detail::to_vec(a);
      auto vb = detail::to_vec(b);
      if (!va || !vb)
        return false;
      const auto &eq = default_predicates().at("==");
      for (const auto &item : *vb)
      {
        if (std::find_if(va->begin(), va->end(), [&](const std::any &x)
                         { return eq(x, item); }) == va->end())
          return false;
      }
      return true;
    };

    m["}}"] = [](const std::any &a, const std::any &b) -> bool
    {
      return default_predicates().at("{{")(b, a);
    };

    m["!{"] = [](const std::any &a, const std::any &b) -> bool
    {
      return !default_predicates().at("{{")(a, b);
    };

    m["!}"] = [](const std::any &a, const std::any &b) -> bool
    {
      return !default_predicates().at("}}")(a, b);
    };

    return m;
  }();

  return predicates;
}

// ============================================================
// 值获取器类型 — 对应 IValGetter / IValGetterGetter
// 使用 void* 消除模板，由调用方 static_cast 还原上下文
// ============================================================
using ValGetter = std::function<std::any(void *ctx, const std::string &word, const std::string &op)>;

using ValGetterGetter = std::function<std::optional<ValGetter>(const std::string &word)>;

// ============================================================
// IExpression — 表达式接口（无模板，void* 上下文）
// 对应 TS IExpression
// ============================================================
struct IExpression
{
  virtual ~IExpression() = default;
  virtual bool run(void *ctx) = 0;
};

// ============================================================
// IJudger — 求值器接口（无模板，继承 IExpression）
// 对应 TS IJudger<T>：在 IExpression 上增加元数据
// ============================================================
struct IJudger : IExpression
{
  virtual const std::string &text() const = 0;
  virtual const std::string *err() const { return nullptr; }
  virtual const std::string *warn() const { return nullptr; }
  virtual std::optional<bool> result() const { return std::nullopt; }
};

// ============================================================
// ALWAYS_FALSE 辅助
// ============================================================
class AlwaysFalseJudger : public IJudger
{
  std::string _text;
  std::string _err;

public:
  AlwaysFalseJudger(std::string text, std::string err)
      : _text(std::move(text)), _err(std::move(err)) {}
  bool run(void *) override { return false; }
  const std::string &text() const override { return _text; }
  const std::string *err() const override { return &_err; }
  std::optional<bool> result() const override { return false; }
};

inline std::unique_ptr<IJudger> always_false(std::string text, std::string err = "")
{
  return std::make_unique<AlwaysFalseJudger>(std::move(text), std::move(err));
}

// ============================================================
// Expression — 表达式引擎（核心）
// 对应 TS Expression<T1,T2>，void* 上下文 + std::any 值
// ============================================================
class Expression : public IJudger
{
public:
  // 子表达式
  std::vector<std::unique_ptr<IJudger>> children;
  std::vector<std::string> before; // child 之前的逻辑符号（空/"|"/"&"）
  ValGetterGetter get_val_getter;
  std::string _err;
  std::string _warn;
  std::string _text;
  std::optional<bool> _result;
  bool _not = false;

  // judger 模式字段
  std::string op;
  std::any val_1;
  std::any val_2;

  // judger 模式的运行函数（void* 上下文）
  std::function<bool(void *)> _run_fn;

  // 谓词表（可外部替换，默认用 default_predicates）
  std::map<std::string, PredicateFn> predicates = default_predicates();

  Expression() = default;

  // 构造函数：解析表达式字符串
  Expression(const std::string &input, ValGetterGetter getter)
      : get_val_getter(std::move(getter))
  {
    if (input.empty())
      return;
    _text = strip_whitespace(input);
    parse_group();
  }

private:
  // 去除空白
  static std::string strip_whitespace(const std::string &s)
  {
    std::string out;
    for (char c : s)
    {
      if (c != ' ' && c != '\n' && c != '\r' && c != '\t')
        out += c;
    }
    return out;
  }

  // 递归解析
  void parse_group()
  {
    auto &text = _text;
    std::size_t p = 0;
    std::size_t i = 0;
    std::string before_sym;

    auto add_child = [&](std::unique_ptr<IJudger> child)
    {
      children.push_back(std::move(child));
      this->before.push_back(before_sym);
      before_sym.clear();
    };

    // 找到匹配的右括号（跳过嵌套括号）
    auto find_matching_paren = [&](std::size_t start) -> std::size_t
    {
      int depth = 1;
      for (std::size_t j = start; j < text.size(); ++j)
      {
        if (text[j] == '(')
          ++depth;
        else if (text[j] == ')')
        {
          --depth;
          if (depth == 0)
            return j;
        }
      }
      return std::string::npos;
    };

    while (i <= text.size())
    {
      char c = (i < text.size()) ? text[i] : '\0';

      if (c == '!' && (i + 1) < text.size() && text[i + 1] == '(')
      {
        // "!(" 取反分组
        auto end = find_matching_paren(i + 2);
        if (end == std::string::npos)
          break;

        auto child = std::make_unique<Expression>();
        child->get_val_getter = get_val_getter;
        child->predicates = predicates;
        child->_not = true;
        child->_text = text.substr(i + 2, end - i - 2);
        child->parse_group();

        i = end;
        p = end + 1;
        add_child(std::move(child));
      }
      else if (c == '(')
      {
        // "( 分组"
        auto end = find_matching_paren(i + 1);
        if (end == std::string::npos)
          break;

        auto child = std::make_unique<Expression>();
        child->get_val_getter = get_val_getter;
        child->predicates = predicates;
        child->_text = text.substr(i + 1, end - i - 1);
        child->parse_group();

        i = end;
        p = end + 1;
        add_child(std::move(child));
      }
      else if (c == '|' || c == '&')
      {
        bool db = (i + 1) < text.size() && text[i + 1] == c;
        if (db)
          ++i;

        if (p < i)
        {
          auto sub = text.substr(p, db ? i - 1 - p : i - p);
          if (!sub.empty())
          {
            auto child = std::make_unique<Expression>();
            child->get_val_getter = get_val_getter;
            child->predicates = predicates;
            child->judger(sub);
            add_child(std::move(child));
          }
        }
        before_sym = std::string(1, c);
        p = i + 1;
      }
      else if (c == ')' || c == '\0')
      {
        if (p < i)
        {
          auto child = std::make_unique<Expression>();
          child->get_val_getter = get_val_getter;
          child->predicates = predicates;
          child->judger(text.substr(p, i - p));
          add_child(std::move(child));
        }
        break;
      }
      ++i;
    }
    _text = text.substr(0, i);
  }

public:
  // judger — 解析原子表达式 "word1 op word2"
  void judger(const std::string &text)
  {
    _text = text;
    if (text.empty())
    {
      set_error("[empty text]");
      return;
    }

    // 静态 regex 避免重复构造开销
    static const std::regex re1(R"((\S*)\s*(==|!=|<=|>=|\{\{|\}\}|!\{|!\})\s?(\S*))");
    static const std::regex re2(R"((\S*)\s*(=|<|>)\s?(\S*))");
    std::smatch m;
    if (std::regex_match(text, m, re1) && m.size() >= 4)
    {
      parse_judger(m[1].str(), m[2].str(), m[3].str());
      return;
    }

    if (std::regex_match(text, m, re2) && m.size() >= 4)
    {
      parse_judger(m[1].str(), m[2].str(), m[3].str());
      return;
    }

    set_error("[wrong expression: " + text + "]");
  }

private:
  void parse_judger(const std::string &word1, const std::string &op_str, const std::string &word2)
  {
    op = op_str;

    if (word1.empty() || word2.empty())
    {
      set_error("[wrong expression: " + _text + "]");
      return;
    }

    auto it = predicates.find(op);
    if (it == predicates.end())
    {
      set_error("wrong operator: " + op);
      return;
    }

    auto getter_1 = get_val_getter(word1);
    auto getter_2 = get_val_getter(word2);

    bool is_set_op = (op == "{{" || op == "}}" || op == "!{" || op == "!}");

    // 处理字面量（自动检测数字）
    if (!getter_1)
    {
      val_1 = is_set_op ? split_csv(word1) : parse_literal(word1);
    }
    if (!getter_2)
    {
      val_2 = is_set_op ? split_csv(word2) : parse_literal(word2);
    }

    // 如果两边都无 getter，静态求值（结果固定，大概率是写错了变量名）
    if (!getter_1 && !getter_2)
    {
      bool result = it->second(val_1, val_2);
      _result = result;
      _warn = "expression \"" + _text + "\" is always " + (result ? "true" : "false") + " (both operands are literals)";
      _run_fn = [result](void *)
      { return result; };
      return;
    }

    // 运行时求值
    auto pred = it->second;
    _run_fn = [this, pred,
               getter_1 = std::move(getter_1),
               getter_2 = std::move(getter_2),
               v1 = val_1, v2 = val_2,
               w1 = word1, w2 = word2](void *ctx) -> bool
    {
      auto a = getter_1 ? (*getter_1)(ctx, w1, this->op) : v1;
      auto b = getter_2 ? (*getter_2)(ctx, w2, this->op) : v2;
      return pred(a, b);
    };
  }

  void set_error(const std::string &err)
  {
    _err = err;
    _result = false;
    _run_fn = [](void *)
    { return false; };
  }

  // 解析字面量：自动检测并转换数字
  static std::any parse_literal(const std::string &s)
  {
    // 尝试解析为整数
    char *end = nullptr;
    long long int_val = std::strtoll(s.c_str(), &end, 10);
    if (end == s.c_str() + s.size())
      return std::any(static_cast<int>(int_val));

    // 尝试解析为浮点数
    double fp_val = std::strtod(s.c_str(), &end);
    if (end == s.c_str() + s.size())
      return std::any(fp_val);

    // 作为字符串
    return std::any(s);
  }

  static std::vector<std::any> split_csv(const std::string &s)
  {
    std::vector<std::any> result;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, ','))
    {
      if (!item.empty())
        result.push_back(std::any(item));
    }
    return result;
  }

public:
  // --- IJudger 接口 ---
  bool run(void *ctx) override
  {
    if (_run_fn)
    {
      _result = _run_fn(ctx);
      return *_result;
    }

    // 有 children：先合并 &（AND）链，再合并 |（OR）链
    // 保证 & 优先级高于 |，对应 TypeScript 的 run 逻辑
    bool or_result = false;
    std::optional<bool> and_result;
    for (std::size_t i = 0; i < children.size(); ++i)
    {
      bool val = children[i]->run(ctx);

      if (i == 0 || before[i].empty())
      {
        and_result = val;
      }
      else if (before[i] == "&")
      {
        and_result = *and_result && val;
      }
      else if (before[i] == "|")
      {
        or_result = or_result || *and_result;
        and_result = val;
      }
    }
    if (and_result.has_value())
    {
      or_result = or_result || *and_result;
    }
    _result = _not ? !or_result : or_result;
    return *_result;
  }

  const std::string &text() const override { return _text; }
  const std::string *err() const override
  {
    return _err.empty() ? nullptr : &_err;
  }
  const std::string *warn() const override
  {
    if (!_warn.empty())
      return &_warn;
    // 传播子节点的警告
    for (auto &child : children)
    {
      auto *w = child->warn();
      if (w)
        return w;
    }
    return nullptr;
  }
  std::optional<bool> result() const override { return _result; }
};

// ============================================================
// 用法示例
// ============================================================
#if 0

// ① 定义上下文
struct BattleContext {
    int hp;
    int mp;
    float distance;
    std::string state;
    std::vector<std::string> buffs;
};

// ② 定义值获取器
auto getter = [](const std::string& word) ->
    std::optional<ValGetter<BattleContext>>
{
    if (word == "hp") {
        return ValGetter<BattleContext>{
            [](const BattleContext& ctx, const std::string&, const std::string&) -> std::any {
                return ctx.hp;
            }
        };
    }
    if (word == "mp") {
        return ValGetter<BattleContext>{
            [](const BattleContext& ctx, const std::string&, const std::string&) -> std::any {
                return ctx.mp;
            }
        };
    }
    if (word == "distance") {
        return ValGetter<BattleContext>{
            [](const BattleContext& ctx, const std::string&, const std::string&) -> std::any {
                return ctx.distance;
            }
        };
    }
    if (word == "state") {
        return ValGetter<BattleContext>{
            [](const BattleContext& ctx, const std::string&, const std::string&) -> std::any {
                return ctx.state;
            }
        };
    }
    if (word == "buffs") {
        return ValGetter<BattleContext>{
            [](const BattleContext& ctx, const std::string&, const std::string&) -> std::any {
                std::vector<std::any> result;
                for (auto& b : ctx.buffs) result.push_back(std::any(b));
                return result;
            }
        };
    }
    return std::nullopt;
};

// ③ 使用
int main() {
    // 解析表达式
    Expression<BattleContext> expr("hp < 50 && mp > 30", getter);

    BattleContext ctx{30, 80, 100.0f, "idle", {"shield"}};
    bool result = expr.run(ctx); // true: hp<50 && mp>30

    // 括号分组 + 取反
    Expression<BattleContext> expr2("!(hp >= 100) && state == idle", getter);

    // 包含操作
    Expression<BattleContext> expr3("buffs {{ shield", getter);

    // 也可以静态求值（两边都是字面量）
    Expression<BattleContext> expr4("100 > 50", getter);
    bool always_true = expr4.run(ctx); // true, 永远为 true
}

#endif

#endif // LFW_CORE_EXPRESSION_H