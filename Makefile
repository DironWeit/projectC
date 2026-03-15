# Makefile

logic.o:logic/logic.c
	gcc -c logic/logic.c

main.o:main.c
	gcc -c main.c

gui.o:gui/gui.c
	gcc -c gui/gui.c -o gui.o `sdl2-config --cflags`

game2048:main.o logic.o gui.o
	gcc -o game2048 main.o logic.o gui.o `sdl2-config --libs` -lSDL2_ttf

run: game2048
	./game2048

delet:
	rm -f main.o logic.o gui.o game2048	