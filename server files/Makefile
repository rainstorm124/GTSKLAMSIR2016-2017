CC=gcc
CFLAGS=-std=gnu99
#tell the linker to look for libraries in the current directory
LDFLAGS=-L.
#tell the linker which libraries to use
LDLIBS=-lgreg -lcrypt
LIBG_OBJECTS=gregutils.o

all: mainpage.cgi account.cgi libgreg.a createaccount.cgi

libgreg.a: $(LIBG_OBJECTS)
	ar rcs $@ $^

mainpage.cgi:mainpage.o libgreg.a
	$(CC) $(LDFLAGS) -o mainpage.cgi mainpage.o $(LDLIBS)

account.cgi:account.o libgreg.a
	$(CC) $(LDFLAGS) -o account.cgi account.o $(LDLIBS)
		
createaccount.cgi: createaccount.o libgreg.a
	$(CC) $(LDFLAGS) -o createaccount.cgi createaccount.o $(LDLIBS)
	
rain.cgi: player_interface_v1.o libgreg.account
	$(CC) $(LDFLAGS) -o rain.cgi player_interface_v1.o $(LDLIBS)
clean:
	rm *.o *.cgi *.a