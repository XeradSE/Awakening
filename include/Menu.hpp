#pragma once

extern bool MAIN_MENU;
extern bool GAME_OVER;
extern bool PAUSE_MENU;

class Menu {
public:
  void drawMainMenu();
  void drawGameOver();
  void drawPauseMenu();

  bool handleInput();
};
