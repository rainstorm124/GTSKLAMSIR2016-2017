//A file for functions concerning updating, checking player chosen counts, etc.

#include "prompt.h"
#include "gregutils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "prompt_chooser.h"


int main(int argc, char **argv){
	return 0;
}

bool add_update_to_queue(char* input_code)
{
	bool complete = false;
	FILE *file;
	while (file = fopen("lock_file.txt", "r"))
		fclose(file);
	file = fopen("lock_file.txt", "w");
	if(FILE *fp = fopen("update_file.txt", "a+")){
		fprintf(fp, "%s\n", input_code);
		if(count_players_chosen(fp) == MAX_PLAYERS){
			if(round==5){
				int stak_votes = 0;
				bool stak_vote_special = false;
				bool YEZ_favor_special = false;
				bool YEZ_cred_special = false;
				bool YAG_favor_special = false;
				bool YAG_cred_special = false;
			}
			char *raw_updates = malloc(sizeof(char) *1024 * 1024);
			raw_updates = read_text(fp);
			char **raw_updates_lines = split(raw_updates, '/n');
			char **targets_for_updates = malloc(sizeof(char) * 1024 * 1024);
			char **stakw_voters = malloc(sizeof(char)*100);
			for (int i = 0; raw_updates_lines[i]; i++)
			{
				if(round==5){
					char **split_update_line = split(raw_updates_lines, ':');
					char *choice_only_code = malloc(sizeof(char) * 100);
					char **stakw_player_name = malloc(sizeof(char)*100);
					sprintf(choice_only_code, "%s:%s:%s", split_update_line[1], split_update_line[2], split_update_line[3]);
					if(strcmp(get_type(split_update_line[0]), "STAKW") == 0 && strcmp(choice_only_code, "5:2:2")){
						stak_vote_special = true;
						strcpy(stakw_player_name[stak_votes], split_update_line[0]);
						strcpy(stakw_voters[stak_votes], raw_updates_lines[i]);
						stak_votes++;
						continue;
					}
					else if(strcmp(get_type(split_update_line[0]), "YEZ")==0 && strcmp(choice_only_code, "5:2:2")==0){
						YEZ_favor_special = true;
						continue;
					}
					else if(strcmp(get_type(split_update_line[0]), "YEZ")==0 && strcmp(choice_only_code, "5:2:3")==0){
						YEZ_cred_special = true;
						continue;
					}
					else if(strcmp(get_type(split_update_line[0]), "YAG")==0 && strcmp(choice_only_code, "5:2:2")==0){
						YAG_favor_special = true;
						continue;
					}
					else if(strcmp(get_type(split_update_line[0]), "YAG")==0 && strcmp(choice_only_code, "5:2:3")==0){
						YEZ_cred_special = true;
						continue;
					}
				}
				targets_for_updates = get_targets(raw_updates_lines[i]);
				do_option(targets_for_updates, raw_update_lines[i]);
				if(round==5){
					free_arr(split_update_line);
					free(choice_only_code);
				}
			}
			
			if(stak_vote_special == true)
				stak_vote(stak_votes, stakw_player_name, stakw_voters);
			else if(YEZ_favor_special == true)
				YEZ_favor_special();
			else if(YEZ_cred_special == true)
				YEZ_cred_special();
			else if(YAG_favor_special == true)
				YAG_favor_special();
			else if(YAG_cred_special == true)
				YAG_cred_special();
			
			complete = true;
			fclose(fp);
			//Clears update file
			fp = fopen("update_file.txt", "w");
			fclose(fp);
			free(raw_updates);
			free_arr(raw_updates_lines);
			free_arr(targets_for_updates);
		}
		fclose(file);
		unlink(file);
		complete = true;
	}
	if(complete != true)
		return false;
	else
		return complete;
}

