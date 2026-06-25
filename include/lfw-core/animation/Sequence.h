#ifndef LFW_CORE_ANIMATION_SEQUENCE_H
#define LFW_CORE_ANIMATION_SEQUENCE_H

#include <memory>
#include <vector>

#include "lfw-core/animation/Animation.h"

LFW_NS_BEGIN

/**
 * 序列动画 — 对应 TS Sequence
 *
 * 将多个 Animation 按顺序串联播放。
 */
class Sequence : public Animation
{
public:
  static const char *tag();

  Sequence() = default;
  Sequence(std::initializer_list<std::shared_ptr<Animation>> anims);

  void add(std::shared_ptr<Animation> anim);

  const std::vector<std::shared_ptr<Animation>> &anims() const;
  std::shared_ptr<Animation> curr_anim() const;

  Animation &start(bool reverse_val) override;
  Animation &end(bool reverse_val) override;
  Animation &calc() override;

private:
  void recompute_duration();

  std::vector<std::shared_ptr<Animation>> _anims;
  std::shared_ptr<Animation> _curr_anim;
};

LFW_NS_END

#endif
