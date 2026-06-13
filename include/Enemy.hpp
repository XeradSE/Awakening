#pragma once

#include "Mob.hpp"

class Enemy : public Mob {
  float enemy_map_hp_reduction = 1.0f;

public:
  Enemy() { movement_speed = 50.0f; };

  void updatePosition(float player_x, float player_y, float delta_time);
  void drawEnemy(float camera_x, float camera_y);
};
