#include "../include/Player.hpp"

Player::Player(int map_w, int map_h) {
  pos_x = (float)map_w / 2;
  pos_y = (float)map_h / 2;
  movement_speed = 100.0f;
};
