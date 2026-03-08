# Makefile

logic.o:logic/logic.c
	gcc -c logic/logic.c

main.o:main.c
	gcc -c main.c

game2048:main.o logic.o
	gcc -o game2048 main.o logic.o

run: game2048
	./game2048

delet:
	rm -f main.o logic.o game2048	