#include "../include/RectangleRenderComponent.hpp"
#include "../include/Entity.hpp"
#include "../include/TransformComponent.hpp"
#include "raylib.h"

RectangleRenderComponent::RectangleRenderComponent(float w, float h, Color c) {
  width = w;
  height = h;
  color = c;
}

void RectangleRenderComponent::Draw() {
  TransformComponent *transform = owner->GetComponent<TransformComponent>();

  if (transform != nullptr) {
    DrawRectangle((int)(transform->x - width / 2),
                  (int)(transform->y - height / 2), (int)width, (int)height,
                  color);
  }
}
