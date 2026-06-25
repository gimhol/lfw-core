#ifndef LFW_CORE_BG_LAYER_H
#define LFW_CORE_BG_LAYER_H

#include "lfw-core/core.hpp"
#include "lfw-core/defines/IBgLayerInfo.hpp"

LFW_NS_BEGIN

class Background;

/**
 * 背景图层 — 对应 TS Layer
 */
class Layer
{
public:
  const Background &bg;
  const IBgLayerInfo info; // 值拷贝，避免 add_layer 中临时对象悬空
  bool visible = false;

  Layer(const Background &bg_ref, const IBgLayerInfo &info_ref)
      : bg(bg_ref), info(info_ref) {}

  bool is_static() const
  {
    bool no_cc = (!info.cc.has_value() || !info.c1.has_value() || !info.c2.has_value());
    return no_cc &&
           !info.offsetAnimX.has_value() &&
           !info.offsetAnimY.has_value() &&
           info.absolute.has_value();
  }

  void update(int count)
  {
    if (info.cc.has_value() && info.c1.has_value() && info.c2.has_value())
    {
      int now = count % static_cast<int>(*info.cc);
      visible = now >= *info.c1 && now <= *info.c2;
    }
    else
    {
      visible = true;
    }
  }
};

LFW_NS_END

#endif
