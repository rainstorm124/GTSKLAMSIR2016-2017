#ifndef _ZUTILS_H
#define _ZUTILS_H 1
#include "gregutils.h"
#include "prompt.h"
#include "prompt_chooser.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

const extern int character_type, max_rounds;
bool add_update_to_queue(char* option_code);
int count_players_chosen(char *fp);
void admin_override();
void stak_vote_special(int stak_votes, char **voter_codes, char **voter_names);
void YEZ_favor_special();
void YAG_favor_special();
void YEZ_cred_special();
void YAG_cred_special();
void lock(void);
void unlock(void);
int count_nav_lines(void);
char *get_user_choice(char *user);
#endif