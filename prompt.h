#ifndef _PROMPT_H
#define _PROMPT_H
#include "gregutils.h"
#include "stdbool.h"
///
char* get_player(char*); 
char* get_type(char*);
char* get_prompt_code(char*, int);
char* get_choice(char *player_name, int round);
char* get_prompt_text(char *prompt_code);
char* get_option_text(char *option_code);

char** get_option_codes(char*);
char** get_targets(char*);
char** get_random_players(char *type, int num);
char** get_all_players_of_type(char *type);

int get_player_choice(char*, int);
int get_attr_val(char*, char*);
int get_round(void);

bool do_option(char**, char*);
bool attr_change_single(char*, char*);
bool attr_change_multiple(char*, char*);

void set_round(int round);
#endif