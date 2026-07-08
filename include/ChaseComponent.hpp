#pragma once

#include "./Component.hpp"

class Entity;

class ChaseComponent : public Component {
public:
  float speed;
  Entity *target;

  ChaseComponent(float spd, Entity *playerTarget);

  void Update(float dt) override;
};
