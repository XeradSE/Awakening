#pragma once

#include "../include/Component.hpp"
#include "../include/Entity.hpp"
#include "../include/TransformComponent.hpp"
#include <algorithm>

class BoundsComponent : public Component {
public:
  float min_x, max_x;
  float min_y, max_y;


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


    transform->x = std::clamp(transform->x, min_x, max_x);
    transform->y = std::clamp(transform->y, min_y, max_y);
  }
};
