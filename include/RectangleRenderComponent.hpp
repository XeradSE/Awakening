#pragma once

#include "Component.hpp"
#include "raylib.h"

class RectangleRenderComponent : public Component {
public:
  float width;
  float height;
  Color color;

  RectangleRenderComponent(float w, float h, Color c);

  void Draw() override;
};
