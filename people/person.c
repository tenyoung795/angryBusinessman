#include <string.h>

#include "../ourtypes.h"

void _move(person *p){
  p->vz += p->az;

  p->x += p->vx;
  p->y += p->vy;
  p->z += p->vz;

  if (p->x < 0)
    p->x = 0;
  else if (p->x >= MAX_X)
    p->x = MAX_X;

  if (p->y < MIN_Y)
    p->y = MIN_Y;
  else if (p->y >= MAX_Y)
    p->y = MAX_Y;

  if (p->z <= 0)
    p->z = p->vz = p->az = 0;
}

void _jump(person *p, int vz){
  p->az = -GRAVITY;
  p->vz = vz;
}

void _stand(person *p){
  p->vx = p->vy = p->vz = 0;
}

void _process(person *p){
  move(p);
  if (p->att)
    process_attack(p->att);
  if (p->timer) p->timer--;
}
