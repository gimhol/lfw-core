#include <iostream>
#include <string>
#include <vector>
#include <any>

#include "lfw-core/base/Expression.hpp"

// ============================================================
// 示例 1: 基本用法 — 数值比较
// ============================================================
namespace demo_numeric
{

  // 上下文
  struct Stats
  {
    int hp;
    int mp;
    float distance;
  };

  void run()
  {
    std::cout << "--- demo_numeric: 数值比较 ---\n";

    // 定义值获取器
    auto getter = [](const std::string &word)
        -> std::optional<ValGetter<Stats>>
    {
      if (word == "hp")
        return ValGetter<Stats>{[](const Stats &ctx, const std::string &, const std::string &) -> std::any
                                { return ctx.hp; }};
      if (word == "mp")
        return ValGetter<Stats>{[](const Stats &ctx, const std::string &, const std::string &) -> std::any
                                { return ctx.mp; }};
      if (word == "distance")
        return ValGetter<Stats>{[](const Stats &ctx, const std::string &, const std::string &) -> std::any
                                { return ctx.distance; }};
      return std::nullopt;
    };

    Stats ctx{30, 80, 100.0f};

    // 表达式: hp < 50 && mp > 20
    Expression<Stats> expr1("hp < 50 && mp > 20", getter);
    std::cout << "  \"hp < 50 && mp > 20\" → " << (expr1.run(ctx) ? "true" : "false") << "\n";

    // 表达式: hp >= 100
    Expression<Stats> expr2("hp >= 100", getter);
    std::cout << "  \"hp >= 100\" → " << (expr2.run(ctx) ? "true" : "false") << "\n";

    // 表达式: distance == 100
    Expression<Stats> expr3("distance == 100", getter);
    std::cout << "  \"distance == 100\" → " << (expr3.run(ctx) ? "true" : "false") << "\n";

    // 验证 || 和 && 与 | 和 & 含义一致
    Expression<Stats> expr4("hp < 50 || mp > 100", getter);
    std::cout << "  \"hp < 50 || mp > 100\" → " << (expr4.run(ctx) ? "true" : "false") << "\n";

    Expression<Stats> expr5("hp < 50 && mp > 100", getter);
    std::cout << "  \"hp < 50 && mp > 100\" → " << (expr5.run(ctx) ? "true" : "false") << "\n";

    std::cout << "\n";
  }

} // namespace demo_numeric

// ============================================================
// 示例 2: 字符串比较 + 括号分组 + 取反
// ============================================================
namespace demo_string
{

  struct Unit
  {
    std::string name;
    std::string faction;
    int level;
  };

  void run()
  {
    std::cout << "--- demo_string: 字符串比较 + 括号 + 取反 ---\n";

    auto getter = [](const std::string &word)
        -> std::optional<ValGetter<Unit>>
    {
      if (word == "name")
        return ValGetter<Unit>{[](const Unit &ctx, const std::string &, const std::string &) -> std::any
                               { return ctx.name; }};
      if (word == "faction")
        return ValGetter<Unit>{[](const Unit &ctx, const std::string &, const std::string &) -> std::any
                               { return ctx.faction; }};
      if (word == "level")
        return ValGetter<Unit>{[](const Unit &ctx, const std::string &, const std::string &) -> std::any
                               { return ctx.level; }};
      return std::nullopt;
    };

    Unit ctx{"Arthur", "human", 50};

    // 字符串相等
    Expression<Unit> expr1("faction == human", getter);
    std::cout << "  \"faction == human\" → " << (expr1.run(ctx) ? "true" : "false") << "\n";

    // 括号分组: (faction == human) && !(level >= 100)
    Expression<Unit> expr2("(faction == human) && !(level >= 100)", getter);
    std::cout << "  \"(faction == human) && !(level >= 100)\" → "
              << (expr2.run(ctx) ? "true" : "false") << "\n";

    // 取反分组 "!("
    Expression<Unit> expr3("!(faction == elf)", getter);
    std::cout << "  \"!(faction == elf)\" → " << (expr3.run(ctx) ? "true" : "false") << "\n";

    // 字符串 >, <, >=, <= 比较（按字典序）
    Expression<Unit> expr4("faction > angel", getter);
    std::cout << "  \"faction > angel\" → " << (expr4.run(ctx) ? "true" : "false") << "\n";

    Expression<Unit> expr5("faction < zombie", getter);
    std::cout << "  \"faction < zombie\" → " << (expr5.run(ctx) ? "true" : "false") << "\n";

    Expression<Unit> expr6("name <= Arthur", getter);
    std::cout << "  \"name <= Arthur\" → " << (expr6.run(ctx) ? "true" : "false") << "\n";

    Expression<Unit> expr7("name > Arthur", getter);
    std::cout << "  \"name > Arthur\" → " << (expr7.run(ctx) ? "true" : "false") << "\n";

    std::cout << "\n";
  }

} // namespace demo_string

