CC = g++
OBJS = main.o Game.o Object.o Ball.o Text.o
INC=-Isrc/include
LDFLAGS=-Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
CXXFLAGS=-std=c++17

all: produce
	./app

produce: $(OBJS)
	${CC} -o app $(OBJS) ${INC} ${LDFLAGS} ${CXXFLAGS}

# Object.o: Object.cpp
# 	${CC} -c Object.cpp ${INC} ${LDFLAGS} ${CXXFLAGS}

%.o: %.cpp
	${CC} -c $< -o $@ ${INC} ${LDFLAGS} ${CXXFLAGS}

clean:
	rm *.o