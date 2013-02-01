SDL_Surface *screen;

void display();
void display_bg();
void display_spr();
void display_health();
void _display_person(person *p);
void display_projectile(projectile *pr);
void blit(char *filename,
	  int x, int y, unsigned int z,
	  unsigned int w, int x_offset, _Bool flip);

#define display_person(p) _display_person( (person*)(p) )
