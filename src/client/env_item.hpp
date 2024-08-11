#pragma once

#include <raylib.h>

class EnvItem {
public:
  EnvItem(Rectangle rect, bool blocking, Color color);
  void Resize(Vector2 old, Vector2 neew);
  void Draw();

  Rectangle GetRec();
  bool IsBlocking();

private:
  Rectangle rect;
  bool blocking;
  Color color;
};
