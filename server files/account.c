#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include "gregutils.h"
// zero terminated string non-allocating replace
void szRPLC_NA(char old, char cnew, char *str){
  while(*str){
    if(*str == old)*str = cnew;
    (void)*str++;
  }
}

int main(void) {
  char *data;
  // the sysadmin is really paranoid -- Nick
  char *user = calloc(1024 * 1024, sizeof(char));
  char *pass = calloc(1024 * 1024, sizeof(char));
  
  char *len_ = getenv("CONTENT_LENGTH");
  long int len = strtol(len_, NULL, 10);
  char *postdata = malloc(len + 1);
  fgets(postdata, len + 1, stdin);
  szRPLC_NA('&', ' ', postdata);
  sscanf(arr[0], "user=%s", user);
  sscanf(arr[1], "pass=%s", pass);
  
  
  //printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
  print_header();
  puts("<html><head><TITLE>Account</TITLE></head>");
  puts("<body><h3>Your account:</h3>");
  //data = strdup(getenv("QUERY_STRING"));
  if(postdata == NULL)
    puts("<p>Error! Error in passing data from form to script.</p>");
  else {
    fflush(stdout);
    // BECAUSE __THIS__ IS HOW sscanf WORKS!!!
    szRPLC_NA('&', ' ', data);
    //IMPORTANT: YOU MUST ALLOCATE THE STRINGS BEFORE READING CHARACTERS INTO THEM!!!!!!!!!!!!!!!!!!!!
    //Post: ignore data, read from standard input (is the default for scanf): scanf("uname=%s&psw=%s", user, pass);
    sscanf(data,"uname=%s psw=%s", user, pass);

    // please hash the passwords when you actually implement this. -- Nick
    if(strcmp(user,"user") == 0 && strcmp(pass,"pass") == 0)
      printf("<p> Hello %s</em></strong> </p>", user);
    else {
      printf("<p> Invalid username or password</p>");
    }
  }
  puts("</body></html>");
  return 0;
}
