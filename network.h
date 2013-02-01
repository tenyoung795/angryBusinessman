#ifndef NETWORK_H
#define NETWORK_H

#define LOOPBACK "127.0.0.1"
#define PORT 60000
#define MSG_SIG "Angry Businessman"
#define MAX_CLIENTS (MAX_PLAYERS - 1)
#define EMPTY_FD -1

int host, listener, num_clients;
int clients[MAX_CLIENTS];

#endif
