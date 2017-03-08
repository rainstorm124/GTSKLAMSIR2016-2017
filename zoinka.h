#ifndef _ZOINKA_H
#define _ZOINKA_H
#include "gregutils.h"
#include "stdbool.h"
#include "prompt.h"
extern int round;
const extern int character_type, max_rounds;
char* add_update_to_queue(char* option_code);
int count_players_chosen(FILE *fp);
#endif