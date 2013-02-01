#ifndef PERSON_HEADER
#define PERSON_HEADER

#define GRAVITY 1
#define PERSON_W 20
#define PERSON_H 60

typedef struct {
  int x, y,
    vx, vy, vz,
    az, x_offset;
  unsigned int z,
    health, timer,
    anim_frame, anim_timer; 
  void *att; /* should be attack *att, but then the struct definitions become circular */
  char image[64];
  enum lorr heading;
  _Bool flip;
} person;

void _move(person *p);
void _jump(person *p, int vz);
void _stand(person *p);
void _process(person *p);

/* psuedo polymorphism */
#define move(p) _move( (person*)(p) )
#define jump(p, vz) _jump( (person*)(p), (vz) )
#define stand(p) _stand( (person*)(p) )
#define process(p) _process( (person*)(p) )

#endif
