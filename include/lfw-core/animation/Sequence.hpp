#ifndef LFW_CORE_ANIMATION_SEQUENCE_HPP
#define LFW_CORE_ANIMATION_SEQUENCE_HPP

#include <memory>
#include <vector>

#include "lfw-core/animation/Animation.hpp"

LFW_NS_BEGIN

/**
 * 序列动画 — 对应 TS Sequence
 *
 * 将多个 Animation 按顺序串联播放。
 */
class Sequence : public Animation
{
public:
  static const char *tag() { return "Sequence"; }

  Sequence() = default;

  /// 通过初始化列表构造
  Sequence(std::initializer_list<std::shared_ptr<Animation>> anims)
  {
    for (auto &a : anims)
      add(a);
  }

  /// 添加子动画
  void add(std::shared_ptr<Animation> anim)
  {
    _anims.push_back(std::move(anim));
    recompute_duration();
  }

  /// 子动画列表
  const std::vector<std::shared_ptr<Animation>> &anims() const { return _anims; }

  /// 当前播放到的子动画
  std::shared_ptr<Animation> curr_anim() const { return _curr_anim; }

  Animation &start(bool reverse_val) override;
  Animation &end(bool reverse_val) override;
  Animation &calc() override;

private:
  void recompute_duration();

  std::vector<std::shared_ptr<Animation>> _anims;
  std::shared_ptr<Animation> _curr_anim;
};

LFW_NS_END

#endif // LFW_CORE_ANIMATION_SEQUENCE_HPP
