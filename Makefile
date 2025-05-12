
all:
	gcc -g -Wall main.c -o main -I. -L./lib -lglew32 -lopengl32 -lglfw3dll