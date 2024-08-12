#include "client.hpp"
#include "config.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <enet/enet.h>
#include <iostream>
#include <optional>
#include <raylib.h>
#include <sstream>
#include <string>
#include <vector>

Client::Client() {
  ENetAddress address;
  firstMessage = true;

  if (enet_initialize() != 0) {
    std::cerr << "[ERROR]: failed to init enet\n";
    exit(EXIT_FAILURE);
  }

  client = enet_host_create(NULL, 1, 3, 57600 / 8, 14400 / 8);
  if (client == NULL) {
    std::cerr << "[ERROR]: failed to create client\n";
    exit(EXIT_FAILURE);
  }

  enet_address_set_host(&address, SERVER_IP);
  address.port = SERVER_PORT;

  peer = enet_host_connect(client, &address, 3, 0);
  if (peer == NULL) {
    std::cerr << "[ERROR]: failed to connect to host\n";
    exit(EXIT_FAILURE);
  }
}

std::optional<Vector2> Client::Update() {
  ENetEvent event;
  int eventStatus = enet_host_service(client, &event, SERVER_IDLE_DELAY_MS);

  while (eventStatus > 0) {
    switch (event.type) {
    case ENET_EVENT_TYPE_NONE:
      break;
    case ENET_EVENT_TYPE_CONNECT:
      printf("(Client) We got a new connection from %x\n",
             event.peer->address.host);
      break;
    case ENET_EVENT_TYPE_DISCONNECT:
      printf("(Client) %s disconnected.\n", (char *)event.peer->data);
      event.peer->data = NULL;
      break;
    case ENET_EVENT_TYPE_RECEIVE:
      printf("(Client) Message from server : %s\n", (char *)event.packet->data);
      if (firstMessage) {
        firstMessage = false;
        channel = std::atoi((char *)event.packet->data);
      } else {
        std::string pos = (char *)event.packet->data;

        std::stringstream ss(pos);

        std::string token;
        std::vector<std::string> tokens;
        char delimiter = ';';

        while (getline(ss, token, delimiter)) {
          tokens.push_back(token);
        }

        if (channel != atoi(tokens[0].data()) &&
            strcmp(tokens[1].data(), "pos") == 0) {
          return Vector2{(float)atoi(tokens[2].data()),
                         (float)atoi(tokens[3].data())};
        }
      }
      enet_packet_destroy(event.packet);
      break;
    }
    eventStatus = enet_host_service(client, &event, SERVER_IDLE_DELAY_MS);
  }

  return {};
}

void Client::SendStr(std::string msg) {
  std::ostringstream ss;
  ss << channel << ";" << msg;
  std::string msgS = ss.str();
  const char *text = msgS.data();
  enet_peer_send(
      peer, channel == 1 ? 2 : 1,
      enet_packet_create(text, strlen(text) + 1, ENET_PACKET_FLAG_RELIABLE));
}

Client::~Client() {
  enet_peer_disconnect(peer, 0);
  enet_host_destroy(client);
  enet_deinitialize();
};
