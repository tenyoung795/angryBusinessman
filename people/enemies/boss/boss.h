#ifndef BOSS_H
#define BOSS_H

#define B_PREFIX "enemies/boss/"
#define B_X_OFFSET -32
#define B_STAND_T 60
#define B_WALK_T 150
#define B_SHOOT_T 15
#define B_SMACK_T 45
#define B_HURT_T 4
#define B_VX 2
#define B_VY 1

void init_boss(enemy *e);
void process_boss(enemy *e);
void stand_boss(enemy *e);
void walk_boss(enemy *e);
void smack_boss(enemy *e);
void hurt_boss(enemy *e);
void hurting_boss(enemy *e);

void set_img_boss(enemy *e, char *img, int dx);
void animate_boss(enemy *e, anim_t anim);

#endif
