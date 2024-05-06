# src/Makefile
# created apr 30 2024
# by catroidvania

SRCS = main.cpp bitboard.cpp board.cpp
OBJS = $(SRCS:.cpp=.o)
CFLAGS = -std=c++17 -O2 -Wall -g3
GPP = g++


all: obj
	${GPP} ${OBJS} -o ${OUTFILE}

obj: ${SRCS}
	${GPP} ${CFLAGS} -c ${SRCS}

clean: ${OBJS}
	rm ${OBJS}
