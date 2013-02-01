#include <stdio.h>

#include "ourtypes.h"
#include "collide.h"

_Bool collide(int x, int y, unsigned int z, unsigned int w, unsigned int h, person *p){
  int leftA, leftB,
    rightA, rightB,
    topyA, topyB,
    bottomyA, bottomyB,
    topzA, topzB,
    bottomzA, bottomzB;
  
  leftA = x;
  leftB = p->x;
  rightA = x + w;
  rightB = p->x + PERSON_W;
  topyA = y;
  topyB = p->y;
  bottomyA = y + DEPTH;
  bottomyB = p->y + DEPTH;
  topzA = z + h;
  topzB = p->z + PERSON_H;
  bottomzA = z;
  bottomzB = p->z;
  
  return !( (leftA > rightB)
	    || (leftB > rightA)
	    || (topyA > bottomyB)
	    || (topyB > bottomyA)
	    || (topzA < bottomzB)
	    || (topzB < bottomzA) );
}
