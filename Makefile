

CC				:= g++
INCLUDE_PATH	:= 
LIBS			:= -lGLESv2 -lglfw
CARGS			:= -c -g -ggdb $(INCLUDE_PATH)
LARGS			:= -g -ggdb $(INCLUDE_PATH)

.PHONY: build run gdb

out		:= run
objects	:= obj/main.o
objects	+= obj/window.o

build: $(objects)
	$(CC) $(LARGS) -o $(out) $^ $(LIBS)

obj/main.o: src/main.cpp
	$(CC) $(CARGS) -o $@ $<

obj/window.o: src/window.cpp
	$(CC) $(CARGS) -o $@ $<

run: build
	./$(out)

gdb: build
	gdb ./$(out)