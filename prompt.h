#ifndef _PROMPT_H
#define _PROMPT_H
#include "gregutils.h"
#include "stdbool.h"
extern int round;
const extern int character_type, max_rounds;
char* get_player(char*);
char* get_type(char*);
char* get_prompt(char*);
char** get_options(char*);
char** get_targets(char*);
bool do_option(char**, char*);
#endif