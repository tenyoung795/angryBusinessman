#include <stdlib.h>
#include <string.h>

#include "ourtypes.h"
#include "collide.h"
#include "things.h"

int new_projectile(enemy *e,
		   unsigned int z,
		   unsigned int w, unsigned int h,
		   unsigned int damage,
		   unsigned int vx, int vy,
		   int x_offset, char *image){
  int i;
  projectile *pr;
  person *p;

  for (i = 0; i < MAX_PROJECTILES && projectiles[i]; i++);
  if (i >= MAX_PROJECTILES) return -1;

  p = (person*)e;

  projectiles[i] = calloc(sizeof(*projectiles[i]), 1);
  pr = projectiles[i];

  pr->x = p->x;
  pr->y = p->y;
  pr->z = z;
  pr->w = w;
  pr->h = h;
  pr->damage = damage;
  pr->timer = 0;
  pr->heading = p->heading;
  pr->vx = (pr->heading == LEFT)? -vx : vx;
  pr->vy = vy;
  set_img_projectile(pr, image, x_offset);

  return 0;
}

void process_projectile(projectile **ptr){
  projectile *pr;
  int i;

  pr = *ptr;

  pr->x += pr->vx;
  pr->y += pr->vy;
  pr->z += pr->vz;

  if (pr->x < 0 || pr->x >= MAX_X){
    free(pr);
    *ptr = NULL;
    return;
  }

  if (pr->y < MIN_Y)
    pr->y = MIN_Y;
  else if (pr->y >= MAX_Y)
    pr->y = MAX_Y;

  if (pr->z <= 0)
    pr->z = pr->vz = 0;

  for (i = 0; i < MAX_PLAYERS; i++);
}

void set_img_projectile(projectile *pr, char *img, int dx){
  pr->x_offset = dx;
  if (!img)
    strncpy(pr->image, "", sizeof(pr->image) );
  else{
    strncpy(pr->image, PR_PREFIX, sizeof(pr->image) );
    strncat(pr->image, img, sizeof(pr->image) );
  }
}
