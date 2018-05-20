CC=gcc
CFLAGS= -g -ansi -pedantic -Wall -Werror -I. 
#LDFLAGS= -pg

all: main

main: main.o task.o input.o p_task.o l_item.o list.o ht_item.o hashtable.o planner.o cmd.h key_t.h 

clean:
	@rm  *.o

clean-all: clean
	@rm -f main
