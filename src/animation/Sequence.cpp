#include "lfw-core/animation/Sequence.hpp"

LFW_NS_BEGIN

void Sequence::recompute_duration()
{
  double total = 0;
  for (const auto &a : _anims)
    total += a->duration();
  _duration = total;
}

Animation &Sequence::start(bool reverse_val)
{
  Animation::start(reverse_val);

  if (_anims.empty())
  {
    _curr_anim.reset();
    return *this;
  }

  _curr_anim = reverse_val ? _anims.back() : _anims.front();
  return *this;
}

Animation &Sequence::end(bool reverse_val)
{
  Animation::end(reverse_val);

  if (_anims.empty())
  {
    _curr_anim.reset();
    return *this;
  }

  _curr_anim = reverse_val ? _anims.front() : _anims.back();
  return *this;
}

Animation &Sequence::calc()
{
  double t = _time;
  bool rev = reverse();
  double dur = _duration;
  const auto &as = _anims;
  std::size_t len = as.size();

  if (len == 0)
    return *this;

  if (t >= dur)
  {
    auto &a = as.back();
    _curr_anim = a;
    a->set_time(a->duration());
    _value = a->calc().value();
    return *this;
  }

  if (t <= 0)
  {
    auto &a = as.front();
    _curr_anim = a;
    a->set_time(0);
    _value = a->calc().value();
    return *this;
  }

  if (rev)
  {
    double remaining = dur;
    for (std::size_t i = len; i-- > 0;)
    {
      auto &anim = as[i];
      remaining -= anim->duration();
      if (t > remaining)
      {
        anim->set_time(t - remaining);
        _value = anim->calc().value();
        _curr_anim = anim;
        break;
      }
    }
  }
  else
  {
    double elapsed = t;
    for (std::size_t i = 0; i < len; ++i)
    {
      auto &anim = as[i];
      if (anim->duration() > elapsed)
      {
        anim->set_time(elapsed);
        _value = anim->calc().value();
        _curr_anim = anim;
        break;
      }
      elapsed -= anim->duration();
    }
  }

  return *this;
}

LFW_NS_END
