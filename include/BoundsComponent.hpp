#pragma once

#include "../include/Component.hpp"
#include "../include/Entity.hpp"
#include "../include/TransformComponent.hpp"
#include <algorithm> // Pour std::clamp

class BoundsComponent : public Component {
public:
  float min_x, max_x;
  float min_y, max_y;

  // On définit les limites de notre carte (ex: 0 à 600)
  BoundsComponent(float minX, float maxX, float minY, float maxY) {
    min_x = minX;
    max_x = maxX;
    min_y = minY;
    max_y = maxY;
  }

  void Update(float dt) override {
    TransformComponent *transform = owner->GetComponent<TransformComponent>();
    if (transform == nullptr)
      return;

    // std::clamp bloque la valeur entre le min et le max
    transform->x = std::clamp(transform->x, min_x, max_x);
    transform->y = std::clamp(transform->y, min_y, max_y);
  }
};
