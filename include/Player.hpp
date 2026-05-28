#pragma once

#include "Mob.hpp"

class Player : public Mob {
  double hp_regen_per_s = 0.0;
  double life_orb_hp_recovery = 50;

  double damage_reduction = 1.0;
  double evasion_chance = 0.0;

  double amplify_atk = 1.0;
  double all_magic_damage = 1.0;

  double all_magic_size = 1.0;
  double all_magic_duration = 1.0;
  double all_magic_cooldown_reduction = 1.0;

  double critical_rate = 5.0;
  double critical_damage = 50;

  double mana_acquisition = 1.0;
  double item_pickup_range = 1.0;

  double required_exp = 100.0;
  double current_exp = 0.0;

public:
  Player(int map_h, int map_w);
};
