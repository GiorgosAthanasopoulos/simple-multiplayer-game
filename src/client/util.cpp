#include "util.hpp"
#include <raylib.h>

Vector2 GetWindowSize() {
  return {(float)GetRenderWidth(), (float)GetRenderHeight()};
}

Vector2 AssertTextFitsInViewport(const char *text, float fontSize,
                                 Vector2 maxSize) {
  float textW = MeasureText(text, fontSize);

  while (textW > maxSize.x || fontSize > maxSize.y) {
    fontSize--;
    textW = MeasureText(text, fontSize);
  }

  return {textW, fontSize};
}

Vector2 operator/(Vector2 a, float b) {
  if (b == 0) {
    return {0, 0};
  }
  return {a.x / b, a.y / b};
}
Vector2 operator*(Vector2 a, float b) { return {a.x * b, a.y * b}; }
Vector2 operator/(Vector2 a, Vector2 b) {
  return {b.x != 0 ? a.x / b.x : 0, b.y != 0 ? a.y / b.y : 0};
}
Vector2 operator*(Vector2 a, Vector2 b) { return {a.x * b.x, a.y * b.y}; }
void operator+=(Vector2 &a, Vector2 b) {
  a.x += b.x;
  a.y += b.y;
}

bool MouseHovered(Rectangle rect) {
  Vector2 mousePos = GetMousePosition();
  return mousePos.x >= rect.x && mousePos.x <= rect.x + rect.width &&
         mousePos.y >= rect.y && mousePos.y <= rect.y + rect.height;
}

Vector2 CalculateSize(Vector2 sizeToWinSizeRatioAxis) {
  return GetWindowSize() / sizeToWinSizeRatioAxis;
}
Vector2 CalculateSpeed(Vector2 speedToWinSizeRatioAxis) {
  return GetWindowSize() / speedToWinSizeRatioAxis;
}
Vector2 MaintainPosAfterResize(Vector2 old, Vector2 neew, Vector2 pos) {
  return pos / old * neew;
}

float GetGravity(float gravToWinSizeRatio) {
  return GetRenderHeight() / gravToWinSizeRatio;
}
