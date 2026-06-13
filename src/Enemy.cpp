#include "../include/Enemy.hpp"
#include "../include/Constants.hpp"
#include "raylib.h"
#include <cmath>

void Enemy::updatePosition(float player_x, float player_y, float delta_time) {
  float dx = player_x - pos_x;
  float dy = player_y - pos_y;
  float distance = std::sqrt(dx * dx + dy * dy);

  if (distance > 0) {
    float move_step = movement_speed * delta_time;

    // Si la distance restante est plus petite que notre pas de mouvement,
    // on le colle direct sur le joueur pour éviter qu'il ne le traverse.
    if (distance <= move_step) {
      pos_x = player_x;
      pos_y = player_y;
    } else {
      // Sinon, on applique la logique de normalisation
      pos_x += (dx / distance) * move_step;
      pos_y += (dy / distance) * move_step;
    }
  }
};

void Enemy::drawEnemy(float camera_x, float camera_y) {
  int screen_x = (int)(pos_x * CELL_SIZE - camera_x);
  int screen_y = (int)(pos_y * CELL_SIZE - camera_y);

  DrawRectangle(screen_x, screen_y, CELL_SIZE, CELL_SIZE, ORANGE);
};
