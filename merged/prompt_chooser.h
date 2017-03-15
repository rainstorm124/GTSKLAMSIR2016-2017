#ifndef _PROMPT_CHOOSER_H
#define _PROMPT_CHOOSER_H 1
int get_prompt_num_STA(char*, int);
int get_prompt_num_YAG(char*, int);
int get_prompt_num_YEZ(char*, int);
int get_prompt_num_EP(char*, int);
int get_prompt_num_NKVDO(char*, int);
int get_prompt_num_OPL(char*, int);
int get_prompt_num_IM(char*, int);
int get_prompt_num_STAKW(char*, int);
int get_prompt_num_EXK(char*, int);
int get_prompt_num_BD(char*, int);

//utility functions -- really should go elsewhere
int is_player_choice(char *player_name, int round, char *choice);
int is_type_choice(char *player_type, int round, char *choice);
int is_player_type(char *player_name, char *type);
double get_DEC();
#endif