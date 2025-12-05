all: main.o jogo.o snake.o frutinha.o mapa.o
	gcc jogo.o main.o snake.o frutinha.o mapa.o -o crobinha -lraylib -lm -lpthread -ldl -lGL -lX11

main.o: main.c jogo.h snake.h
	gcc -g -c main.c

jogo.o: jogo.h jogo.c
	gcc -g -c jogo.c

snake.o: snake.h snake.c
	gcc -g -c snake.c

frutinha.o: frutinha.h frutinha.c
	gcc -g -c frutinha.c

mapa.o: mapa.h mapa.c
	gcc -g -c mapa.c

run:
	./crobinha

clean:
	rm -r main.o jogo.o snake.o frutinha.o mapa.o crobinha

