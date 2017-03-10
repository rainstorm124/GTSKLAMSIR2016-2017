#include "gregutils.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
  print_header();
  /// MAKE SURE THAT passwords.txt is WORLD WRITEABLE!
  // setup code
  char *user = calloc(1024 * 1024, sizeof(char));
  char *pass = calloc(1024 * 1024, sizeof(char));
  
  char *len_ = getenv("CONTENT_LENGTH");
  long int len = strtol(len_, NULL, 10);
  char *postdata = malloc(len + 1);
  fgets(postdata, len + 1, stdin);

  char **arr = split(postdata, '&');
  sscanf(arr[0], "user=%s", user);
  sscanf(arr[1], "pass=%s", pass);
  //check if username is actually in the list of students (IMSA usernames)
  char *students = read_text("students.txt");
  char **studarr = split(students, '\n');
  char **s;
  for(s = studarr; *s; s++){
	  if(!strcmp(*s, user)) break;
  }
  if(!(*s)){
	puts("<html><head><title>Bad Username</title></head><body><h1>This is not a permissible username."
         "Try your IMSA username, or contact your teacher or sysadmin for help.</h1>"
		 "<p>Click <a href='/greg/createaccount.html'>here</a> to return to the account creation page</p></body></html>");
    exit(0);
  }
  free_arr(studarr);
  free(students);
  // check to see if the user is already registered
  char *pwtext = read_text("passwords.txt");
 // if(!pwtext) goto qwerty;
 // if(strlen(pwtext) < 4) goto frpwd;
  char **pwarr = split(pwtext, '\n');
  for(char **p = pwarr; *p; p++){
	  char **pswd_line = split(*p, '=');
	  if(!strcmp(pswd_line[0], user)){
		  printf("<html><head><title>Username Taken</title></head><body><h1>This username has already been taken."
               "Try your <strong>OWN</strong> IMSA username or ask your teacher or sysadmin for help.</h1>"
			   "<p>Click <a href='/greg/createaccount.html'>here</a> to return to the account creation page</p></body></html>");
		  free_arr(pswd_line);
		  exit(0);
	  }
	  free_arr(pswd_line);
  }
  free_arr(pwarr);
  //frpwd:
  free(pwtext);
  //qwerty:
  // username is valid and is free/open for the taking.
  // print a success message
  printf("<html><head>\n<title> Thanks </title> </head>\n<body><h1>Account creation successful, click "
	   "<a href='/cgi-bin/greg/mainpage.cgi'>here</a> to login.</h1></body></html>");
  // write to the file
  char *hash = hash_pw(pass);
  FILE *fp = fopen("passwords.txt", "a");
  fprintf(fp, "%s=%s\n", user, hash);
  fflush(fp);
  fclose(fp);
  fflush(stdout);
  //and that's a wrap
  exit(0);
}