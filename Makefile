CC=gcc
CFLAGS= -g -ansi -pedantic -Wall -Werror -I.
#LDFLAGS= -pg

all: main

main: main.o task.o input.o dummy.o p_task.o l_item.o list.o key_t.h ht_item.o hashtable.o

clean:
	@rm  *.o

clean-all: clean
	@rm -f main
