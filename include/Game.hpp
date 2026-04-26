#pragma once

#include "Menu.hpp"
#include "Player.hpp"
#include "raylib.h"
#include <fstream>
#include <random>

enum SPRITE { GROUND = '#' };

static const int CELL_SIZE = 10;
static const int MAP_WIDTH = 600;
static const int MAP_HEIGHT = 600;

class Game {
  int nb_cell_width = 0;
  int nb_cell_height = 0;
  int screen_width = 0;
  int screen_height = 0;
  Menu menu;
  std::mt19937 rng{std::random_device{}()};
  Player player;
  double camera_x = 0.0;
  double camera_y = 0.0;

public:
  Game(int w, int h);

  void drawMap();
  void update();
};
