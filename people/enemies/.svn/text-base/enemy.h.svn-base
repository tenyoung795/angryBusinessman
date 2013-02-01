#ifndef ENEMY_H
#define ENEMY_H

#define CLOSE_X_RANGE 24
#define CLOSE_Y_RANGE 2
#define MID_CLOSE_X_RANGE 64
#define MID_FAR_X_RANGE 100
#define FAR_X_RANGE 200

typedef struct _enemy{
  person p;
  enum etype {GOON, CHINESE, BOSS, FINAL} type;
  player *closest;
  void (*action)(struct _enemy*);
} enemy;

void new_enemy(enum etype t, unsigned int health, int x, int y);
void process_enemy(enemy **ptr);
void walk_enemy(enemy *e, int vx, int vy);
void stand_enemy(enemy *e);
void hurt_enemy(enemy *e);

void get_closest_player(enemy *e);
int distance_squared(enemy *e, player *p);

#endif
