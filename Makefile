main: main.h main.c ourtypes.h network.h things.h input.o display.o player.o chinese.o goon.o enemy.o collide.o projectile.o attack.o anim.o person.o
	gcc -o Angry\ Businessman.out main.c input.o display.o player.o chinese.o goon.o enemy.o collide.o projectile.o attack.o anim.o person.o -pedantic `sdl-config --cflags --libs`
	rm *.o

input.o: input.h input.c network.h ourtypes.h things.h
	gcc -c input.c -pedantic `sdl-config --cflags --libs`

display.o: display.h display.c ourtypes.h things.h
	gcc -c display.c -pedantic `sdl-config --cflags --libs`

player.o: people/player/player.h people/player/player.c ourtypes.h things.h
	gcc -c people/player/player.c -pedantic

chinese.o: people/enemies/chinese/chinese.h people/enemies/chinese/chinese.c people/enemies/enemies.h ourtypes.h
	gcc -c people/enemies/chinese/chinese.c -pedantic

goon.o: people/enemies/goon/goon.h people/enemies/goon/goon.c people/enemies/enemies.h ourtypes.h
	gcc -c people/enemies/goon/goon.c -pedantic

enemy.o: people/enemies/enemy.h people/enemies/enemy.c people/enemies/enemies.h ourtypes.h things.h
	gcc -c people/enemies/enemy.c -pedantic

collide.o: collide.h collide.c ourtypes.h
	gcc -c collide.c -pedantic

projectile.o: projectile.h projectile.c collide.h ourtypes.h
	gcc -c projectile.c -pedantic

attack.o: attack.h attack.c collide.h ourtypes.h things.h
	gcc -c attack.c -pedantic

anim.o: anim.h anim.c ourtypes.h things.h
	gcc -c anim.c -pedantic

person.o: people/person.h people/person.c ourtypes.h things.h
	gcc -c people/person.c -pedantic

clean:
	rm *.o
