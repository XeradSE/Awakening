#pragma once

#include "./Entity.hpp"

class Mob : public Entity {
public:
  double max_hp;
  double current_hp = max_hp;

  double movement_speed = 100.0;

  double atk;
};
