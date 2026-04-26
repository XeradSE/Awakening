#include "../include/Game.hpp"
#include <iostream>

int main() {

  const int screenWidth = 1080;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Awakening");
  SetTargetFPS(120);

  std::cout << "Hello World!" << std::endl;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
