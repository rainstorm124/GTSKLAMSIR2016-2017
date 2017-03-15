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
  print_header();
  //char *data;
  // the sysadmin is really paranoid -- Nick
  char *user = calloc(1024 * 1024, sizeof(char));
  char *pass = calloc(1024 * 1024, sizeof(char));
  
  char *len_ = getenv("CONTENT_LENGTH");
  long int len = strtol(len_, NULL, 10);
  char *postdata = malloc(len + 1);
  fgets(postdata, len + 1, stdin);

  //szRPLC_NA('&', ' ', postdata);
  char **arr = split(postdata, '&');
  sscanf(arr[0], "user=%s", user);
  sscanf(arr[1], "pass=%s", pass);
  
  //printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
  //puts("<html><head><TITLE>Account</TITLE></head>");
  //puts("<body><h3>Your account:</h3>");
  //data = strdup(getenv("QUERY_STRING"));
  if(postdata == NULL)
    puts("<p>Error! Error in passing data from form to script.</p>");
  else {
    fflush(stdout);
    // BECAUSE __THIS__ IS HOW sscanf WORKS!!!
    //szRPLC_NA('&', ' ', data);
    //IMPORTANT: YOU MUST ALLOCATE THE STRINGS BEFORE READING CHARACTERS INTO THEM!!!!!!!!!!!!!!!!!!!!
    //Post: ignore data, read from standard input (is the default for scanf): scanf("uname=%s&psw=%s", user, pass);
    //sscanf(data,"uname=%s psw=%s", user, pass);

    if(check_pass(user, pass, "passwords.txt")){
      if(strcmp(user, "klam") == 0){ // admin
        printf("<html><head><script type=\"text/javascript\">"
               "function loaded(e){ document.forms[0].submit.click();}"
               "</script></head><body onload=\"loaded();\"><h1>Loading..."
			         "</h1><br><form name='user' id='user' action='admin_interface_v1.cgi' "
			         "method='POST'><input type='hidden' name='user'"
               "value='%s'><input type='submit' name='submit' "
			         "value='Submit'></form></body></html>",user);
      }else{ // player
        printf("<html><head><script type=\"text/javascript\">"
               "function loaded(e){ document.forms[0].submit.click();}"
               "</script></head><body onload=\"loaded();\"><h1>Loading..."
			         "</h1><br><form name='user' id='user' action='player_interface_v2.1.cgi' "
			         "method='POST'><input type='hidden' name='user'"
               "value='%s'><input type='submit' name='submit' "
			         "value='Submit'></form></body></html>",user);
      }      
    }else {
      printf("<p> Invalid username or password<br /><a href='/cgi-bin/greg/mainpage.cgi'>Homepage</a></p>");
    }
  }
  puts("</body></html>");
  return 0;
}