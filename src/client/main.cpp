#include "game.hpp"
int main() {
  Game g;

  while (!g.ShouldClose()) {
    g.Update();
    g.Draw();
  }
}
