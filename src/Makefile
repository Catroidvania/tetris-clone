# src/Makefile
# created apr 30 2024
# by catroidvania

# can we keep everything after main in alphabetical order?
SRCS = main.c app.c assets.c bitboard.c block.c board.c bot.c game.c gamepad.c movegen.c pieces.c rng.c rendering.c selector.c
OBJS = $(SRCS:.c=.o)
# this isnt cross platform but we can figure that out later!
CFLAGS = -std=c99 -O2 -Wall -g3 -I/usr/local/Cellar/sdl2/2.30.2/include/SDL2 -I/usr/include/SDL2 -I/usr/local/Cellar/sdl2_image/2.0.5/include/SDL2 -I/Library/Frameworks/SDL2_mixer.framework/Headers
CLIBS = -L/usr/local/Cellar/sdl2/2.30.2/lib -L/usr/local/Cellar/sdl2_image/2.0.5/lib -L/user/local/lib -lSDL2 -lSDL2_image -lSDL2_mixer
CC = gcc


all: obj
	${CC} ${OBJS} -o ${OUTFILE} ${CLIBS}

obj: ${SRCS}
	${CC} ${CFLAGS} -c ${SRCS} 

clean:
	rm ${OBJS}
