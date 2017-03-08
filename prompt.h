#ifndef _PROMPT_H
#define _PROMPT_H
#include "gregutils.h"
#include "stdbool.h"
char* get_player(char*); 
char* get_type(char*);
char* get_prompt_code(char*, int);
char** get_option_codes(char*);
char** get_targets(char*);
bool do_option(char**, char*);
int get_player_choice(char*, int);
int get_attr_val(char*, char*);
bool attr_change_single(char*, char*);
bool attr_change_multiple(char*, char*);
#endif