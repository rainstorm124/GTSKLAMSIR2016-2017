#include "gregutils.h"
#include <stdio.h>

int main(int argc, char **argv){
	print_header();
	char *text = read_text("login.html");
	printf(text);
	free(text);
}