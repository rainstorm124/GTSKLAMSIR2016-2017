CC=gcc
CFLAGS=-g -std=gnu99
all:test setup dectest
test:test_prompt.o gregutils.o prompt.o
	$(CC) test_prompt.o prompt.o gregutils.o -o test.exe
setup:setup.o gregutils.o linked_list.o prompt.o
	$(CC) setup.o gregutils.o linked_list.o prompt.o -o setup.exe
dectest:prompt_chooser.o gregutils.o prompt.o
	$(CC) -g prompt_chooser.o prompt.o gregutils.o -o dectest.exe