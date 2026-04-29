#include "../include/Game.hpp"
#include "raylib.h"

int main() {

  const int screenWidth = 1080;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Awakening");
  SetTargetFPS(120);

  Game game(screenWidth, screenHeight);

  while (!WindowShouldClose()) {
    SetExitKey(KEY_NULL);

    BeginDrawing();

    if (MAIN_MENU == true) {
      game.getMenu().drawMainMenu();
      if (game.getMenu().handleInput()) {
        MAIN_MENU = false;
      }
    } else if (GAME_OVER == true) {
      game.getMenu().drawGameOver();
      if (game.getMenu().handleInput()) {
        GAME_OVER = false;
      }
    } else if (PAUSE_MENU == true) {
      game.getMenu().drawPauseMenu();
      if (game.getMenu().handleInput()) {
        PAUSE_MENU = false;
      }
    } else {
      game.update();
      game.drawMap();
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
