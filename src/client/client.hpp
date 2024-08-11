#pragma once

#include <enet/enet.h>
#include <optional>
#include <raylib.h>
#include <string>

class Client {
public:
  Client();
  std::optional<Vector2> Update();
  ~Client();

  void SendStr(std::string msg);

private:
  ENetHost *client;
  ENetPeer *peer;
  bool firstMessage;
  int channel;
};