// ============================================================
// 示例 3: 集合操作 ({{ 包含, }} 被包含)
// ============================================================
namespace demo_set
{

  struct Player
  {
    std::string name;
    std::vector<std::string> buffs;
    std::vector<std::string> items;
  };

  void run()
  {
    std::cout << "--- demo_set: 集合操作 ({{ }}) ---\n";

    auto getter = [](const std::string &word)
        -> std::optional<ValGetter<Player>>
    {
      if (word == "name")
        return ValGetter<Player>{[](const Player &ctx, const std::string &, const std::string &) -> std::any
                                 { return ctx.name; }};
      if (word == "buffs")
        return ValGetter<Player>{[](const Player &ctx, const std::string &, const std::string &) -> std::any
                                 {
                                   std::vector<std::any> result;
                                   for (auto &b : ctx.buffs)
                                     result.push_back(std::any(b));
                                   return result;
                                 }};
      if (word == "items")
        return ValGetter<Player>{[](const Player &ctx, const std::string &, const std::string &) -> std::any
                                 {
                                   std::vector<std::any> result;
                                   for (auto &i : ctx.items)
                                     result.push_back(std::any(i));
                                   return result;
                                 }};
      return std::nullopt;
    };

    Player ctx{"Hero", {"shield", "haste"}, {"sword", "potion"}};

    // buffs 包含 "shield"
    Expression<Player> expr1("buffs {{ shield", getter);
    std::cout << "  \"buffs {{ shield\" → " << (expr1.run(ctx) ? "true" : "false") << "\n";

    // "sword" 在 items 中
    Expression<Player> expr2("items {{ sword", getter);
    std::cout << "  \"items {{ sword\" → " << (expr2.run(ctx) ? "true" : "false") << "\n";

    // 不包含
    Expression<Player> expr3("buffs !{ poison", getter);
    std::cout << "  \"buffs !{ poison\" → " << (expr3.run(ctx) ? "true" : "false") << "\n";

    std::cout << "\n";
  }

} // namespace demo_set

// ============================================================
// 示例 4: 静态求值（无需 getter，两边都是字面量）
// ============================================================
namespace demo_static
{

  void run()
  {
    std::cout << "--- demo_static: 静态求值 ---\n";

    // 无需 getter，所有操作数都是字面量
    auto getter = [](const std::string &) -> std::optional<ValGetter<int>>
    { return std::nullopt; };

    auto show = [&](auto &expr, const char *label)
    {
      bool r = expr.run(0);
      std::cout << "  \"" << label << "\" → " << (r ? "true" : "false");
      if (auto *w = expr.warn())
        std::cout << "  ⚠ " << *w;
      std::cout << "\n";
    };

    Expression<int> expr1("100 > 50", getter);
    show(expr1, "100 > 50");

    Expression<int> expr2("3.14 == 3.14", getter);
    show(expr2, "3.14 == 3.14");

    Expression<int> expr3("10 <= 5", getter);
    show(expr3, "10 <= 5");

    // 复合静态表达式 — 子节点也有警告
    Expression<int> expr4("(10 > 5) && (3 < 8)", getter);
    show(expr4, "(10 > 5) && (3 < 8)");

    std::cout << "\n";
  }

} // namespace demo_static

