ifeq ($(OS), Windows_NT)
	CCFLAGS += -lgdi32 -lwinmm
endif

run: build/main
	build/main

build/main: src/*.c build
	gcc -o build/main src/main.c -Llib -Iinclude -lm -lraylib $(CCFLAGS)

build:
	mkdir -p build
