#ifndef PROJECTILE_H
#define PROJECTILE_H

#define PR_PREFIX "images/projectiles/"

#define BULLET_DMG 15

typedef struct{
  unsigned int x, y, z,
    w, h, damage, timer;
  int vx, vy, vz, x_offset;
  char image[64];
  enum lorr heading;
  _Bool flip;
} projectile;

int new_projectile(enemy *e,
		   unsigned int z,
		   unsigned int w, unsigned int h,
		   unsigned int damage,
		   unsigned int vx, int vy,
		   int x_offset, char *image);


int new_bullet(enemy *e);

void process_projectile(projectile **ptr);

void set_img_projectile(projectile *pr, char *img, int dx); 

#endif
