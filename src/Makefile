# src/Makefile
# created apr 30 2024
# by catroidvania

SRCS = main.cpp
OBJS = main.o
GPP = g++


all: obj
	${GPP} ${OBJS} -o ${OUTFILE}

obj: ${SRCS}
	${GPP} -c ${SRCS}

clean: ${OBJS}
	rm ${OBJS}
