#include "../include/BoundsComponent.hpp"
#include "../include/ChaseComponent.hpp"
#include "../include/Constants.hpp"
#include "../include/Entity.hpp"
#include "../include/Menu.hpp"
#include "../include/PlayerInputComponent.hpp"
#include "../include/RectangleRenderComponent.hpp"
#include "../include/TransformComponent.hpp"
#include "raylib.h"
#include <algorithm>
#include <fstream>
#include <math.h>
#include <stdexcept>
#include <string>

enum SPRITE { GROUND = '#' };

static std::vector<std::string> map_cache;
static bool map_loaded = false;

void loadMap() {
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

void drawMap(Camera2D camera, int s_w, int s_h) {
  loadMap();

  ClearBackground(BLACK);

  int start_x = (int)(camera.offset.x / CELL_SIZE);
  int start_y = (int)(camera.offset.y / CELL_SIZE);
  int end_x = start_x + (s_w / CELL_SIZE) + 1;
  int end_y = start_y + (s_h / CELL_SIZE) + 1;

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

      int screen_x = (int)(x * CELL_SIZE - camera.offset.x);
      int screen_y = (int)(y * CELL_SIZE - camera.offset.y);

      if (tile == GROUND) {
        DrawRectangle(screen_x, screen_y, CELL_SIZE, CELL_SIZE, DARKGRAY);
        DrawRectangleLines(screen_x, screen_y, CELL_SIZE, CELL_SIZE, GRAY);
      } else {
        DrawRectangle(screen_x, screen_y, CELL_SIZE, CELL_SIZE, BLACK);
        DrawRectangleLines(screen_x, screen_y, CELL_SIZE, CELL_SIZE, DARKGRAY);
      }
    }
  }
}

int main() {

  const int screenWidth = 1080;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Awakening");
  SetTargetFPS(100);

  Entity player;
  player.AddComponent<TransformComponent>(540.0f, 360.0f);
  player.AddComponent<RectangleRenderComponent>(10.0f, 10.0f, RED);
  player.AddComponent<PlayerInputComponent>(100.0f);
  player.AddComponent<BoundsComponent>(0.0f, 1080.0f, 0.0f, 720.0f);

  Camera2D camera = {0};

  camera.offset = {540.0f, 360.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  std::vector<std::unique_ptr<Entity>> ennemis;

  float spawn_timer = 0.0f;
  float spawn_interval = 1.0f;
  float spawn_radius = 450.0f;

  Menu menu;

  while (!WindowShouldClose()) {
    SetExitKey(KEY_NULL);

    if (MAIN_MENU == true) {
      menu.drawMainMenu();
      if (menu.handleInput()) {
        MAIN_MENU = false;
      }
    } else if (GAME_OVER == true) {
      menu.drawGameOver();
      if (menu.handleInput()) {
        GAME_OVER = false;
      }
    } else if (PAUSE_MENU == true) {
      menu.drawPauseMenu();
      if (menu.handleInput()) {
        PAUSE_MENU = false;
      }
    } else {

      if (IsKeyPressed(KEY_ESCAPE)) {
        PAUSE_MENU = true;
      }

      float dt = GetFrameTime();
      player.Update(dt);

      for (auto &ennemi : ennemis) {
        ennemi->Update(dt);
      }

      spawn_timer += dt;

      if (spawn_timer >= spawn_interval) {

        spawn_timer -= spawn_interval;

        TransformComponent *p_pos = player.GetComponent<TransformComponent>();

        if (p_pos != nullptr) {

          float angle = GetRandomValue(0, 360) * (PI / 180.0f);

          float spawn_x = p_pos->x + cos(angle) * spawn_radius;
          float spawn_y = p_pos->y + sin(angle) * spawn_radius;

          spawn_x = std::clamp(spawn_x, 0.0f, 1080.0f);
          spawn_y = std::clamp(spawn_y, 0.0f, 720.0f);

          auto nouvel_ennemi = std::make_unique<Entity>();
          nouvel_ennemi->AddComponent<TransformComponent>(spawn_x, spawn_y);
          nouvel_ennemi->AddComponent<RectangleRenderComponent>(10.0f, 10.0f,
                                                                ORANGE);

          float random_speed = (float)GetRandomValue(60, 90);
          nouvel_ennemi->AddComponent<ChaseComponent>(random_speed, &player);

          ennemis.push_back(std::move(nouvel_ennemi));
        }
      }

      TransformComponent *p_pos = player.GetComponent<TransformComponent>();
      if (p_pos != nullptr) {
        camera.target = {p_pos->x, p_pos->y};
      }

      BeginDrawing();
      ClearBackground(BLACK);

      BeginMode2D(camera);

      drawMap(camera, screenWidth, screenHeight);

      player.Draw();

      for (auto &ennemi : ennemis) {
        ennemi->Draw();
      }

      EndMode2D();
    }

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
