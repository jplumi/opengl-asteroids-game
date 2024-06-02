CC := clang++
FLAGS := -Wall
OUT := out/game
LIBS_PATH := -Ldependencies/lib
LIBS := -lglfw.3.4 # -lSDL2-2.0.0
INCLUDES := -Idependencies/include
TARGETS := src/*.cpp src/glad.c

build:
	$(CC) $(FLAGS) $(INCLUDES) $(TARGETS) -o $(OUT) $(LIBS_PATH) $(LIBS)

run:
	./$(OUT)

clean:
	rm $(OUT)

all: build run
