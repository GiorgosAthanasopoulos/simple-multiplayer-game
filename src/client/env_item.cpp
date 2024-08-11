#include "env_item.hpp"
#include "util.hpp"
#include <raylib.h>

EnvItem::EnvItem(Rectangle rect, bool blocking, Color color) {
  this->rect = rect;
  this->blocking = blocking;
  this->color = color;
}

void EnvItem::Resize(Vector2 old, Vector2 neew) {
  Vector2 pos = MaintainPosAfterResize(old, neew, {rect.x, rect.y});
  rect.x = pos.x;
  rect.y = pos.y;
  rect.width = rect.width / old.x * neew.x;
  rect.height = rect.height / old.y * neew.y;
}

void EnvItem::Draw() { DrawRectangleRec(rect, color); }

Rectangle EnvItem::GetRec() { return rect; }

bool EnvItem::IsBlocking() { return blocking; }
