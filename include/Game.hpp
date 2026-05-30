#pragma once

#include "Enemy.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include <random>
#include <vector>

enum SPRITE { GROUND = '#' };

static std::vector<std::string> map_cache;
static bool map_loaded = false;

class Game {
  int nb_cell_width = 0;
  int nb_cell_height = 0;
  int screen_width = 0;
  int screen_height = 0;
  Menu menu;
  std::mt19937 rng{std::random_device{}()};
  Player player;
  std::vector<Enemy> enemies;
  double camera_x = 0.0;
  double camera_y = 0.0;
  int nb_enemies_killed = 0;
  double timer = 0.0;

public:
  Game(int w, int h);

  void loadMap();
  void drawMap();
  void update();

  Menu &getMenu() { return menu; };
};
