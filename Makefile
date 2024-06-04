CC := clang++
FLAGS := -Wall -std=c++11
OUT := out/game
LIBS_PATH := -Ldependencies/lib
LIBS := -lglfw.3.4
INCLUDES := -Idependencies/include
TARGETS := src/*.cpp src/glad.c

build:
	$(CC) $(FLAGS) $(INCLUDES) $(TARGETS) -o $(OUT) $(LIBS_PATH) $(LIBS)

run:
	./$(OUT)

clean:
	rm $(OUT)

all: build run