// ============================================================
// 示例 5: 错误处理
// ============================================================
namespace demo_error
{

  void run()
  {
    std::cout << "--- demo_error: 错误处理 ---\n";

    auto getter = [](const std::string &) -> std::optional<ValGetter<int>>
    { return std::nullopt; };

    // 无效运算符
    Expression<int> expr1("a ?? b", getter);
    std::cout << "  \"a ?? b\" result = " << (expr1.run(0) ? "true" : "false");
    if (auto *e = expr1.err())
      std::cout << "  error: " << *e;
    std::cout << "\n";

    // 空表达式
    Expression<int> expr2("", getter);
    std::cout << "  \"\" result = " << (expr2.run(0) ? "true" : "false") << "\n";

    std::cout << "\n";
  }

} // namespace demo_error

// ============================================================
// 示例 6: 运算符优先级 — & (AND) 优先级高于 | (OR)
// ============================================================
namespace demo_precedence
{

  struct Ctx
  {
    bool a;
    bool b;
    bool c;
  };

  void run()
  {
    std::cout << "--- demo_precedence: & 优先级高于 | ---\n";

    auto getter = [](const std::string &word) -> std::optional<ValGetter<Ctx>>
    {
      if (word == "a" || word == "b" || word == "c")
        return ValGetter<Ctx>{[word](const Ctx &ctx, const std::string &, const std::string &) -> std::any
                              {
                                if (word == "a")
                                  return ctx.a;
                                if (word == "b")
                                  return ctx.b;
                                return ctx.c;
                              }};
      return std::nullopt;
    };

    // a & b | c   →   (a & b) | c
    // a=true, b=true, c=false  →  (true & true) | false = true | false = true
    Ctx ctx1{true, true, false};
    Expression<Ctx> expr1("a == true & b == true | c == true", getter);
    std::cout << "  \"a==true & b==true | c==true\" (a=T,b=T,c=F)"
              << " → " << (expr1.run(ctx1) ? "true" : "false") << "\n";

    // a | b & c   →   a | (b & c)
    // a=false, b=true, c=true  →  false | (true & true) = false | true = true
    Ctx ctx2{false, true, true};
    Expression<Ctx> expr2("a == true | b == true & c == true", getter);
    std::cout << "  \"a==true | b==true & c==true\" (a=F,b=T,c=T)"
              << " → " << (expr2.run(ctx2) ? "true" : "false") << "\n";

    // a & b | c & d   →   (a & b) | (c & d)
    // a=true, b=false, c=true, d=true  →  (T&F) | (T&T) = F | T = T
    // 用字面量测试 4 项
    auto literal_getter = [](const std::string &) -> std::optional<ValGetter<int>>
    { return std::nullopt; };
    Expression<int> expr3("1==1 & 0==1 | 1==1 & 1==1", literal_getter);
    std::cout << "  \"1==1 & 0==1 | 1==1 & 1==1\""
              << " → " << (expr3.run(0) ? "true" : "false")
              << "  (期望: (T&F)|(T&T) = F|T = T)\n";

    // 验证 || 和 && 与 | 和 & 含义一致
    Expression<int> expr4("1==1 && 0==1 || 1==1 && 1==1", literal_getter);
    std::cout << "  \"1==1 && 0==1 || 1==1 && 1==1\""
              << " → " << (expr4.run(0) ? "true" : "false")
              << "  (双字符，应与 &/| 结果一致)\n";

    std::cout << "\n";
  }

} // namespace demo_precedence

// ============================================================
// 统一入口
// ============================================================
void run_expression_demos()
{
  demo_numeric::run();
  demo_string::run();
  demo_set::run();
  demo_static::run();
  demo_error::run();
  demo_precedence::run();
}
