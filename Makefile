CC=gcc
all:test setup dectest
test:prompt.o gregutils.o 
	$(CC) prompt.o gregutils.o -o test.exe
setup:setup.o gregutils.o linked_list.o
	$(CC) setup.o gregutils.o linked_list.o -o setup.exe
dectest:prompt_chooser.o gregutils.o prompt.o
	$(CC) prompt_chooser.o prompt.o gregutils.o -o dectest.exe