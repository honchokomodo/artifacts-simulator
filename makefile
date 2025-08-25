CCFLAGS += -Llib -Iinclude -lm -lraylib
UNAME_S := $(shell uname -s)

ifeq ($(OS), Windows_NT)
	CCFLAGS += -lgdi32 -lwinmm
else ifeq ($(UNAME_S),Darwin)
	CCFLAGS += -framework Cocoa -framework IOKit -framework OpenGL -framework CoreVideo -framework CoreAudio
endif

run: build/main
	build/main

build/main: src/*.c build
	gcc -o build/main src/main.c $(CCFLAGS)

basic: src/*.c build
	gcc -o build/basic src/examples/basic.c

generated_ui: src/*.c build
	gcc -o build/generated_ui src/examples/generated_ui.c $(CCFLAGS)

uitest: src/*.c build
	gcc -o build/uitest src/examples/uitest.c $(CCFLAGS)

uitest2: src/*.c build
	gcc -o build/uitest2 src/examples/uitest2.c $(CCFLAGS)

artifactui: src/*.c build
	gcc -o build/artifactui src/examples/artifactui.c $(CCFLAGS)

build:
	mkdir -p build
