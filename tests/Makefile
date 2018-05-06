CC=gcc
CFLAGS= -g -ansi -pedantic -Wall -Werror -I.
#LDFLAGS= -pg

all: test_task test_input

test_task: ../task.o test_task.o

test_input: ../input.o test_input.o

clean:
	@rm  *.o

clean-all: clean
	@rm -f test_task test_input
