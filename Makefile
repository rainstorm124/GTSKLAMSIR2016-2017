CC=gcc
all:test setup
test:prompt.o gregutils.o 
	$(CC) prompt.o gregutils.o -o test.exe
setup:setup.o gregutils.o linked_list.o
	$(CC) setup.o gregutils.o linked_list.o -o setup.exe