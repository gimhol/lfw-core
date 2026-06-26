#ifndef LFW_CORE_STATE_STATES_H
#define LFW_CORE_STATE_STATES_H

#include <functional>
#include <map>
#include <vector>

#include "lfw-core/defines/EntityType.hpp"
#include "lfw-core/core.hpp"

LFW_NS_BEGIN

class State_Base;

/// States — 状态注册表，对应 TS States
class States
{
public:
  /// 按 state code 查找
  State_Base *get(int key) const;

  /// 注册状态
  void set(int key, State_Base *value);

  /// 批量添加，以 value->state 为 key
  void add(std::initializer_list<State_Base *> values);

  /// 按 [from, to] 范围批量创建
  void set_in_range(int from, int to, const std::function<State_Base *(int)> &create);

  /// 按 key 列表批量创建
  void set_all_of(const std::vector<int> &keys, const std::function<State_Base *(int)> &create);

  /// 按 EntityType + code 查找，无则创建默认状态
  State_Base *fallback(EntityType type, int code);

private:
  std::map<int, State_Base *> state_map;
};

LFW_NS_END

#endif
