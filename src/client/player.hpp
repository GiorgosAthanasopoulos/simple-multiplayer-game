#pragma once

#include "env_item.hpp"
#include <raylib.h>
#include <vector>

class Player {
public:
  Player();
  void Resize(Vector2 old, Vector2 neew);
  void Update(std::vector<EnvItem> envItems);
  void Draw();

  void Reset();
  Vector2 GetPos();
  Vector2 GetSize();

private:
  Vector2 pos, size, speed;
  bool canJump = false;
  float speedY;
};
