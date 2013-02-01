#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../ourtypes.h"
#include "../enemies/enemies.h"
#include "../../things.h"

char *PL_WALK_FRAMES[] = {"pl_stand", "pl_walk", NULL};
unsigned int PL_WALK_TIMES[] = {4, 4};
int PL_WALK_OFFSETS[] = {PL_X_OFFSET, PL_X_OFFSET};
anim_t PL_WALK_CYCLE = {PL_WALK_FRAMES, PL_WALK_TIMES, PL_WALK_OFFSETS};

void new_player(){
  person *p;
  player *pl, **ptr;

  ptr = players;
  while (*ptr) ptr++;

  *ptr = calloc(sizeof(**ptr), 1);
  pl = *ptr;
  p = (person*)pl;

  p->y = MIN_Y;
  p->health = 100;
  set_img_player(pl, "pl_stand", PL_X_OFFSET);
  p->heading = RIGHT;
  pl->action = stand_player;
}

void process_player(player **ptr){
  player *pl = *ptr;
  person *p = (person*)pl;

  if (!p->health){
    free(pl);
    *ptr = NULL;
    num_players--;
    return;
  }

  process(pl);

  if (!p->timer && p->att && pl->action != kick_player){
    free(p->att);
    p->att = NULL;
  }

  pl->action = p->timer? pl->action
    : (!p->timer && pl->attack && !pl->prev_attack)? attack_player
    : (!p->z && pl->jump && !pl->prev_jump)? jump_player
    : (p->az)? pl->action
    : (pl->l || pl->r || pl->u || pl->d)? walk_player
    : stand_player;

  pl->action(pl);
}

void attack_player(player *pl){
  person *p = (person*)pl;
  if (pl->p.z){
    p->att = new_pl_kick(pl);
    pl->action = kick_player;    
  }
  else{
    p->timer = PL_PUNCH_T;
    p->att = new_pl_punch(pl);
    pl->action = punch_player;
  }
}

void kick_player(player *pl){
  set_img_player(pl, "pl_kick", PL_X_OFFSET);
  move_player(pl);
}

void punch_player(player *pl){
  set_img_player(pl, "pl_punch", PL_X_OFFSET);   
  stand(pl);
}

void jump_player(player *pl){
  jump(pl, PL_VZ);
  pl->action = jumping_player;
}

void jumping_player(player *pl){
  set_img_player(pl, "pl_jump", PL_X_OFFSET);
  move_player(pl);
}

void walk_player(player *pl){
  animate_player(pl, PL_WALK_CYCLE);
  pl->p.vz = 0;
  move_player(pl);
}

void stand_player(player *pl){
  set_img_player(pl, "pl_stand", PL_X_OFFSET);
  stand(pl);
}

void move_player(player *pl){
  person *p = (person*)pl;

  if (pl->l && !pl->r)
    p->heading = LEFT;
  else if (pl->r)
    p->heading = RIGHT;

  p->flip = (p->heading == RIGHT)? 0 : 1;

  p->vx = (pl->l && !pl->r)? -PL_VX : (pl->r)? PL_VX : 0;
  p->vy = (pl->u && !pl->d)? -PL_VY : (pl->d)? PL_VY : 0;
}

void hurt_player(player *pl){
  pl->p.timer = PL_HURT_T;
  pl->action = hurting_player;
}

void hurting_player(player *pl){
  set_img_player(pl, "pl_hurt", PL_X_OFFSET);
  if (!pl->p.az) stand(pl);
}

void set_img_player(player *pl, char *filename, int dx){
  set_img(pl, PL_PREFIX, filename, dx);
}

void animate_player(player *pl, anim_t anim){
  animate(pl, PL_PREFIX, anim);
}
