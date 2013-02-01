#include <string.h>

#include "ourtypes.h"

void _set_img(person *p, char *prefix, char *img, int dx){
  if (!img)
    strncpy(p->image, "", sizeof(p->image) );
  else{
    strncpy(p->image, prefix, sizeof(p->image) );
    strncat(p->image, img, sizeof(p->image) );
    p->x_offset = dx;
  }
}

void _animate(person *p, char *prefix, anim_t anim){
  if (!(p->anim_timer += (p->anim_timer < anim.times[p->anim_frame])?
	1 : -p->anim_timer) )
    p->anim_frame += anim.frames[p->anim_frame + 1]?
      1 : -p->anim_frame;
  _set_img(p, prefix, anim.frames[p->anim_frame], anim.x_offsets[p->anim_frame]);
}
