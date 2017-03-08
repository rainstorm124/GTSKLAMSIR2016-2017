CC=gcc
CFLAGS=-std=gnu99
#tell the linker to look for libraries in the current directory
LDFLAGS=-L.
LIBG_OBJECTS=gregutils.o

all: mainpage.cgi account.cgi libgreg.a

libgreg.a: $(LIBG_OBJECTS)
        ar rcs $@ $^

mainpage.cgi:mainpage.o libgreg.a
        $(CC) $(LDFLAGS) -o mainpage.cgi mainpage.o -lgreg

account.cgi:account.o libgreg.a
        $(CC) $(LDFLAGS) -o account.cgi account.o -lgreg
clean:
        rm *.o *.cgi *.a