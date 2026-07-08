#pragma once

#include "../include/Component.hpp"

class BoundsComponent : public Component {
public:
  float min_x, max_x;
  float min_y, max_y;

  BoundsComponent(float minX, float maxX, float minY, float maxY);

  void Update(float dt) override;
};
