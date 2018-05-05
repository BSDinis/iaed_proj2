CC=gcc
CFLAGS= -g -ansi -pedantic -Wall -Werror -I.
#LDFLAGS= -pg

all: test_task

test_task: ../task.o test_task.o

clean:
	@rm  *.o

clean-all: clean
	@rm -f test_task
