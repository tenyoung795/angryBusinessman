#ifndef OURTYPES_H
#define OURTYPES_H

#define DEPTH 4
#define MAX_X 600
#define MIN_Y 360
#define MAX_Y 420
#define MAX_PLAYERS 4
#define MAX_ENEMIES 6
#define MAX_PROJECTILES 3

enum lorr {LEFT, RIGHT};

#include "people/person.h"
#include "anim.h"
#include "people/player/player.h"
#include "people/enemies/enemy.h"
#include "attack.h"
#include "projectile.h"

#endif
