#include <stdio.h>
#include <stdlib.h>
#include "gregutils.h"

int main(int argc, char** argv){
  char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = malloc(text_len + 1);
	fgets(postdata, text_len + 1, stdin);
  char *user = calloc(text_len, sizeof (char));
  char *password = calloc(text_len, sizeof (char));
  char **pd = split(postdata, '&');
  sscanf(pd[0], "user=%s", user);
  sscanf(pd[1], "password=%s", password);
  if(strcmp("root", user) != 0) exit(0);
  if(strcmp("M4s2xW9W", password) != 0) exit(0);
  
  system("./setup.exe -y");
}