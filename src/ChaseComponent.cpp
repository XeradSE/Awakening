#include "../include/ChaseComponent.hpp"
#include "../include/Entity.hpp"
#include "../include/TransformComponent.hpp"
#include <cmath>

ChaseComponent::ChaseComponent(float spd, Entity *playerTarget) {
  speed = spd;
  target = playerTarget;
}

void ChaseComponent::Update(float dt) {
  TransformComponent *my_transform = owner->GetComponent<TransformComponent>();
  TransformComponent *target_transform = target->GetComponent<TransformComponent>();

  if (my_transform == nullptr || target_transform == nullptr)
    return;

  float dx = target_transform->x - my_transform->x;
  float dy = target_transform->y - my_transform->y;
  float distance = std::sqrt(dx * dx + dy * dy);

  if (distance > 0.0f) {
    float move_step = speed * dt;

    if (distance <= move_step) {
      my_transform->x = target_transform->x;
      my_transform->y = target_transform->y;
    } else {
      my_transform->x += (dx / distance) * move_step;
      my_transform->y += (dy / distance) * move_step;
    }
  }
}
