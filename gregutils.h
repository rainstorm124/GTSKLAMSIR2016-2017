#ifndef _GREG_UTILS_H
#define _GREG_UTILS_H 1
#include <stdio.h>
#include <stdlib.h>
char* read_text(char*);
char** split(char*, char);
void free_arr(char**);
int grandom(int);
void print_header(void);
char* hash_pw(char *);
#endif