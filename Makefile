CXX = gcc
CXXFLAGS = -g -Wall -I.
APPNAME = main
LIBS = -L./lib -lglew32 -lopengl32 -lglfw3dll

SRCFILES := $(wildcard src/*.c) main.c
OBJS := $(addprefix obj/, $(patsubst %.c, %.o, $(SRCFILES)))

obj/%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $(addprefix obj/, $(notdir $@)) $^

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(addprefix obj/, $(notdir $^)) -o $(APPNAME) $(LIBS)