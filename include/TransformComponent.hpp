#pragma once

#include "Component.hpp"

class TransformComponent : public Component {
public:
  float x;
  float y;

  TransformComponent(float start_x, float start_y);
};
