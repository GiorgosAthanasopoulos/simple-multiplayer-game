#include "raylib.hpp"
#include "config.hpp"
#include <raylib.h>

Raylib::Raylib() {
  SetConfigFlags(WIN_FLAGS);
  InitWindow(WIN_W, WIN_H, WIN_TITLE);
  SetTargetFPS(WIN_FPS);
  SetExitKey(KEY_EXIT);
  SetWindowMinSize(WIN_MIN_W, WIN_MIN_H);
  SetWindowMaxSize(WIN_MAX_W, WIN_MAX_H);
  InitAudioDevice();
}

void Raylib::Draw() {
  if (DEBUG) {
    DrawFPS(0, 0);
  }
}

Raylib::~Raylib() {
  CloseAudioDevice();
  CloseWindow();
}
