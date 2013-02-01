#include <stdlib.h>

#include "../../../ourtypes.h"
#include "../enemies.h"

char *C_WALK_FRAMES[] = {"c_stand", "c_walk", NULL};
unsigned int C_WALK_TIMES[] = {6, 6};
int C_WALK_OFFSETS[] = {C_X_OFFSET, C_X_OFFSET};
anim_t C_WALK_CYCLE = {C_WALK_FRAMES, C_WALK_TIMES, C_WALK_OFFSETS};

void init_chinese(enemy *e){
  person *p;
  p = (person*)e;

  p->timer = C_STAND_T;
  p->x_offset = C_X_OFFSET;
}

void process_chinese(enemy *e){
  person *p;
  p = (person*)e;

  if (e->action == stand_chinese)
    e->action = walk_chinese;
  else if (e->action != walk_chinese
	   && e->action != jump_chinese
	   && !p->az){
    p->timer = C_STAND_T;
    e->action = stand_chinese;
  }
}

void stand_chinese(enemy *e){
  set_img_chinese(e, "c_stand", C_X_OFFSET);
  stand(e);
}

void walk_chinese(enemy *e){
  person *plp, *ep;
  unsigned int d;

  plp = (person*)e->closest;
  ep = (person*)e;

  animate_chinese(e, C_WALK_CYCLE);
  walk_enemy(e, C_VX, C_VY);
  if (!ep->vy){
    if ( (d = abs(plp->x - ep->x) ) <= CLOSE_X_RANGE){
      ep->timer = C_PUNCH_T;
      ep->att = new_c_punch(e);
      e->action = punch_chinese;
    }
    else if (d <= MID_FAR_X_RANGE && d >= MID_CLOSE_X_RANGE)
      e->action = jump_chinese;
  }
}

void punch_chinese(enemy *e){
  set_img_chinese(e, "c_punch", C_PUNCH_OFFSET);
  stand(e);
}

void jump_chinese(enemy *e){
  person *p;
  p = (person*)e;

  jump(e, C_VZ);
  p->vx = (e->closest->p.x < p->x)? -C_JUMP_VX : C_JUMP_VX;
  p->vy = 0;
  p->att = new_c_kick(e);
  e->action = kick_chinese;
}

void kick_chinese(enemy *e){
  set_img_chinese(e, "c_kick", C_KICK_OFFSET);
}

void hurt_chinese(enemy *e){
  e->p.timer = C_HURT_T;
  e->action = hurting_chinese;
}

void hurting_chinese(enemy *e){
  person *p;
  p = (person*)e;

  if (p->timer % 2)
    set_img_chinese(e, NULL, 0);
  else
    set_img_chinese(e, "c_stand", C_X_OFFSET);

  if (!p->az)
    stand(e);
}

void set_img_chinese(enemy *e, char *img, int dx){
  set_img(e, C_PREFIX, img, dx);
}

void animate_chinese(enemy *e, anim_t anim){
  animate(e, C_PREFIX, anim);
}
