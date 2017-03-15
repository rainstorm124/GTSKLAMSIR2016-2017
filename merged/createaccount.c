#include "gregutils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int is_valid_game_key(char *user, char *key);

int main(int argc, char **argv){
  print_header();
  /// MAKE SURE THAT passwords.txt is WORLD WRITEABLE!
  // setup code
  char *user = calloc(1024 * 1024, sizeof(char));
  char *pass = calloc(1024 * 1024, sizeof(char));
  char *key = calloc(1024 * 1024, sizeof(char));

  char *len_ = getenv("CONTENT_LENGTH");
  long int len = strtol(len_, NULL, 10);
  char *postdata = malloc(len + 1);
  fgets(postdata, len + 1, stdin);

  char **arr = split(postdata, '&');
  sscanf(arr[0], "user=%s", user);
  sscanf(arr[1], "pass=%s", pass);
  sscanf(arr[2], "key=%s", key);
  
  //check if username is actually in the list of students (IMSA usernames)
  char *students = read_text("students.txt");
  char **studarr = split(students, '\n');
  bool user_found = false;
  if(!studarr[0]){
    puts("<html><head><title>ERROR 500 NO STUDENTS.TXT</title></head><body><h1>List of permissible usernames not found."
         "Contact your teacher or sysadmin for help.</h1>"
		     "<p>Click <a href='/greg/createaccount.html'>here</a> to return to the account creation page</p></body></html>");
    exit(0);
  }
  for(int i = 0; studarr[i]; i++){
	  if(strcmp(studarr[i], user) == 0){
      user_found = true;
      break;
    }    
  }
  if(!user_found){
    printf("<html><head><title>Bad Username</title></head><body><h1>\"%s\" is not a permissible username."
         "Try your IMSA username, or contact your teacher or sysadmin for help.</h1>"
		     "<p>Click <a href='/greg/createaccount.html'>here</a> to return to the account creation page</p></body></html>", user);
    exit(0);
  }
  free_arr(studarr);
  free(students);
  // check to see if the user is already registered
  char *pwtext = read_text("passwords.txt");
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
  
  if(!is_valid_game_key(user, key)){
    printf("<html><head><title>Invalid Game Key</title></head><body><h1>\"%s\" is an invalid game key."
           "Ask your teacher or sysadmin for help.</h1>"
           "<p>Click <a href='/greg/createaccount.html'>here</a> to return to the account creation page</p></body></html>", key);
    exit(0);
  }
  
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
  free(user);
  free(pass);
  free(key);
  exit(0);
}

int is_valid_game_key(char *user, char *key){
  char *enrollment_key_text = read_text("enrollment_file.txt");
  char **enrollment_key_lines = split(enrollment_key_text, '\n');
  for(int i = 0; enrollment_key_lines[i]; i++){
    char **line = split(enrollment_key_lines[i], ',');
    if(enrollment_key_lines[i][0] == '\0') continue;
    if(strcmp(line[0], user) == 0){
      if(strcmp(line[1], key) == 0){
        free(enrollment_key_text);
        free_arr(enrollment_key_lines);
        return 1;
      }
    }
    free_arr(line);
  }
  free(enrollment_key_text);
  free_arr(enrollment_key_lines);
  return 0;
}