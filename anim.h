#ifndef ANIM_H
#define ANIM_H

typedef struct {
  char **frames;
  unsigned int *times;
  int *x_offsets;
} anim_t;

void _set_img(person *p, char *prefix, char *img, int dx);
void _animate(person *p, char *prefix, anim_t anim);

#define set_img(p, prefix, img, dx) _set_img( (person*)(p), (prefix), (img), (dx) )
#define animate(p, prefix, anim) _animate( (person*)(p), (prefix), (anim) )

#endif
