# Makefile
# created apr 30 2024
# by catroidvania

MAKE = make
SRCDIR = src
BINDIR = bin
OUTFILE = cetris

export OUTFILE


all:
	${MAKE} -C ${SRCDIR}
	mv ${SRCDIR}/${OUTFILE} ${BINDIR}/${OUTFILE}
	${MAKE} -C ${SRCDIR} clean

clean:
	${MAKE} -C ${SRCDIR} clean
	rm ${BINDIR}/${OUTFILE}
