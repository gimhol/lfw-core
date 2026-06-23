#ifndef LFW_CORE_IEXPRESSION_HPP
#define LFW_CORE_IEXPRESSION_HPP

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

#endif // LFW_CORE_IEXPRESSION_HPP
