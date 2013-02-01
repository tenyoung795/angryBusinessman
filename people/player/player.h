#ifndef PLAYER_H
#define PLAYER_H

#define PL_PREFIX "player/"
#define PL_X_OFFSET -10
#define PL_VZ 15
#define PL_VX 2
#define PL_VY 2
#define PL_HURT_T 3

typedef struct _player{
  person p;
  _Bool jump, attack, u, d, l, r, prev_jump, prev_attack;
  void (*action)(struct _player *pl);
} player;

void new_player();

void process_player(player **ptr);

void move_player(player *pl);

void attack_player(player *pl);
void punch_player(player *pl);
void kick_player(player *pl);

void jump_player(player *pl);
void jumping_player(player *pl);

void walk_player(player *pl);
void stand_player(player *pl);

void hurt_player(player *pl);
void hurting_player(player *pl);

void set_img_player(player *pl, char *filename, int dx);
void animate_player(player *pl, anim_t anim);

#endif
