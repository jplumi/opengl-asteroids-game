CC := clang++
FLAGS := -Wall -std=c++11
OUT := out/game
LIBS_PATH := -Ldependencies/lib
LIBS := -lglfw.3.4
INCLUDES := -Idependencies/include -Isrc
SRC := src
CPP_SRCS=$(shell find $(SRC) -name "*.cpp")

build:
	$(CC) $(FLAGS) src/glad.c $(CPP_SRCS) $(INCLUDES) -o $(OUT) $(LIBS_PATH) $(LIBS) -DDEV_BUILD

release:
	$(CC) $(FLAGS) src/glad.c $(CPP_SRCS) $(INCLUDES) -o $(OUT) $(LIBS_PATH) $(LIBS)

run:
	./$(OUT)

clean:
	rm $(OUT)

all: build run
