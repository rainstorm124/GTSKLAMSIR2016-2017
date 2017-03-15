CC=gcc
CFLAGS=-g -std=gnu99
all:test setup
test:test_prompt.o gregutils.o prompt.o prompt_chooser.o
	$(CC) test_prompt.o prompt.o gregutils.o prompt_chooser.o -o test.exe
setup:setup.o gregutils.o linked_list.o prompt.o prompt_chooser.o
	$(CC) setup.o gregutils.o linked_list.o prompt.o prompt_chooser.o -o setup.exe