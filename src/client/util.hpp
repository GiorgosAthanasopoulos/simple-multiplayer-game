#pragma once

#include <raylib.h>

Vector2 GetWindowSize();

Vector2 AssertTextFitsInViewport(const char *text, float fontSize,
                                 Vector2 maxSize);

Vector2 operator/(Vector2 a, float b);
Vector2 operator*(Vector2 a, float b);
Vector2 operator/(Vector2 a, Vector2 b);
Vector2 operator*(Vector2 a, Vector2 b);
void operator+=(Vector2 &a, Vector2 b);

bool MouseHovered(Rectangle rect);

Vector2 CalculateSize(Vector2 sizeToWinSizeRatioAxis);
Vector2 CalculateSpeed(Vector2 speedToWinSizeRatioAxis);
Vector2 MaintainPosAfterResize(Vector2 old, Vector2 neew, Vector2 pos);

float GetGravity(float gravToWinSizeRatio);
