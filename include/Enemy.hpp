#pragma once

#include "Mob.hpp"

class Enemy : public Mob {
  double enemy_map_hp_reduction = 1.0;

public:
  Enemy() { movement_speed = 75.0; };

  void updatePosition(double player_x, double player_y, float delta_time);
  void drawEnemy(double camera_x, double camera_y);
};
