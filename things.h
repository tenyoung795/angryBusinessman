#ifndef THINGS_H
#define THINGS_H

/* external variables for active "things" (people and projectiles) */
unsigned int num_players, playerno;

player *players[MAX_PLAYERS];
enemy *enemies[MAX_ENEMIES];
projectile *projectiles[MAX_PROJECTILES];

#endif
