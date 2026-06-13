#pragma once

#include "Mob.hpp"

class Player : public Mob {
  float hp_regen_per_s = 0.0f;
  float life_orb_hp_recovery = 50.0f;

  float damage_reduction = 1.0f;
  float evasion_chance = 0.0f;

  float amplify_atk = 1.0f;
  float all_magic_damage = 1.0f;

  float all_magic_size = 1.0f;
  float all_magic_duration = 1.0f;
  float all_magic_cooldown_reduction = 1.0f;

  float critical_rate = 5.0f;
  float critical_damage = 50.0f;

  float mana_acquisition = 1.0f;
  float item_pickup_range = 1.0f;

  float required_exp = 100.0f;
  float current_exp = 0.0f;

public:
  Player(int map_h, int map_w);
};
