#pragma once

#include "Component.hpp"

class PlayerInputComponent : public Component {
public:
  float speed;

  PlayerInputComponent(float spd);

  void Update(float dt) override;
};
