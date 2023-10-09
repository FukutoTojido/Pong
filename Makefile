CC = g++
OBJS = main.o Game.o Object.o Ball.o
INC=-Isrc/include
LDFLAGS=-Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

all: produce
	./app

produce: $(OBJS)
	${CC} -o app $(OBJS) ${INC} ${LDFLAGS} 

Object.o: Object.cpp
	${CC} -c Object.cpp ${INC} ${LDFLAGS} 

%.o: %.cpp
	${CC} -c $< -o $@ ${INC} ${LDFLAGS} 

clean:
	rm *.o