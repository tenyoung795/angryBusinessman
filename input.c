#include <unistd.h>
#include <stdio.h>

#include "SDL.h"

#include "ourtypes.h"
#include "things.h"
#include "network.h"
#include "main.h"
#include "input.h"

void input(){
  SDL_Event event;

  if (players[playerno])
    key_input();   

  else if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
    mode = EXIT;
  
  if (playerno){ /* nonzero playerno is client */
    broadcast(host, playerno);
    get_server_output();
  }

  else if (num_clients){ /* 0 playerno is host */
    get_client_input();
    broadcast_all();
  }
}

void key_input(){
  SDL_Event event;
  player *pl = players[playerno];

  pl->prev_jump = pl->jump;
  pl->prev_attack = pl->attack;

  while (SDL_PollEvent(&event) )
    switch (event.type){
    case SDL_QUIT:
      mode = EXIT;
      return;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym){
      case SDLK_z:
	pl->attack = 1;
	break;
      case SDLK_x:
	pl->jump = 1;
	break;
      case SDLK_UP:
	pl->u = 1;
	break;
      case SDLK_DOWN:
	pl->d = 1;
	break;
      case SDLK_LEFT:
	pl->l = 1;
	break;
      case SDLK_RIGHT:
	pl->r = 1;
      default:
	break;
      }
      break;
    case SDL_KEYUP:
      switch (event.key.keysym.sym){
      case SDLK_z:
	pl->attack = 0;
	break;
      case SDLK_x:
	pl->jump = 0;
	break;
      case SDLK_UP:
	pl->u = 0;
	break;
      case SDLK_DOWN:
	pl->d = 0;
	break;
      case SDLK_LEFT:
	pl->l = 0;
	break;
      case SDLK_RIGHT:
	pl->r = 0;
      default: break;
      }
    default: break;
    }
}

void get_server_output(){
  int i;
  for (i = 0; i < num_clients; i++)
    update_player(host);
}

void update_player(int sd){
  player *pl; 
  net_input ni;

  read(sd, &ni, sizeof(ni) );
  
  if (!playerno && clients[ni.playerno - 1] < 0)
    return; /* host: discard messages from nonexistent clients */

  pl = players[ni.playerno];
  
  if (ni.exit){
    if (pl){
      free(pl->p.att); /* remember to destroy attack! */
      free(pl);
      players[ni.playerno] = NULL;
      num_players--;
    }

    if (ni.playerno){
      if (!playerno){ /* host ends connection with exiting client */
	close(clients[ni.playerno - 1]);
	clients[ni.playerno - 1] = EMPTY_FD;
      }
      num_clients--;
    }

    else{
      printf("Host ended the game.\n");
      mode = EXIT; /* game ends if host quits */
    }

    return;
  }

  if (!pl) return;

  pl->prev_attack = pl->attack;
  pl->prev_jump = pl->jump;

  pl->attack = ni.attack;
  pl->jump = ni.jump;
  pl->u = ni.u;
  pl->d = ni.d;
  pl->l = ni.l;
  pl->r = ni.r;
}

void broadcast(int sd, int pno){
  net_input ni;
  player *pl;
  
  pl = players[pno];

  ni.playerno = pno;
  ni.exit = (mode == EXIT);

  if (pl){
    ni.attack = pl->attack;
    ni.jump = pl->jump;
    ni.u = pl->u;
    ni.d = pl->d;
    ni.l = pl->l;
    ni.r = pl->r;
  }

  write(sd, &ni, sizeof(ni) );
}

void get_client_input(){
  int i;
  for (i = 0; i < MAX_CLIENTS; i++)
    if (clients[i] > 0)
      update_player(clients[i]);
}

void broadcast_all(){
  int i, j;
  for (i = 0; i < MAX_CLIENTS; i++)
    if (clients[i] > 0)
      for (j = 0; j < MAX_PLAYERS; j++)
	if (!j || (clients[j - 1] > 0 && i != j - 1) )
	  broadcast(clients[i], j);
}
