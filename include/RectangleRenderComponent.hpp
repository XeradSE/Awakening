

#pragma once

#include "../include/Entity.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "raylib.h"

class RectangleRenderComponent : public Component {
public:
  float width;
  float height;
  Color color;

  RectangleRenderComponent(float w, float h, Color c) {
    width = w;
    height = h;
    color = c;
  };

  void Draw() override {
    TransformComponent *transform = owner->GetComponent<TransformComponent>();

    if (transform != nullptr) {
      DrawRectangle((int)(transform->x - width / 2),
                    (int)(transform->y - height / 2), (int)width, (int)height,
                    color);
    }
  };
};