bool admin_override(){
	bool updated = false;
	FILE *file;
	while (file = fopen("lock_file.txt", "r"))
		fclose(file);
	file = fopen("lock_file.txt", "w");
	if(FILE *fp = fopen("update_file.txt", "r")){
		//First, push updates in file
		char *raw_updates = malloc(sizeof(char) * 1024 * 1024);
		raw_updates = read_text(fp);
		char **raw_updates_lines
		char *raw_updates = malloc(sizeof(char) *1024 * 1024);
		raw_updates = read_text(fp);
		char **raw_updates_lines = split(raw_updates, '/n');
		char **targets_for_updates = malloc(sizeof(char) * 1024 * 1024);
		for (int i = 0; raw_updates_lines[i]; i++)
		{
			targets_for_updates = get_targets(raw_updates_lines[i]);
			do_option(targets_for_updates, raw_update_lines[i]);
		}

		fclose(fp);
		//Clears update file
		fp = fopen("update_file.txt", "w");
		fclose(fp);
		
		//Now make random updates. Taken from Greg's prompt.c mainline and repurposed. :P
		
		char **players = calloc(sizeof(char*), 400);
		char *nav_text = read_text("nav_file.txt");
		char **nav_lines = split(nav_text, '\n');
		int i = 0;
		for(;nav_lines[i]; i++){
		  if(nav_lines[i][0] == '\0') continue;
		  char **nav_line = split(nav_lines[i], '=');
		  if(!nav_line[0]) continue;
		  players[i] = calloc(sizeof(char), 100);
		  strcpy(players[i], nav_line[0]);
		  free_arr(nav_line);
		}
		for(int j = 0; players[j]; j++){
			char *prompt_code = get_prompt_code(players[j], round);
			char **options = get_option_codes(prompt_code);
			int option_count = 0;
			while(options[option_count]) option_count++;
			int random_option_choice = grandom(option_count);
			char **targets = get_targets(options[random_option_choice]);
			do_option(targets, options[random_option_choice]);
			free(prompt_code);
			free_arr(options);
			free_arr(targets);
		}
		updated = true;
	}
	return updated;
}

int count_players_chosen(FILE *fp)
{
	char* file_to_count = read_text(fp);
	int i = 0;
	char** file_lines = split(file_to_count, '/n');
	for (i = 0; file_lines[i]; i++)
		continue;
	return i;
}

//First counts then checks total of stakw chosen and all stakw overall.
bool stak_vote_special(int stak_votes, char **voter_codes, char **voter_names){
	bool success = false;
	int total = 0;
	char *nav = read_text("nav_file.txt");
	char **nav_lines = split(nav, '\n');
	char **stakw_players = malloc(sizeof(char)*300);
	for(int i = 0; nav_lines[i]; i++){
		char **split_line = split(nav_lines[i], '=');
		//CHECK IF NAME ON RIGHT OR LEFT
		if(strcmp(split_line[1], "STAKW")){
			strcpy(stakw_players, split_line[0]);
			total++;
		}
		else
			continue;
	}
	char **targets = malloc(sizeof(char)*30);
	char **targets_2= malloc(sizeof(char)*30);
	char **temporary = malloc(sizeof(char)*30);
	if((total/4) >= stak_votes){
		for(int j = 0; voter_names[j]; j++){
			char *poor_design = malloc(sizeof(char)*10);
			sprintf(targets[j], "%s 1 SUS -2", get_type(voter_names[j]));
		}
		for(int j = 0; targets[j]; j++){
			do_option(targets[j], voter_codes[j]);
		}
		for(int j = 0; stakw_players[j]; j++){
			int q = 0;
			char **targets = malloc(sizeof(char)*30);
			if(!is_player_choice(stakw_players[j], 5, "2:2"){
				sprintf(targets_2[q], "%s 1 SUS 3", get_type(stakw_players[j]));
				strcpy(temporary[q], stakw_players[j]);
			}
			else{
				continue;
			}
			q++;
		}
		for(int j = 0; targets_2[j]; j++){
			attr_change_single(targets[j], temporary[q]);
		}
		free(poor_design);
	}
	else if((total/4)<stak_votes){
		for(int i = 0; voter_codes[i]; i++){
			char *target = malloc(sizeof(char)*30);
			sprintf(target, "%s 1 GULAG 1", get_type(target));
		}
	}
}

void YEZ_favor_special(){
	char *YEZ_name = get_player("YEZ");
	int FAV_val = get_attr_val(YEZ_name, "FAV");
	if(FAV_val > 7){
		attr_change_multiple("YEZ_NKVDO", YEZ_name);
	}
	else
		attr_change_single("YEZ 1 GULAG 1", YEZ_name);
}

void YAG_favor_special(){
	char *YAG_name = get_player("YAG");
	int FAV_val = get_attr_val(YAG_name, "FAV");
	if(FAV_val > 7){
		attr_change_multiple("YAG_NKVDO", YAG_name);
	}
	else
		attr_change_single("YAG 1 GULAG 1", YAG_name);
}

void YEZ_cred_special(){
	char *YEZ_name = get_player("YEZ");
	int CRED_val = get_attr_val(YEZ_name, "CRED");
	if(CRED_val > 7){
		attr_change_single("YEZ 1 GULAG 1", YEZ_name);
	}
	else
		attr_change_single("YEZ 1 DEAD 1", YEZ_name);
}

void YAG_cred_special(){
	char *YAG_name = get_player("YAG");
	int CRED_val = get_attr_val(YAG_name, "CRED");
	if(CRED_val > 7){
		attr_change_single("YEZ 1 GULAG 1", YAG_name);
	}
	else
		attr_change_single("YAG 1 DEAD 1", YAG_name);
}