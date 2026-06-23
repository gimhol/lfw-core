#ifndef LFW_CORE_FSM_HPP
#define LFW_CORE_FSM_HPP

#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>

#include "lfw-core/base/Signal.hpp"

// ============================================================
// IState — 状态接口
// ============================================================
template <typename K>
class IState
{
public:
  virtual ~IState() = default;
  virtual K key() const = 0;
  virtual const char *name() const { return nullptr; }

  /** @return 下一个状态的 key，std::nullopt 表示不切换 */
  virtual std::optional<K> update(float dt) { return std::nullopt; }
  virtual void enter() {}
  virtual void leave() {}
};

// ============================================================
// FSM — 有限状态机，回调基于 Signal
// ============================================================
template <typename K, typename S = IState<K>>
class FSM
{
  static_assert(std::is_base_of_v<IState<K>, S>,
                "S must inherit from IState<K>");

public:
  // 状态变更信号: void(const FSM&)
  Signal<const FSM &> on_state_changed_signal;

private:
  std::string _name;
  std::map<K, S *> _state_map; // 状态池，不拥有所有权
  S *_state = nullptr;
  S *_prev_state = nullptr;
  float _time = 0;
  float _state_time = 0;

  std::function<void(const std::string &)> _logger;

public:
  static std::function<void(const std::string &)> default_logger;

  explicit FSM(std::string name = "")
      : _name(std::move(name))
  {
    _logger = default_logger;
  }

  // --- 属性 ---
  const std::string &name() const { return _name; }
  void set_name(const std::string &n) { _name = n; }

  S *state() const { return _state; }
  S *prev_state() const { return _prev_state; }
  float time() const { return _time; }
  float state_time() const { return _state_time; }
  void set_time(float t) { _time = t; }

  const std::map<K, S *> &states() const { return _state_map; }

  // --- 注册状态变更回调（便捷方法，返回连接 id）---
  template <typename T>
  std::size_t on_state_changed(T *obj, void (T::*cb)(const FSM &))
  {
    return on_state_changed_signal.on(obj, cb);
  }

  std::size_t on_state_changed_fn(void (*cb)(const FSM &))
  {
    return on_state_changed_signal.on_fn(cb);
  }

  // --- 日志 ---
  FSM &logger(std::function<void(const std::string &)> log)
  {
    _logger = std::move(log);
    return *this;
  }

  // --- 状态管理 ---
  S *get(const K &key) const
  {
    auto it = _state_map.find(key);
    return it != _state_map.end() ? it->second : nullptr;
  }

  /** 添加单个状态（指针） */
  FSM &add(S *state)
  {
    if (state)
      _state_map[state->key()] = state;
    return *this;
  }

  /** 添加单个状态（引用） */
  FSM &add(S &state)
  {
    _state_map[state.key()] = &state;
    return *this;
  }

  /** 批量添加状态 */
  template <typename... Args>
  FSM &add(S &first, Args &...rest)
  {
    add(first);
    (add(rest), ...);
    return *this;
  }

  /** 立即切换到指定 key 的状态 */
  FSM &use(const K &key)
  {
    if (auto *next = get(key))
      set_state(next);
    return *this;
  }

  /** 切换状态核心 */
  void set_state(S *next_state)
  {
    // 避免重复切换到同一个状态
    if (next_state == _state)
      return;

    _prev_state = _state;

    if (_state)
      _state->leave();

    _state_time = 0;
    _state = next_state;

    if (_state)
      _state->enter();

    // 日志（使用 key_to_string 统一处理）
    if (_logger)
    {
      auto prev_label = label_of(_prev_state);
      auto next_label = label_of(_state);
      _logger("[" + _name + "::state] " +
              prev_label + " ==> " + next_label);
    }

    // 触发 Signal 回调
    on_state_changed_signal.emit(*this);
  }

  /** 每帧更新 */
  void update(float dt)
  {
    _time += dt;
    _state_time += dt;
    if (!_state)
      return;

    auto next_key = _state->update(dt);
    if (!next_key.has_value())
      return;

    auto *next_state = get(*next_key);
    if (!next_state)
      return;

    set_state(next_state);
  }

private:
  // 获取状态的可读标签
  static std::string label_of(S *s)
  {
    if (!s)
      return "(null)";
    if (s->name())
      return s->name();
    // 通过 key() 转为 string
    return key_str(s->key());
  }

  // key 转 string — 根据类型自动选择
  template <typename T>
  static std::string key_str(const T &key)
  {
    if constexpr (std::is_same_v<T, std::string>)
      return key;
    else if constexpr (std::is_arithmetic_v<T>)
      return std::to_string(key);
    else
      return std::to_string(static_cast<int>(key));
  }
};

// 默认 logger（可外部设置，设为 nullptr 则不输出日志）
template <typename K, typename S>
std::function<void(const std::string &)> FSM<K, S>::default_logger = nullptr;

#endif // LFW_CORE_FSM_HPP

// ============================================================
// 用法示例
// ============================================================
#if 0
#include <iostream>

// ① 定义状态枚举
enum class PlayerState { Idle, Run, Jump, Fall };

// ② 实现状态
class IdleState : public IState<PlayerState> {
    PlayerState key() const override { return PlayerState::Idle; }
    const char* name() const override { return "Idle"; }
    void enter() override { std::cout << "进入 Idle\n"; }
    void leave() override { std::cout << "离开 Idle\n"; }

    std::optional<PlayerState> update(float dt) override {
        // 检测切换到 Run
        if (/* 按了移动键 */) return PlayerState::Run;
        if (/* 按了跳 */)      return PlayerState::Jump;
        return std::nullopt;
    }
};

class RunState : public IState<PlayerState> {
    PlayerState key() const override { return PlayerState::Run; }
    const char* name() const override { return "Run"; }
    void enter() override { std::cout << "进入 Run\n"; }
    void leave() override { std::cout << "离开 Run\n"; }

    std::optional<PlayerState> update(float dt) override {
        if (/* 松开移动 */) return PlayerState::Idle;
        if (/* 按了跳 */)   return PlayerState::Jump;
        return std::nullopt;
    }
};

// ③ 使用
int main() {
    FSM<PlayerState> fsm("Player");
    IdleState idle;
    RunState  run;

    fsm.add(idle, run);          // 注册状态
    fsm.use(PlayerState::Idle);  // 初始状态

    // 监听状态变更
    fsm.on_state_changed([](const FSM<PlayerState>& fsm) {
        auto* s = fsm.state();
        std::cout << "状态变了 -> " << (s ? s->name() : "null") << "\n";
    });

    // 游戏循环
    while (running) {
        fsm.update(1.0f / 60.0f);
    }
}
#endif