#include "../include/BoundsComponent.hpp"
#include "../include/ChaseComponent.hpp"
#include "../include/Entity.hpp"
#include "../include/PlayerInputComponent.hpp"
#include "../include/RectangleRenderComponent.hpp"
#include "../include/TransformComponent.hpp"
#include "raylib.h"

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
  camera.zoom = 2.0f;


  std::vector<std::unique_ptr<Entity>> ennemis;

  float spawn_timer = 0.0f;
  float spawn_interval = 1.0f;
  float spawn_radius =
      450.0f;

  while (!WindowShouldClose()) {

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
    DrawRectangle(0, 0, 1080, 720, GRAY);

    player.Draw();

    for (auto &ennemi : ennemis) {
      ennemi->Draw();
    }

    EndMode2D();

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
