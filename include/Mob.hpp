#pragma once

#include "./Entity.hpp"

class Mob : public Entity {
public:
  float max_hp = 50.0f;
  float current_hp = max_hp;

  float movement_speed;

  float atk;
};
