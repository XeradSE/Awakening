#include "../include/Game.hpp"
#include "../include/Constants.hpp"
#include "raylib.h"
#include <algorithm>
#include <fstream>
#include <math.h>
#include <random>
#include <stdexcept>
#include <string>

Game::Game(int w, int h)
    : nb_cell_width(w / CELL_SIZE), nb_cell_height(h / CELL_SIZE),
      screen_width(w), screen_height(h), player(MAP_HEIGHT, MAP_WIDTH) {

  camera_x = player.pos_x * CELL_SIZE - (float)screen_width / 2;
  camera_y = player.pos_y * CELL_SIZE - (float)screen_height / 2;
  camera_x =
      std::clamp(camera_x, 0.0f, (float)(MAP_WIDTH * CELL_SIZE - screen_width));
  camera_y = std::clamp(camera_y, 0.0f,
                        (float)(MAP_HEIGHT * CELL_SIZE - screen_height));

  Enemy test_enemy;
  test_enemy.pos_x = 10.0f;
  test_enemy.pos_y = 10.0f;
  enemies.push_back(test_enemy);
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

  for (auto &enemy : enemies) {
    enemy.drawEnemy(camera_x, camera_y);
  }

  DrawFPS(10, 10);
  DrawText(std::to_string(player.pos_x).c_str(), 200, 10, 10, GREEN);
  DrawText(std::to_string(player.pos_y).c_str(), 300, 10, 10, GREEN);
}

void Game::update() {

  float deltatime = GetFrameTime();

  // 1. On stocke UNIQUEMENT la direction voulue (valeurs entre -1 et 1)
  float dir_x = 0.0f;
  float dir_y = 0.0f;

  if (IsKeyDown(KEY_RIGHT))
    dir_x += 1.0f;
  if (IsKeyDown(KEY_LEFT))
    dir_x -= 1.0f;
  if (IsKeyDown(KEY_DOWN))
    dir_y += 1.0f;
  if (IsKeyDown(KEY_UP))
    dir_y -= 1.0f;

  // 2. On calcule la magnitude (la longueur du vecteur de direction)
  float magnitude = sqrt(dir_x * dir_x + dir_y * dir_y);

  // 3. On normalise SEULEMENT si le joueur bouge (pour éviter la division par
  // zéro)
  if (magnitude > 0.0f) {
    dir_x = dir_x / magnitude;
    dir_y = dir_y / magnitude;
  }

  // 4. On applique la vitesse et le temps au résultat normalisé
  player.pos_x += dir_x * player.movement_speed * deltatime;
  player.pos_y += dir_y * player.movement_speed * deltatime;

  /*
   * #include <raymath.h>. Il contient des fonctions toutes faites comme
   * Vector2Normalize() qui font exactement ces étapes sous le capot si tu
   * utilises le type Vector2 pour ta position et ta direction
   */

  if (IsKeyPressed(KEY_ESCAPE)) {
    PAUSE_MENU = true;
  }

  player.pos_x = std::clamp(player.pos_x, 0.0f, (float)(MAP_WIDTH - 1));
  player.pos_y = std::clamp(player.pos_y, 0.0f, (float)(MAP_HEIGHT - 1));

  camera_x = player.pos_x * CELL_SIZE - (float)screen_width / 2;
  camera_y = player.pos_y * CELL_SIZE - (float)screen_height / 2;

  camera_x =
      std::clamp(camera_x, 0.0f, (float)(MAP_WIDTH * CELL_SIZE - screen_width));
  camera_y = std::clamp(camera_y, 0.0f,
                        (float)(MAP_HEIGHT * CELL_SIZE - screen_height));

  for (auto &enemy : enemies) {
    enemy.updatePosition(player.pos_x, player.pos_y, deltatime);
  }

  float spawn_rate = 0.16;
  timer += GetFrameTime();

  if (timer >= spawn_rate) {
    timer = 0;
    std::uniform_int_distribution<> dist_x(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<> dist_y(0, MAP_HEIGHT - 1);

    Enemy test_enemy;
    test_enemy.pos_x = dist_x(rng);
    test_enemy.pos_y = dist_y(rng);
    enemies.push_back(test_enemy);
  }
};
