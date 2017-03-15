#ifndef _ZOINKA_H
#define _ZOINKA_H
#include "gregutils.h"
#include "stdbool.h"
#include "prompt.h"
extern int round;
const extern int character_type, max_rounds;
bool add_update_to_queue(char* option_code);
int count_players_chosen(FILE *fp);
bool admin_override();
bool stak_vote_spcial(int stak_votes, char **voter_codes, char **voter_names);
void YEZ_favor_special();
void YAG_favor_special();
void YEZ_cred_special();
void YAG_cred_special();
#endif