#ifndef INPUT_H
#define INPUT_H

typedef struct{
  int playerno;
  _Bool exit, attack, jump, u, d, l, r;
} net_input;

void input();
void key_input();

void get_server_output();
void broadcast(int sd, int pno);

void get_client_input();
void broadcast_all();

void update_player(int sd);

#endif
