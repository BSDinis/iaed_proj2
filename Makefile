CC=gcc
CFLAGS= "-g" -ansi -pedantic -Wall -Werror -I. #-pg
#LDFLAGS= -pg

all: main

main: main.o task.o input.o p_task.o l_item.o list.o key_t.h ht_item.o hashtable.o planner.o

clean:
	@rm  *.o

clean-all: clean
	@rm -f main
