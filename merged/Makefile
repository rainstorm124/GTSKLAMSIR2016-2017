CC=gcc
CFLAGS=-std=gnu99 -g
#tell the linker to look for libraries in the current directory
LDFLAGS=-L.
#tell the linker which libraries to use
LDLIBS=-lgreg -lcrypt -g
LIBG_OBJECTS=gregutils.o prompt.o prompt_chooser.o zoinka.o

all: mainpage.cgi account.cgi libgreg.a createaccount.cgi\
player_interface.cgi player_choice.cgi forced_update.cgi setup.exe\
admin_choice.cgi admin_interface.cgi

libgreg.a: $(LIBG_OBJECTS)
	ar rcs $@ $^

player_choice.cgi: libgreg.a player_choice.o
	$(CC) $(LDFLAGS) -o player_choice.cgi player_choice.o $(LDLIBS)

forced_update.cgi: libgreg.a forced_update.o
	$(CC) $(LDFLAGS) -o forced_update.cgi forced_update.o $(LDLIBS)
	
mainpage.cgi:mainpage.o libgreg.a
	$(CC) $(LDFLAGS) -o mainpage.cgi mainpage.o $(LDLIBS)

account.cgi:account.o libgreg.a
	$(CC) $(LDFLAGS) -o account.cgi account.o $(LDLIBS)
		
createaccount.cgi: createaccount.o libgreg.a
	$(CC) $(LDFLAGS) -o createaccount.cgi createaccount.o $(LDLIBS)
	
player_interface.cgi: player_interface.o libgreg.a
	$(CC) $(LDFLAGS) -o player_interface.cgi player_interface.o $(LDLIBS)
	
admin_interface.cgi: admin_interface.o libgreg.a
	$(CC) $(LDFLAGS) -o admin_interface.cgi admin_interface.o $(LDLIBS)
	
admin_choice.cgi: admin_choice.o libgreg.a
	$(CC) $(LDFLAGS) -o admin_choice.cgi admin_choice.o $(LDLIBS)
	
clean:
	rm *.o *.cgi *.a *.exe

setup.exe:setup.o gregutils.o linked_list.o prompt.o prompt_chooser.o
	$(CC) $(LDFLAGS) setup.o gregutils.o linked_list.o prompt.o prompt_chooser.o -o setup.exe $(LDLIBS)