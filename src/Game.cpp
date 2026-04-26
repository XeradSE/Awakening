#include "../include/Game.hpp"
#include "raylib.h"
#include <algorithm>
#include <stdexcept>

Game::Game(int w, int h) {
  screen_width = w;
  screen_height = h;
  nb_cell_width = screen_width / CELL_SIZE;
  nb_cell_height = screen_height / CELL_SIZE;
  player(MAP_WIDTH, MAP_HEIGHT);
  camera_x = player.pos_x * nb_cell_width - (double)screen_width / 2;
  camera_y = player.pos_y * nb_cell_height - (double)screen_height / 2;
  camera_x = std::clamp(camera_x, 0, MAP_WIDTH * nb_cell_width - screen_width);
  camera_y =
      std::clamp(camera_y, 0, MAP_HEIGHT * nb_cell_height - screen_width);
};

void Game::drawMap() {
  std::ifstream map("../data/map.txt");
  if (!map.is_open())
    throw std::runtime_error("Erreur lors de la lecture de la map!");
};

void Game::update() {
  if (IsKeyPressed(KEY_RIGHT)) {
    player.pos_x += player.speed * deltatime;
  } else if (IsKeyPressed(KEY_LEFT)) {
    player.pos_x -= player.speed * deltatime;
  } else if (IsKeyPressed(KEY_DOWN)) {
    player.pos_y += player.speed * deltatime;
  } else if (IsKeyPressed(KEY_UP)) {
    player.pos_y -= player.speed * deltatime;
  }

  player.pos_x = std::clamp(player.pos_x, 0, MAP_WIDTH - 1);
  player.pos_y = std::clamp(player.pos_y, 0, MAP_HEIGHT - 1);

  camera_x = player.pos_x * nb_cell_width - (double)screen_width / 2;
  camera_y = player.pos_y * nb_cell_height - (double)screen_height / 2;
  camera_x = std::clamp(camera_x, 0, MAP_WIDTH * nb_cell_width - screen_width);
  camera_y =
      std::clamp(camera_y, 0, MAP_HEIGHT * nb_cell_height - screen_width);
};
