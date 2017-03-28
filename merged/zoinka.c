//A file for functions concerning updating, checking player chosen counts, etc.
#ifdef __unix__
#define _GNU_SOURCE
#include <pthread.h>
#define YIELD pthread_yield()
#else
#define YIELD
#endif
#include "zoinka.h"
int ZOINKA_main(int argc, char **argv){
	return 0;
}

int count_nav_lines(void){
  char *nav_text = read_text("nav_file.txt");
  char **nav_lines = split(nav_text, '\n');
  int lines = 0;
  for(;nav_lines[lines]; lines++);
  free_arr(nav_lines);
  free(nav_text);
  return lines;
}

bool add_update_to_queue(char* input_code) {
	bool complete = false;
  lock();
  FILE *fp;
	if(fp = fopen("update_file.txt", "a+")){
		fprintf(fp, "%s\n", input_code);
    int stak_votes = 0;
    bool stak_vote_specialP = false;
		bool YEZ_favor_specialP = false;
		bool YEZ_cred_specialP = false;
		bool YAG_favor_specialP = false;
		bool YAG_cred_specialP = false;
    
		if(count_players_chosen("update_file.txt") == count_nav_lines() ){
			char *raw_updates = read_text("update_file.txt");
			char **raw_updates_lines = split(raw_updates, '\n');
			char **targets_for_updates = calloc(sizeof(char*), 65500);
			char **stakw_voters = calloc(sizeof(char*),100);
			char **stakw_player_name = calloc(sizeof(char*), 100);
			for (int i = 0; raw_updates_lines[i]; i++){
				if(get_round()==5){
					char **split_update_line = split(raw_updates_lines[i], ':');
          char *player = split_update_line[0];
          
					if(is_player_type(player, "STAKW") && is_player_choice(player, 5, "2:2")){
						stak_vote_specialP = true;
						strcpy(stakw_player_name[stak_votes], player);
						strcpy(stakw_voters[stak_votes], raw_updates_lines[i]);
						stak_votes++;
					} else if(is_player_type(player, "YEZ") && is_player_choice(player, 5, "2:2")){
						YEZ_favor_specialP = true;
					} else if(is_player_type(player, "YEZ") && is_player_choice(player, 5, "2:3")){
						YEZ_cred_specialP = true;
					} else if(is_player_type(player, "YAG") && is_player_choice(player, 5, "2:2") ){
						YAG_favor_specialP = true;
					} else if(is_player_type(player, "YAG") && is_player_choice(player, 5, "2:3")){
						YAG_cred_specialP = true;
					}
          free_arr(split_update_line);
				}
				targets_for_updates = get_targets(raw_updates_lines[i]);
				do_option(targets_for_updates, raw_updates_lines[i]);
			}
			
			if(stak_vote_specialP)
				stak_vote_special(stak_votes, stakw_player_name, stakw_voters);
			else if(YEZ_favor_specialP)
				YEZ_favor_special();
			else if(YEZ_cred_specialP)
				YEZ_cred_special();
			else if(YAG_favor_specialP)
				YAG_favor_special();
			else if(YAG_cred_specialP)
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
		unlock();
		complete = true;
	}
	if(complete != true)
		return false;
	else
		return complete;
}
FILE* z_lock_file;

void lock(void){  
  while (!(z_lock_file = fopen("lock_file.txt", "wx")))YIELD;
}

void unlock(void){
  fclose(z_lock_file);
  unlink("lock_file.txt");
}

/// Force the round to advance and choose randomly for those who have not chosen.
bool admin_override(){
	bool updated = false;
	lock();
  FILE *fp;
  //First, push updates in file
  char *raw_updates = read_text("update_file.txt");
	char **raw_updates_lines = split(raw_updates, '\n');
	char **targets_for_updates;
	for (int i = 0; raw_updates_lines[i]; i++) {
	  targets_for_updates = get_targets(raw_updates_lines[i]);
		do_option(targets_for_updates, raw_updates_lines[i]);
    free_arr(targets_for_updates);
  }

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
		char *prompt_code = get_prompt_code(players[j], get_round());
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
  unlock();
	return updated;
}

int count_players_chosen(char *fname) {
	char* file_contents = read_text(fname);
	int i = 0;
	char** file_lines = split(file_contents, '\n');
	for (; file_lines[i]; i++);
  free_arr(file_lines);
  free(file_contents);
	return i;
}

//First counts then checks total of stakw chosen and all stakw overall.
bool stak_vote_special(int stak_votes, char **voter_codes, char **voter_names){
	bool success = false;
	int total = 0;
	char *nav = read_text("nav_file.txt");
	char **nav_lines = split(nav, '\n');
	char **stakw_players = calloc(sizeof(char*), 300);
	
  for(int i = 0; nav_lines[i]; i++){
		char **split_line = split(nav_lines[i], '=');
		//CHECK IF NAME ON RIGHT OR LEFT
		if(strcmp(split_line[1], "STAKW")){
			strcpy(stakw_players[i], split_line[0]);
			total++;
		}
    free_arr(split_line);
	}

	if((total/4) >= stak_votes){
		for(int j = 0; voter_names[j]; j++){
			attr_change_single("STAKW 1 SUS -2", voter_names[j]);
		}
		for(int j = 0; stakw_players[j]; j++){
			if(!is_player_choice(stakw_players[j], 5, "2:2")){
				attr_change_single("STAKW 1 SUS 3", stakw_players[j]);
			}
		}
	} else if((total/4)<stak_votes){
		for(int i = 0; voter_codes[i]; i++){
      attr_change_single("STAKW 1 GULAG 1", voter_names[i]);
		}
	}
}

void YEZ_favor_special(){
	char *YEZ_name = get_player("YEZ");
	int FAV_val = get_attr_val(YEZ_name, "FAV");
	if(FAV_val > 7){
		attr_change_multiple("YEZ_NKVDO", YEZ_name);
	} else attr_change_single("YEZ 1 GULAG 1", YEZ_name);
  free(YEZ_name);
}

void YAG_favor_special(){
	char *YAG_name = get_player("YAG");
	int FAV_val = get_attr_val(YAG_name, "FAV");
	if(FAV_val > 7){
		attr_change_multiple("YAG_NKVDO", YAG_name);
	} else attr_change_single("YAG 1 GULAG 1", YAG_name);
  free(YAG_name);
}

void YEZ_cred_special(){
	char *YEZ_name = get_player("YEZ");
	int CRED_val = get_attr_val(YEZ_name, "CRED");
	if(CRED_val > 7){
		attr_change_single("YEZ 1 GULAG 1", YEZ_name);
	} else attr_change_single("YEZ 1 DEAD 1", YEZ_name);
  free(YEZ_name);
}

void YAG_cred_special(){
	char *YAG_name = get_player("YAG");
	int CRED_val = get_attr_val(YAG_name, "CRED");
	if(CRED_val > 7){
		attr_change_single("YEZ 1 GULAG 1", YAG_name);
	} else attr_change_single("YAG 1 DEAD 1", YAG_name);
  free(YAG_name);
}

char *get_user_choice(char *user){
  char *update_text = read_text("update_file.txt");
  char **update_lines = split(update_text, '\n');
  free(update_text);
  char *code = NULL;
  for(size_t i=0; update_lines[i]; i++){
    if(*update_lines[i] == '\0' || *update_lines[i] == '\n') continue;
    char **line = split(update_lines[i], ':');
    if(!line[0] || line[0] == '\0'){
      free_arr(line);
      continue;
    }
    if(!strcmp(line[0], user)) {
      code = strdup(update_lines[i]);
      free_arr(line);
      break;
    }
    free_arr(line);
  }
  free_arr(update_lines);
  return code;
}