#pragma once

// window
#define WIN_FLAGS FLAG_WINDOW_RESIZABLE
#define WIN_W 1280
#define WIN_H 720
#define WIN_TITLE "Simple Multiplayer Game"
#define WIN_FPS 30
#define WIN_MIN_W 640
#define WIN_MIN_H 480
#define WIN_MAX_W 3840
#define WIN_MAX_H 2160
#define WIN_BG SKYBLUE

// keybind
#define KEY_EXIT KEY_NULL
#define KEY_PLAYER_MOVE_LEFT KEY_A
#define KEY_PLAYER_MOVE_RIGHT KEY_D
#define KEY_PLAYER_JUMP KEY_SPACE
#define KEY_RESTART KEY_R

// debug
#define DEBUG true

// server
#define SERVER_IP "localhost"
#define SERVER_PORT 1234
#define SERVER_IDLE_DELAY_MS 10

// ui
#define FONT_SIZE 100
#define LARGE_FONT_SIZE FONT_SIZE * 100

// player
#define PLAYER_SIZE_RATIO_X 15
#define PLAYER_SIZE_RATIO_Y 9
#define PLAYER_SPEED_RATIO_X 3
#define PLAYER_SPEED_RATIO_Y 2
#define PLAYER_START_X 400
#define PLAYER_START_Y 280
#define PLAYER_1_COLOR RED
#define PLAYER_2_COLOR BLUE
#define GRAVITY_FORCE_RATIO 1.5
#define PLAYER_POS_COLOR GOLD
