#ifndef _GREG_UTILS_H
#define _GREG_UTILS_H 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// parsing
char* read_text(char*);
char* hash_pw(char *);
char** split(char*, char);

//array
void free_arr(char**);
void print_arr(char **arr);
size_t array_size(char **arr);
// random
int grandom(int);
//server
void print_header(void);
int check_pass(char *user, char *pass, char *file);
#endif