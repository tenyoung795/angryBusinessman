#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ourtypes.h"
#include "collide.h"
#include "things.h"

attack *_new_attack(person *p, int x, unsigned int z, unsigned int w, unsigned int h, unsigned int damage, enum pore from){
  attack *a;
  a = calloc(sizeof(*a), 1);
  
  a->p = p;
  a->x = x;
  a->z = z;
  a->w = w;
  a->h = h;
  a->damage = damage;
  a->from = from;

  return a;
}

attack *new_pl_punch(player *pl){
  return new_attack(pl, PL_PUNCH_X, PL_PUNCH_Z, PL_PUNCH_W, PL_PUNCH_H, PL_PUNCH_DMG, PLAYER);
}

attack *new_pl_kick(player *pl){
  return new_attack(pl, PL_KICK_X, PL_KICK_Z, PL_KICK_W, PL_KICK_H, PL_KICK_DMG, PLAYER);
}

attack *new_g_punch(enemy *e){
  return new_attack(e, G_PUNCH_X, G_PUNCH_Z, G_PUNCH_W, G_PUNCH_H, G_PUNCH_DMG, ENEMY);
}

attack *new_c_punch(enemy *e){
  return new_attack(e, C_PUNCH_X, C_PUNCH_Z, C_PUNCH_W, C_PUNCH_H, C_PUNCH_DMG, ENEMY);
}

attack *new_c_kick(enemy *e){
  return new_attack(e, C_KICK_X, C_KICK_Z, C_KICK_W, C_KICK_H, C_KICK_DMG, ENEMY);
}

attack *new_b_smack(enemy *e){
  return new_attack(e, B_SMACK_X, B_SMACK_Z, B_SMACK_W, B_SMACK_H, B_SMACK_DMG, ENEMY);
}

void process_attack(attack *a){
  int i;
  if (a->from == PLAYER)
    for (i = 0; i < MAX_ENEMIES; i++) {
      if (enemies[i] && !a->hits[i] && collide_attack(a, enemies[i]) ){
	a->hits[i] = 1;
	hurt(a, enemies[i]);
	hurt_enemy(enemies[i]);
	printf("enemy %u: %u\n", i, enemies[i]->p.health);
      }
    }
  else
    for (i = 0; i < MAX_PLAYERS; i++)
      if (players[i] && !a->hits[i] && collide_attack(a, players[i]) ){
	a->hits[i] = 1;
	hurt(a, players[i]);
	hurt_player(players[i]);
	printf("player %u: %u\n", i, players[i]->p.health);
      }
}

_Bool _collide_attack(attack *a, person *p){
  return collide(a->p->x + (a->p->flip? (PERSON_W - a->w - a->x) : a->x),
		 a->p->y,
		 a->p->z + a->z,
		 a->w,
		 a->h,
		 p);
}

void _hurt(attack *a, person *p){
  free(p->att);
  p->att = NULL;
  p->vx /= -2;
  p->health -= (p->health < a->damage)? p->health : a->damage;
}
