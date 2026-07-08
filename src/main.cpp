#include "../include/BoundsComponent.hpp"
#include "../include/Entity.hpp"
#include "../include/Game.hpp"
#include "../include/PlayerInputComponent.hpp"
#include "../include/RectangleRenderComponent.hpp"
#include "../include/TransformComponent.hpp"
#include "raylib.h"
#include <functional>

int main() {

  const int screenWidth = 1080;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Awakening");
  SetTargetFPS(100);

  // Game game(screenWidth, screenHeight);

  Entity player;
  player.AddComponent<TransformComponent>(540.0f, 360.0f);
  player.AddComponent<RectangleRenderComponent>(10.0f, 10.0f, RED);
  player.AddComponent<PlayerInputComponent>(100.0f);
  player.AddComponent<BoundsComponent>(0.0f, 1080.0f, 0.0f, 720.0f);

  // On prépare la caméra
  Camera2D camera = {0};
  // L'offset, c'est l'endroit de l'écran où on veut placer la cible.
  // On veut le joueur au milieu, donc on prend la moitié de la fenêtre (600/2 =
  // 300)
  camera.offset = {540.0f, 360.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f; // Tu peux mettre 2.0f si tu veux zoomer !

  while (!WindowShouldClose()) {

    float dt = GetFrameTime();
    player.Update(dt);

    TransformComponent *p_pos = player.GetComponent<TransformComponent>();
    if (p_pos != nullptr) {
      camera.target = {p_pos->x, p_pos->y};
    }

    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(camera);
    DrawRectangle(0, 0, 1080, 720, GRAY);

    player.Draw();

    EndMode2D();

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
