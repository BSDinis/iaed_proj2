CC=gcc
CFLAGS= -g -ansi -pedantic -Wall -Werror -I.
#LDFLAGS= -pg

all: test_task test_input test_p_task test_lnkd_list test_hashtable

test_task: ../input.o ../task.o test_task.o

test_p_task: ../input.o ../p_task.o test_p_task.o ../task.o

test_lnkd_list: ../task.o ../p_task.o ../list.o ../l_item.o test_lnkd_list.o

test_hashtable:  ../task.o ../p_task.o ../list.o ../l_item.o ../hashtable.o ../ht_item.o  test_hashtable.o

test_input: ../input.o test_input.o

clean:
	@rm  *.o

clean-all: clean
	@rm -f test_task test_input test_p_task test_lnkd_list test_hashtable
