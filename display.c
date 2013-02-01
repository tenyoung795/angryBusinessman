#include "SDL.h"

#include "ourtypes.h"
#include "things.h"
#include "display.h"

void display(){
  SDL_FillRect(screen, NULL, 0);
  display_bg();
  display_spr();
  SDL_Flip(screen);
}

void display_bg(){
  SDL_Surface *temp, *bg;

  temp = SDL_LoadBMP("images/levels/level0.bmp");
  bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  SDL_BlitSurface(bg, NULL, screen, NULL); 
  SDL_FreeSurface(bg);
}

void display_spr(){
  /* display from low to high (visual) y-coor */
  int i;

  for (i = 0; i < MAX_PLAYERS; i++)
    if (players[i])
      display_person(players[i]);

  for (i = 0; i < MAX_ENEMIES; i++)
    if (enemies[i])
      display_person(enemies[i]);

  for (i = 0; i < MAX_PROJECTILES; i++)
    if (projectiles[i])
      display_projectile(projectiles[i]);
}

void _display_person(person *p){
  blit(p->image, p->x, p->y, p->z, PERSON_W, p->x_offset, p->flip);
}

void display_projectile(projectile *pr){
  /* similar to display_person */
}

void display_health(){
  /* display player and enemy health */
  /* blit individual digits */
}

void blit(char *filename,
	  int x, int y, unsigned int z,
	  unsigned int w, int x_offset, _Bool flip){
  SDL_Surface *temp, *sprite;
  SDL_Rect rect, col;
  char name[64] = "images/";
  int i;

  if (!(*filename) )
    return;

  strncat(name, filename, sizeof(name) );
  strncat(name, ".bmp", sizeof(name) );

  temp = SDL_LoadBMP(name);
  sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  rect.w = sprite->w;
  rect.h = sprite->h;

  rect.x = x +
    (flip? (w - rect.w - x_offset): x_offset);
  rect.y = y - z;

  SDL_SetColorKey(sprite,
		  SDL_SRCCOLORKEY,
		  SDL_MapRGB(sprite->format, 128, 128, 128) );
  if (flip){
    col.w = 1;
    col.h = rect.h + ( (rect.y > 0)? 0 : rect.y);
    col.y = ( (rect.y > 0)? 0 : -rect.y);
    for (i = rect.w - 1; i >= 0; i--){
      if (rect.x++ >= 0){
	col.x = i;
	SDL_BlitSurface(sprite, &col, screen, &rect);
      }
    } 
  }
  else
    SDL_BlitSurface(sprite, NULL, screen, &rect);
  SDL_FreeSurface(sprite);

}
