#include "lfw-core/bg/Background.h"

LFW_NS_BEGIN

Background::Background(World &world_ref, const IBgData &data_ref)
    : data(data_ref),
      width(data.base.right - data.base.left),
      depth(data.base.near - data.base.far),
      middle{(data.base.right + data.base.left) / 2,
             (data.base.far + data.base.near) / 2},
      _world(&world_ref)
{
  for (const auto &info : data.layers)
    add_layer(info);

  if (data.base.zoom_x.has_value())
    zoom_x = *data.base.zoom_x;
  if (data.base.zoom_y.has_value())
    zoom_y = *data.base.zoom_y;
  if (data.base.zoom_z.has_value())
    zoom_z = *data.base.zoom_z;
}

void Background::add_layer(const IBgLayerInfo &info)
{
  double x = info.x;
  double loop = info.loop.value_or(0);

  if (loop <= 0)
  {
    _layers.emplace_back(*this, info);
    return;
  }

  double right_edge = width + loop;
  for (x -= loop; x < right_edge; x += loop)
  {
    IBgLayerInfo copy = info;
    copy.x = x;
    _layers.emplace_back(*this, copy);
  }
}

void Background::update()
{
  ++_update_times;
  for (auto &layer : _layers)
    layer.update(_update_times);
}

void Background::dispose()
{
  _layers.clear();
}

LFW_NS_END
