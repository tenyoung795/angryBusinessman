#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>

#include "SDL.h"

#include "ourtypes.h"
#include "things.h"
#include "network.h"
#include "display.h"
#include "input.h"
#include "main.h"

int main(){
  initialize();  
  run();
  return EXIT_SUCCESS;
}

void initialize(){
  int i;
  struct sigaction act;

  umask(0000);

  SDL_Init(SDL_INIT_EVERYTHING); 
  which_frame = 0;

  mode = MENU;
  
  for (i = 0; i < MAX_PLAYERS; i++)
    players[i] = NULL;

  for (i = 0; i < MAX_ENEMIES; i++)
    enemies[i] = NULL;

  for (i = 0; i < MAX_PROJECTILES; i++)
    projectiles[i] = NULL;

  host = listener = EMPTY_FD;
  for (i = 0; i < MAX_CLIENTS; i++)
    clients[i] = EMPTY_FD;

  act.sa_handler = sighandler;
  sigemptyset(&(act.sa_mask) );
  act.sa_flags = 0;

  sigaction(SIGINT, &act, NULL);
  sigaction(SIGTERM, &act, NULL);
  sigaction(SIGQUIT, &act, NULL);
  sigaction(SIGABRT, &act, NULL);

  atexit(cleanup);
}

void run(){
  while(1){
    SDL_Delay( (which_frame)? HIGH_INTERVAL : LOW_INTERVAL);
    switch(mode){
    case EXIT:
      return;
    case MENU:
      menu();
      break;
    case GAMEPLAY:
      gameplay();
      break;
    case ENDING:
      ending();
    default:
      break;
    }
    which_frame += (which_frame == 2)? -2:1;
  }
}

void menu(){
  char in[32];
  int i, data[2];
  unsigned int len;
  struct sockaddr_in sock;

  printf("Welcome to Angry Businessman!\n");
  while(1){
    printf("Netplay? (y/n) $ ");
    fgets(in, sizeof(in), stdin);
    *strchr(in, '\n') = '\0';

    if (!strncasecmp(in, "y", sizeof(in) ) ){
      sock.sin_family = AF_INET;
      sock.sin_port = htons(PORT);      	  

      while(1){
	printf("Hosting? (y/n) $ ");
	fgets(in, sizeof(in), stdin);
	*strchr(in, '\n') = '\0';

	if (!strncasecmp(in, "y", sizeof(in) ) ){
	  playerno = 0;
	  while (num_players < 2 || num_players > MAX_PLAYERS){
	    printf("How many are playing? (2 to 4) $ ");
	    fgets(in, sizeof(in), stdin);
	    *strchr(in, '\n') = '\0';
	    num_players = atoi(in);
	  }

	  data[1] = num_players;
	  num_clients = num_players - 1;

	  len = sizeof(sock);
	  sock.sin_addr.s_addr = INADDR_ANY;
	  listener = socket(AF_INET, SOCK_STREAM, 0);

	  printf("Binding...\n");
	  while (bind(listener, (struct sockaddr *)&sock, sizeof(sock) ) );

	  printf("Listening...\n");
	  while (listen(listener, num_clients) );

	  printf("Connecting...\n");
	  for (i = 0; i < num_clients; i++){
	    clients[i] = accept(listener, (struct sockaddr *)&sock, &len);
	    printf("Connected to client %d.\n", i);
	  }

	  for (i = 0; i < num_clients; i++){
	    data[0] = i + 1;
	    write(clients[i], data, sizeof(data) );
	  }

	  printf("All connected!\n");
	  break;
	}

	else if (!strncasecmp(in, "n", sizeof(in) ) ){
	  do{
	    printf("Enter IPv4 address of host $ ");
	    fgets(in, sizeof(in), stdin);
	    *strchr(in, '\n') = '\0';
	  }
	  while (!inet_aton(in, &(sock.sin_addr) ) );

	  host = socket(AF_INET, SOCK_STREAM, 0);

	  printf("Connecting...\n");
	  while (connect(host, (struct sockaddr *)&sock, sizeof(sock) ) );

	  read(host, data, sizeof(data) );
	  playerno = data[0];
	  num_players = data[1];
	  num_clients = num_players - 1;
	  printf("All connected!\n");

	  break;
	}
      }
      break;
    }
    else if (!strncasecmp(in, "n", sizeof(in) ) ){
      playerno = num_clients = 0;
      num_players = 1;
      break;
    }
  }
  printf("Get ready!\n");

  sleep(1);
  screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);

  level = 0;
  for (i = 0; i < num_players; i++)
    new_player();
  new_enemy(GOON, 20, 320, MIN_Y);
  new_enemy(CHINESE, 15, 360, 380);
  mode = GAMEPLAY;
}

void gameplay(){
  display();
  input();
  process_all();
}

void process_all(){
  int i;
  for (i = 0; i < MAX_PLAYERS; i++)
    if (players[i])
      process_player(players + i);

  if (!num_players){
    mode = EXIT;
    return;
  }

  for (i = 0; i < MAX_ENEMIES; i++)
    if (enemies[i])
      process_enemy(enemies + i);
  for (i = 0; i < MAX_PROJECTILES; i++)
    if (projectiles[i])
      process_projectile(projectiles + i);
}


void ending(){
  mode = MENU;
}

void cleanup(){
  int i;
  for (i = 0; i < MAX_PLAYERS; i++)
    if (players[i]){
      free(players[i]->p.att);
      free(players[i]);
    }

  for (i = 0; i < MAX_ENEMIES; i++)
    if (enemies[i]){
      free(enemies[i]->p.att);
      free(enemies[i]);
    }

  for (i = 0; i < MAX_PROJECTILES; i++)
    free(projectiles[i]);

  if (playerno)
    close(host);

  else if (num_clients){
    for (i = 0; i < MAX_CLIENTS; i++)
      if (clients[i] > 0)
	close(clients[i]);
    close(listener);
  }

  SDL_FreeSurface(screen);

  /* Call SDL_Quit() once you're done with SDL. */
  SDL_Quit();
}

void sighandler(int signum){
  struct sigaction act;
  int i;
  
  /* send last exiting message */
  mode = EXIT;
  if (playerno)
    broadcast(host, playerno);
  else if (num_clients)
    for (i = 0; i < MAX_CLIENTS; i++)
      if (clients[i] > 0)
	broadcast(clients[i], 0);

  cleanup();

  act.sa_handler = SIG_DFL;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  sigaction(signum, &act, NULL);
  raise(signum);
}

