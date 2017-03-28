CC=gcc
CFLAGS=-std=gnu99 -g -Wall -Iinclude
#tell the linker to look for libraries in the current directory
LDFLAGS=-L.
#tell the linker which libraries to use
LDLIBS=-lgreg -lcrypt -g -pthread
LIBG_OBJECTS=src/gregutils.o src/prompt.o src/prompt_chooser.o src/zutils.o

all: mainpage.cgi account.cgi libgreg.a createaccount.cgi\
user_interface.cgi user_choice.cgi forced_update.cgi\
setup.exe setup.cgi reset.cgi

libgreg.a: $(LIBG_OBJECTS)
	ar rcs $@ $^

player_choice.cgi: libgreg.a src/player_choice.o
	$(CC) $(LDFLAGS) -o player_choice.cgi src/player_choice.o $(LDLIBS)

forced_update.cgi: libgreg.a src/forced_update.o
	$(CC) $(LDFLAGS) -o forced_update.cgi src/forced_update.o $(LDLIBS)

mainpage.cgi:src/mainpage.o libgreg.a
	$(CC) $(LDFLAGS) -o mainpage.cgi src/mainpage.o $(LDLIBS)

account.cgi:src/account.o libgreg.a
	$(CC) $(LDFLAGS) -o account.cgi src/account.o $(LDLIBS)

createaccount.cgi: src/createaccount.o libgreg.a
	$(CC) $(LDFLAGS) -o createaccount.cgi src/createaccount.o $(LDLIBS)

user_interface.cgi: src/user_interface.o libgreg.a
	$(CC) $(LDFLAGS) -o user_interface.cgi src/user_interface.o $(LDLIBS)

user_choice.cgi: src/user_choice.o libgreg.a
	$(CC) $(LDFLAGS) -o user_choice.cgi src/user_choice.o $(LDLIBS)

setup.cgi: src/setup_cgi.o libgreg.a
	$(CC) $(LDFLAGS) -o setup.cgi src/setup_cgi.o $(LDLIBS)

reset.cgi: src/reset.o libgreg.a
	$(CC) $(LDFLAGS) -o reset.cgi src/reset.o $(LDLIBS)

clean:
	rm src/*.o *.cgi *.a *.exe

setup.exe:src/setup.o libgreg.a
	$(CC) $(LDFLAGS) src/setup.o -o setup.exe $(LDLIBS)
