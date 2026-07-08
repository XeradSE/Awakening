#pragma once

#include "../include/Entity.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "raylib.h"
#include <math.h>

class PlayerInputComponent : public Component {
public:
  float speed;

  PlayerInputComponent(float spd) { speed = spd; }

  void Update(float dt) override {
    TransformComponent *transform = owner->GetComponent<TransformComponent>();
    if (transform == nullptr)
      return;

    float dir_x = 0.0f;
    float dir_y = 0.0f;

    if (IsKeyDown(KEY_RIGHT))
      dir_x += 1.0f;
    if (IsKeyDown(KEY_LEFT))
      dir_x -= 1.0f;
    if (IsKeyDown(KEY_DOWN))
      dir_y += 1.0f;
    if (IsKeyDown(KEY_UP))
      dir_y -= 1.0f;

    float magnitude = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (magnitude > 0.0f) {
      dir_x = dir_x / magnitude;
      dir_y = dir_y / magnitude;
    }


    transform->x += dir_x * speed * dt;
    transform->y += dir_y * speed * dt;
  };
};
