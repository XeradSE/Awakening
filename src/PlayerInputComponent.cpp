#include "../include/PlayerInputComponent.hpp"
#include "../include/Entity.hpp"
#include "../include/TransformComponent.hpp"
#include "raylib.h"
#include <cmath>

PlayerInputComponent::PlayerInputComponent(float spd) {
  speed = spd;
}

void PlayerInputComponent::Update(float dt) {
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

  float magnitude = std::sqrt(dir_x * dir_x + dir_y * dir_y);
  if (magnitude > 0.0f) {
    dir_x = dir_x / magnitude;
    dir_y = dir_y / magnitude;
  }

  transform->x += dir_x * speed * dt;
  transform->y += dir_y * speed * dt;
}
