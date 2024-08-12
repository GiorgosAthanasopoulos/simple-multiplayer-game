#include <cstring>
#include <enet/enet.h>
#include <stdio.h>
#include <vector>

int main(int argc, char **argv) {
  ENetAddress address;
  ENetHost *server;
  ENetEvent event;
  int eventStatus;
  int id = 1;
  std::vector<ENetPeer *> peers;

  if (enet_initialize() != 0) {
    fprintf(stderr, "An error occured while initializing ENet.\n");
    return EXIT_FAILURE;
  }

  address.host = ENET_HOST_ANY;
  address.port = 1234;

  // max_connections, max_channels
  server = enet_host_create(&address, 2, 3, 0, 0);
  if (server == NULL) {
    fprintf(stderr,
            "An error occured while trying to create an ENet server host\n");
    exit(EXIT_FAILURE);
  }

  eventStatus = 1;
  while (1) {
    eventStatus = enet_host_service(server, &event, 50000);

    if (eventStatus > 0) {
      switch (event.type) {
      case ENET_EVENT_TYPE_CONNECT:
        printf("(Server) We got a new connection from %x\n",
               event.peer->address.host);
        peers.push_back(event.peer);
        enet_peer_send(event.peer, 0,
                       enet_packet_create(id == 1 ? "1" : "2", 2,
                                          ENET_PACKET_FLAG_RELIABLE));
        id++;
        if (id == 3) {
          id = 1;
        }
        break;
      case ENET_EVENT_TYPE_RECEIVE:
        printf("(Server) Message from client : %s\n", event.packet->data);
        enet_host_broadcast(server, 0, event.packet);
        break;
      case ENET_EVENT_TYPE_DISCONNECT:
        printf("%s disconnected.\n", (char *)event.peer->data);
        event.peer->data = NULL;
        break;
      case ENET_EVENT_TYPE_NONE:
        break;
      }
    }
  }

  enet_host_destroy(server);
  enet_deinitialize();
}
