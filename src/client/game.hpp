#pragma once

#include "client.hpp"
#include "env_item.hpp"
#include "player.hpp"
#include "raylib.hpp"
#include <raylib.h>
#include <vector>

class Game {
public:
  Game();
  bool ShouldClose();
  void Update();
  void Draw();
  ~Game();

private:
  Vector2 winSize, otherPos;
  Raylib *raylib;
  Client *client;
  Player *player;
  std::vector<EnvItem> envItems;
  Camera2D camera;

  void HandleResize();
  void Restart();
};
