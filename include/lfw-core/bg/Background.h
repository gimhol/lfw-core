#ifndef LFW_CORE_BG_BACKGROUND_H
#define LFW_CORE_BG_BACKGROUND_H

#include <string>
#include <vector>

#include "lfw-core/bg/Layer.h"
#include "lfw-core/core.hpp"
#include "lfw-core/defines/IBgData.hpp"

LFW_NS_BEGIN

class World;

/**
 * 背景 — 对应 TS Background
 */
class Background
{
public:
  const IBgData &data;
  const double width;
  const double depth;
  const struct
  {
    double x;
    double z;
  } middle;

  double zoom_x = 1;
  double zoom_y = 1;
  double zoom_z = 1;

  Background(World &world, const IBgData &data_ref);

  const std::string &name() const { return data.base.name; }
  const std::string &id() const { return data.id; }
  double left() const { return data.base.left; }
  double right() const { return data.base.right; }
  double near() const { return data.base.near; }
  double far() const { return data.base.far; }
  const std::vector<Layer> &layers() const { return _layers; }

  World &world() const { return *_world; }

  void update();
  void dispose();

private:
  void add_layer(const IBgLayerInfo &info);

  World *_world;
  std::vector<Layer> _layers;
  int _update_times = 0;
};

LFW_NS_END

#endif
