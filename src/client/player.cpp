#include "player.hpp"
#include "config.hpp"
#include "util.hpp"
#include <raylib.h>
#include <vector>

Player::Player() {
  Reset();
  Resize(GetWindowSize(), GetWindowSize());
}

void Player::Resize(Vector2 old, Vector2 neew) {
  size = CalculateSize({PLAYER_SIZE_RATIO_X, PLAYER_SIZE_RATIO_Y});
  speed = CalculateSpeed({PLAYER_SPEED_RATIO_X, PLAYER_SPEED_RATIO_Y});
  pos = MaintainPosAfterResize(old, neew, pos);
}

void Player::Update(std::vector<EnvItem> envItems) {
  Vector2 vel = {0, 0};
  float delta = GetFrameTime();

  bool holdsLeft = IsKeyDown(KEY_PLAYER_MOVE_LEFT);
  bool holdsRight = IsKeyDown(KEY_PLAYER_MOVE_RIGHT);

  if (IsKeyPressed(KEY_PLAYER_JUMP) && canJump) {
    canJump = false;
    speedY = -speed.y;
  }

  if (holdsLeft && holdsRight) {
    vel.x = 0;
  } else if (holdsLeft) {
    vel.x = -speed.x;
  } else if (holdsRight) {
    vel.x = speed.x;
  }

  bool hitObstacle = false;
  for (size_t i = 0; i < envItems.size(); ++i) {
    Rectangle envRec = envItems[i].GetRec();
    if (envItems[i].IsBlocking() && envRec.x <= pos.x &&
        envRec.x + envRec.width >= pos.x && envRec.y >= pos.y &&
        envRec.y <= pos.y + speedY * delta) {
      hitObstacle = true;
      pos.y = envRec.y;
      speedY = 0;
      break;
    }
  }

  if (!hitObstacle) {
    canJump = false;
    pos.y += speedY * delta;
    speedY += GetGravity(GRAVITY_FORCE_RATIO) * delta;
  } else {
    canJump = true;
  }

  pos.x += vel.x * delta;
}

void Player::Draw() {
  DrawRectangleV({pos.x - size.x / 2, pos.y - size.y}, size, PLAYER_1_COLOR);
  DrawCircleV({pos}, 10.0f, PLAYER_POS_COLOR);
}

void Player::Reset() {
  this->pos = {PLAYER_START_X, PLAYER_START_Y};
  canJump = false;
}

Vector2 Player::GetPos() { return pos; }

Vector2 Player::GetSize() { return size; }
