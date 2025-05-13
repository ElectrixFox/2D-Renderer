CXX = gcc
CXXFLAGS = -g -Wall -I. -IInclude
APPNAME = main
LIBS = -L./lib -lglew32 -lopengl32 -lglfw3dll

SRCFILES := $(wildcard src/*.c)
OBJS := $(addprefix obj/, $(patsubst %.c, %.o, $(SRCFILES)))

obj/%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o obj/$(notdir $@) $^

all: $(OBJS)
	$(CXX) $(CXXFLAGS) obj/$(notdir $^) -o $(APPNAME) $(LIBS)