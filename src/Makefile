# src/Makefile
# created apr 30 2024
# by catroidvania

SRCS = main.cpp bitboard.cpp board.cpp piece.cpp
OBJS = $(SRCS:.cpp=.o)
# this isnt cross platform but we can figure that out later
CFLAGS = -std=c++17 -O2 -Wall -g3 -I/usr/local/Cellar/sdl2/2.30.2/include/SDL2 
CLIBS = -L/usr/local/Cellar/sdl2/2.30.2/lib -lSDL2
GPP = g++


all: obj
	${GPP} ${OBJS} -o ${OUTFILE} ${CLIBS}

obj: ${SRCS}
	${GPP} ${CFLAGS} -c ${SRCS} 

clean: ${OBJS}
	rm ${OBJS}
