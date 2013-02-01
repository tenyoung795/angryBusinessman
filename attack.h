#ifndef ATTACK_H
#define ATTACK_H

#define PL_PUNCH_X 32
#define PL_PUNCH_Z 16
#define PL_PUNCH_W 32
#define PL_PUNCH_H 12
#define PL_PUNCH_DMG 5
#define PL_PUNCH_T 4

#define PL_KICK_X 24
#define PL_KICK_Z 44
#define PL_KICK_W 54
#define PL_KICK_H 24
#define PL_KICK_DMG 2

#define G_PUNCH_X -32
#define G_PUNCH_Z 12
#define G_PUNCH_W 40
#define G_PUNCH_H 12
#define G_PUNCH_DMG 2
#define G_PUNCH_T 8
#define G_PUNCH_OFFSET -20

#define C_PUNCH_X -32
#define C_PUNCH_Z 12
#define C_PUNCH_W 32
#define C_PUNCH_H 12
#define C_PUNCH_DMG 6
#define C_PUNCH_T 4
#define C_PUNCH_OFFSET -32

#define C_KICK_X -36
#define C_KICK_Z 22
#define C_KICK_W 40
#define C_KICK_H 18
#define C_KICK_DMG 6
#define C_KICK_OFFSET -40

#define B_SMACK_X -28
#define B_SMACK_Z 20
#define B_SMACK_W 26
#define B_SMACK_H 20
#define B_SMACK_DMG 8

typedef struct{
  int x;
  unsigned int z, w, h, damage;
  enum pore {PLAYER, ENEMY} from;
  _Bool hits[MAX_ENEMIES]; /* MAX_ENEMIES > MAX_PLAYERS */
  person *p;
} attack;

attack *_new_attack(person *p, int x, unsigned int z, unsigned int w, unsigned int h, unsigned int damage, enum pore from);

attack *new_pl_punch(player *pl);
attack *new_pl_kick(player *pl);
attack *new_g_punch(enemy *e);

attack *new_c_punch(enemy *e);
attack *new_c_kick(enemy *e);

attack *new_b_smack(enemy *e);

void process_attack(attack *a);
_Bool _collide_attack(attack *a, person *p);
void _hurt(attack *a, person *p);

#define new_attack(p, x, z, w, h, damage, from) _new_attack( (person*)p, (x), (z), (w), (h), (damage), (from) )

#define collide_attack(a, p) _collide_attack( (a), (person*)(p) )
#define hurt(a, p) _hurt( (a), (person*)(p) )

#endif
