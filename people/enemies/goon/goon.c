#include <stdlib.h>

#include "../../../ourtypes.h"
#include "../enemies.h"

char *G_WALK_FRAMES[] = {"g_stand", "g_walk", NULL};
unsigned int G_WALK_TIMES[] = {4, 4};
int G_WALK_OFFSETS[] = {G_X_OFFSET, G_X_OFFSET};
anim_t G_WALK_CYCLE = {G_WALK_FRAMES, G_WALK_TIMES, G_WALK_OFFSETS};

void init_goon(enemy *e){
  person *p;
  p = (person*)e;

  p->timer = G_STAND_T;
  p->x_offset = G_X_OFFSET;
}

void process_goon(enemy *e){
  person *p;
  p = (person*)e;

  if (e->action == stand_goon)
    e->action = walk_goon;
  else if (e->action != walk_goon){
    p->timer = G_STAND_T;
    e->action = stand_goon;
  }
}

void stand_goon(enemy *e){
  set_img_goon(e, "g_stand", G_X_OFFSET);
  stand(e);
}

void walk_goon(enemy *e){
  person *p;
  p = (person*)e;

  animate_goon(e, G_WALK_CYCLE);
  walk_enemy(e, G_VX, G_VY);
  if (!(p->vx || p->vy) ){
    p->timer = G_PUNCH_T;
    p->att = new_g_punch(e);
    e->action = punch_goon;
  }
}

void punch_goon(enemy *e){
  set_img_goon(e, "g_punch", G_PUNCH_OFFSET);
  stand(e);
}

void hurt_goon(enemy *e){
  e->p.timer = G_HURT_T;
  e->action = hurting_goon;
}

void hurting_goon(enemy *e){
  if (e->p.timer % 2)
    set_img_goon(e, NULL, 0);
  else
    set_img_goon(e, "g_stand", G_X_OFFSET);
  stand(e);
}

void set_img_goon(enemy *e, char *img, int dx){
  set_img(e, G_PREFIX, img, dx);
}

void animate_goon(enemy *e, anim_t anim){
  animate(e, G_PREFIX, anim);
}
