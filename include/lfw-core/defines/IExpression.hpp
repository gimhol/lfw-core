#ifndef LFW_CORE_DEFINES_IEXPRESSION_HPP
#define LFW_CORE_DEFINES_IEXPRESSION_HPP

// ============================================================
// IExpression — 表达式接口
// 对应 TypeScript 的 IExpression<T>
// ============================================================
template <typename T>
struct IExpression
{
  virtual ~IExpression() = default;
  virtual bool run(const T &arg) = 0;
};

/// void 特化 — IExpression<void>::run() 无需参数
template <>
struct IExpression<void>
{
  virtual ~IExpression() = default;
  virtual bool run() = 0;
};

#endif // LFW_CORE_DEFINES_IEXPRESSION_HPP
