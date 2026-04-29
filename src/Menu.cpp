#include "../include/Menu.hpp"
#include "raylib.h"

bool MAIN_MENU = true;
bool GAME_OVER = false;
bool PAUSE_MENU = false;

void Menu::drawMainMenu() {
  ClearBackground(BLACK);
  int x = MeasureText("Awakening", 100);
  DrawText("Awakening", 450 - x, 100, 100, GOLD);
};

void Menu::drawGameOver() {
  ClearBackground(BLACK);
  int x = MeasureText("GAME OVER", 100);
  DrawText("GAME OVER", 450 - x, 100, 100, GOLD);
};

void Menu::drawPauseMenu() {
  ClearBackground(BLACK);
  int x = MeasureText("Pause Menu", 100);
  DrawText("Pause Menu", 450 - x, 100, 100, GOLD);
};

bool Menu::handleInput() {
  if (PAUSE_MENU == true) {
    if (IsKeyPressed(KEY_ESCAPE)) {
      return true;
    }
    return false;
  }
  if (IsKeyPressed(KEY_ENTER)) {
    return true;
  }
  return false;
}
