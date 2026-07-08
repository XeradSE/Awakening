// Pour le déplacement

#pragma once

#include "Component.hpp"

class TransformComponent : public Component {
public:
  float x;
  float y;

  TransformComponent(float start_x, float start_y) {
    x = start_x;
    y = start_y;
  };
};
