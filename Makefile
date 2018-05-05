CC=gcc
CFLAGS= -g -ansi -pedantic -Wall -Werror -I.
#LDFLAGS= -pg

all: main

tests: test_task

main: main.o task.o

test_task: task.o test_task.o

clean:
	@rm  *.o

clean-all: clean
	@rm -f main test_task