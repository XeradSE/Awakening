#include "../include/BoundsComponent.hpp"
#include "../include/Entity.hpp"
#include "../include/TransformComponent.hpp"
#include <algorithm>

BoundsComponent::BoundsComponent(float minX, float maxX, float minY, float maxY) {
  min_x = minX;
  max_x = maxX;
  min_y = minY;
  max_y = maxY;
}

void BoundsComponent::Update(float dt) {
  TransformComponent *transform = owner->GetComponent<TransformComponent>();
  if (transform == nullptr)
    return;

  transform->x = std::clamp(transform->x, min_x, max_x);
  transform->y = std::clamp(transform->y, min_y, max_y);
}
