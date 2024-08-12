#include "game.hpp"
#include "config.hpp"
#include "raylib.hpp"
#include "util.hpp"
#include <cstddef>
#include <optional>
#include <raylib.h>
#include <sstream>

Game::Game() {
  client = new Client;
  raylib = new Raylib;
  player = new Player;
  winSize = GetWindowSize();
  camera.target = player->GetPos();
  camera.offset = GetWindowSize() / 2;
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
  otherPos = {PLAYER_START_X, PLAYER_START_Y};

  Restart();
}

bool Game::ShouldClose() { return WindowShouldClose(); }

void Game::Update() {
  HandleResize();
  if (IsKeyPressed(KEY_RESTART)) {
    Restart();
  }

  std::optional<Vector2> v = client->Update();
  if (v.has_value()) {
    otherPos = v.value();
  }
  player->Update(envItems);
  camera.offset = GetWindowSize() / 2;
  camera.target = player->GetPos();

  std::ostringstream ss;
  ss << "pos;" << player->GetPos().x << ";" << player->GetPos().y;
  client->SendStr(ss.str());
}

void Game::Draw() {
  BeginDrawing();
  ClearBackground(WIN_BG);

  BeginMode2D(camera);
  for (size_t i = 0; i < envItems.size(); ++i) {
    envItems[i].Draw();
  }
  player->Draw();
  Vector2 size = player->GetSize();
  DrawRectangleV({otherPos.x - size.x / 2, otherPos.y - size.y}, size,
                 PLAYER_2_COLOR);
  EndMode2D();
  raylib->Draw();

  EndDrawing();
}

Game::~Game() {
  delete player;
  delete raylib;
  delete client;
}

void Game::HandleResize() {
  if (IsWindowResized()) {
    Vector2 neew = GetWindowSize();

    player->Resize(winSize, neew);
    for (size_t i = 0; i < envItems.size(); ++i) {
      envItems[i].Resize(winSize, neew);
    }

    winSize = neew;
  }
}

void Game::Restart() {
  player->Reset();
  envItems.clear();
  envItems.push_back(EnvItem({0, 0, 1000, 400}, false, LIGHTGRAY));
  envItems.push_back(EnvItem({0, 400, 1000, 200}, true, GRAY));
  envItems.push_back(EnvItem({300, 200, 400, 10}, true, GRAY));
  envItems.push_back(EnvItem({250, 300, 100, 10}, true, GRAY));
  envItems.push_back(EnvItem({650, 300, 100, 10}, true, GRAY));
}
