RAYLIB ?= ./external/raylib-5.5/src/

all:
	g++ src/main.cpp -I $(RAYLIB) -L $(RAYLIB) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	./a.out
