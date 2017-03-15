#ifndef _GREG_UTILS_H
#define _GREG_UTILS_H 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* read_text(char*);
char* hash_pw(char *);
char** split(char*, char);
void free_arr(char**);
void print_header(void);
void print_arr(char **arr);
int grandom(int);
int check_pass(char *user, char *pass, char *file);
#endif