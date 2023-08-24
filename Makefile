tetris: main.o player.o table.o shape.o
	gcc -o tetris main.o player.o table.o shape.o -lncurses

main.o: main.c player.h table.h shape.h
	gcc -c main.c

player.o: player.h player.c
	gcc -c player.c

table.o: table.h table.c
	gcc -c table.c

shape.o: shape.h shape.c
	gcc -c shape.c

clean:
	rm -rf *.o tetirs
