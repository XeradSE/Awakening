#pragma once

#include "./Entity.hpp"

class Mob : public Entity {
public:
  double max_hp = 50.0;
  double current_hp = max_hp;

  double movement_speed;

  double atk;
};
