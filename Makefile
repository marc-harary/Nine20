CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -g3
DEPS = Deque.h Hash.h
OBJ = Hash.o Deque.o Nine20.o

%.o: %.c ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

Nine20: ${OBJ}
	${CC} -o $@ $^ ${CFLAGS}

clean:
	rm -f Nine20 *.o

