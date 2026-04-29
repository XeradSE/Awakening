#include "../include/Game.hpp"
#include "raylib.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>

Game::Game(int w, int h)
    : nb_cell_width(w / CELL_SIZE), nb_cell_height(h / CELL_SIZE),
      screen_width(w), screen_height(h), player(MAP_HEIGHT, MAP_WIDTH) {

  camera_x = player.pos_x * CELL_SIZE - (double)screen_width / 2;
  camera_y = player.pos_y * CELL_SIZE - (double)screen_height / 2;
  camera_x =
      std::clamp(camera_x, 0.0, (double)(MAP_WIDTH * CELL_SIZE - screen_width));
  camera_y = std::clamp(camera_y, 0.0,
                        (double)(MAP_HEIGHT * CELL_SIZE - screen_height));
}

void Game::loadMap() {
  if (map_loaded)
    return;

  std::ifstream map_file("../data/map.txt");
  if (!map_file.is_open())
    throw std::runtime_error("Erreur lors de la lecture de la map!");

  std::string line;
  while (std::getline(map_file, line)) {
    map_cache.push_back(line);
  }
  map_file.close();
  map_loaded = true;
}

void Game::drawMap() {
  loadMap();

  ClearBackground(BLACK);

  int start_x = (int)(camera_x / CELL_SIZE);
  int start_y = (int)(camera_y / CELL_SIZE);
  int end_x = start_x + (screen_width / CELL_SIZE) + 1;
  int end_y = start_y + (screen_height / CELL_SIZE) + 1;

  start_x = std::max(0, start_x);
  start_y = std::max(0, start_y);
  end_x = std::min(MAP_WIDTH, end_x);
  end_y = std::min(MAP_HEIGHT, end_y);

  for (int y = start_y; y < end_y; y++) {
    if (y >= (int)map_cache.size())
      break;

    for (int x = start_x; x < end_x; x++) {
      if (x >= (int)map_cache[y].size())
        break;

      char tile = map_cache[y][x];

      int screen_x = (int)(x * CELL_SIZE - camera_x);
      int screen_y = (int)(y * CELL_SIZE - camera_y);

      if (tile == GROUND) {
        DrawRectangle(screen_x, screen_y, CELL_SIZE, CELL_SIZE, DARKGRAY);
        DrawRectangleLines(screen_x, screen_y, CELL_SIZE, CELL_SIZE, GRAY);
      } else {
        DrawRectangle(screen_x, screen_y, CELL_SIZE, CELL_SIZE, BLACK);
        DrawRectangleLines(screen_x, screen_y, CELL_SIZE, CELL_SIZE, DARKGRAY);
      }
    }
  }

  int player_screen_x = (int)(player.pos_x * CELL_SIZE - camera_x);
  int player_screen_y = (int)(player.pos_y * CELL_SIZE - camera_y);
  DrawRectangle(player_screen_x, player_screen_y, CELL_SIZE, CELL_SIZE, RED);

  DrawFPS(10, 10);
}

void Game::update() {
  float deltatime = GetFrameTime();

  if (IsKeyDown(KEY_RIGHT)) {
    player.pos_x += player.movement_speed * deltatime;
  } else if (IsKeyDown(KEY_LEFT)) {
    player.pos_x -= player.movement_speed * deltatime;
  } else if (IsKeyDown(KEY_DOWN)) {
    player.pos_y += player.movement_speed * deltatime;
  } else if (IsKeyDown(KEY_UP)) {
    player.pos_y -= player.movement_speed * deltatime;
  } else if (IsKeyPressed(KEY_ESCAPE)) {
    PAUSE_MENU = true;
  }

  player.pos_x = std::clamp(player.pos_x, 0.0, (double)(MAP_WIDTH - 1));
  player.pos_y = std::clamp(player.pos_y, 0.0, (double)(MAP_HEIGHT - 1));

  camera_x = player.pos_x * CELL_SIZE - (double)screen_width / 2;
  camera_y = player.pos_y * CELL_SIZE - (double)screen_height / 2;

  camera_x =
      std::clamp(camera_x, 0.0, (double)(MAP_WIDTH * CELL_SIZE - screen_width));
  camera_y = std::clamp(camera_y, 0.0,
                        (double)(MAP_HEIGHT * CELL_SIZE - screen_height));
};
