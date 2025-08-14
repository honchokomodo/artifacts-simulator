CCFLAGS += -Llib -Iinclude -lm -lraylib

ifeq ($(OS), Windows_NT)
	CCFLAGS += -lgdi32 -lwinmm
endif

run: build/main
	build/main

build/main: src/*.c build generate_headers
	gcc -o build/main src/main.c $(CCFLAGS)

basic: src/*.c build generate_headers
	gcc -o build/basic src/examples/basic.c

generated_ui: src/*.c build generate_headers
	gcc -o build/generated_ui src/examples/generated_ui.c $(CCFLAGS)

uitest: src/*.c build generate_headers
	gcc -o build/uitest src/examples/uitest.c $(CCFLAGS)

uitest2: src/*.c build generate_headers
	gcc -o build/uitest2 src/examples/uitest2.c $(CCFLAGS)

generate_headers: build/include build/generate_characters build/generate_weapons build/generate_artifacts
	build/generate_characters
	build/generate_weapons
	build/generate_artifacts

build/generate_characters: src/generate_characters.c
	gcc -o build/generate_characters src/generate_characters.c

build/generate_weapons: src/generate_weapons.c
	gcc -o build/generate_weapons src/generate_weapons.c

build/generate_artifacts: src/generate_artifacts.c
	gcc -o build/generate_artifacts src/generate_artifacts.c

build/include:
	mkdir -p build/include

build:
	mkdir -p build
