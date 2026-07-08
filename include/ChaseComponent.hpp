#pragma once

#include "./Component.hpp"
#include "./Entity.hpp"
#include "./TransformComponent.hpp"
#include <math.h>

class ChaseComponent : public Component {
public:
  float speed;
  Entity *target;

  ChaseComponent(float spd, Entity *playerTarget) {
    speed = spd;
    target = playerTarget;
  }

  void Update(float dt) override {

    TransformComponent *my_transform =
        owner->GetComponent<TransformComponent>();
    TransformComponent *target_transform =
        target->GetComponent<TransformComponent>();


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
};
