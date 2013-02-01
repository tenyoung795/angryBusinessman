#include <stdlib.h>

#include "../../ourtypes.h"
#include "enemies.h"
#include "../../things.h"

void new_enemy(enum etype t, unsigned int health, int x, int y){
  int i;
  enemy *e;
  person *p;

  for (i = 0; i < MAX_ENEMIES && enemies[i]; i++);
  if (i >= MAX_ENEMIES) return;

  enemies[i] = calloc(sizeof(*enemies[i]), 1);
  e = enemies[i];
  p = (person*)e;

  p->x = x;
  p->y = y;
  p->health = health;
  p->heading = LEFT;
  e->type = t;

  switch(t){
  case GOON:
    init_goon(e);
    break;
  case CHINESE:
    init_chinese(e);
    break;
  case BOSS:
  case FINAL:
  default:
    break;
  }
    
  e->action = stand_enemy;
  stand_enemy(e);
}

void process_enemy(enemy **ptr){
  enemy *e;
  person *p;

  e = *ptr;
  p= (person*)e;

  if (!p->health){
    free(e);
    *ptr = NULL;
    return;
  }

  process(e);
  get_closest_player(e);

  if (!p->timer)
    switch (e->type){
    case GOON:
      process_goon(e);
      break;
    case CHINESE:
      process_chinese(e);
      break;
    case BOSS:
    case FINAL:
    default:
      break;
    }

  e->action(e);
}

void walk_enemy(enemy *e, int vx, int vy){
  person *ep, *plp;

  plp = (person*)e->closest;
  ep = (person*)e;

  if (abs(plp->x - ep->x) <= CLOSE_X_RANGE)
    ep->vx = 0;
  else if (plp->x < ep->x){
    ep->vx = -vx;
    ep->heading = LEFT;
    ep->flip = 0;
  }
  else{
    ep->vx = vx;
    ep->heading = RIGHT;
    ep->flip = 1;
  }
  
  if (abs(plp->y - ep->y) <= CLOSE_Y_RANGE)
    ep->vy = 0;
  else if (plp->y < ep->y)
    ep->vy = -vy;
  else
    ep->vy = vy;

  ep->vz = 0;
}

void hurt_enemy(enemy *e){
  switch (e->type){
  case GOON:
    hurt_goon(e);
    break;
  case CHINESE:
    hurt_chinese(e);
    break;
  case BOSS:
  case FINAL:
  default:
    break;
  }
}

void stand_enemy(enemy *e){
  switch (e->type){
  case GOON:
    stand_goon(e);
    break;
  case CHINESE:
    stand_chinese(e);
    break;
  case BOSS:
  case FINAL:
  default:
    break;
  }
}

void get_closest_player(enemy *e){
  int i, d2, d2min;

  e->closest = NULL;

  d2min = MAX_X * MAX_X;

  for (i = 0; i < MAX_PLAYERS; i++)
    if (players[i] && (d2 = distance_squared(e, players[i]) ) < d2min){
      d2min = d2;
      e->closest = players[i];
    }
}

int distance_squared(enemy *e, player *p){
  person *p0, *p1;
  int dx, dy, dz;

  p0 = (person*)e;
  p1 = (person*)p;

  dx = p0->x - p1->x;
  dy = p0->y - p1->y;
  dz = p0->z - p1->z;

  return dx * dx + dy * dy + dz * dz;
}
