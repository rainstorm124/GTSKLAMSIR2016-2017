#include "prompt.h"
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv){
	char *prompt_code = get_prompt_code("greg", 1);
	printf("prompt code = %s\n", prompt_code);
	char **options = get_option_codes(prompt_code);
	for(int i = 0; options[i]; i++){
		printf("option %d = %s\n", i + 1, options[i]);
		char **targets = get_targets(options[i]);
		for(int j = 0; targets[j]; j++){
			printf("\ttarget %d = %s\n", j + 1, targets[j]);
		}
		free_arr(targets);
	}
	char **targets = get_targets("greg:1:1:2");
	do_option(targets, "greg:1:1:2");
	free_arr(targets);
	free(prompt_code);
	free_arr(options);
	
	attr_change_multiple("2_RANDOM_NKVDO 1 2 3", "bob");
	
	return 0;
}

char* get_player(char *type){
	char *player_name = malloc(sizeof(char) * 100);
	char *navigator = read_text("nav_file.txt");
	char **nav_split = split(navigator, '\n');
	bool player_found = false;
	for(int j = 0; nav_split[j]; j++){ // find the player from the given type (target)
		char **nav_line = split(nav_split[j], '=');
		if(strcmp(nav_line[1], type) == 0){
			player_found = true;
			player_name = nav_line[0];
		}
	}
	free(navigator);
	free_arr(nav_split);
	if(!player_found){
		printf("Type not found!\n");
		return NULL; // no type match was found in nav file
	}
	return player_name;
}

char* get_type(char *player){
	char *player_type = malloc(sizeof(char) * 100);
	char *navigator = read_text("nav_file.txt");
	char **nav_split = split(navigator, '\n');
	bool player_found = false;
	for(int j = 0; nav_split[j]; j++){ // find the player from the given type (target)
		char **nav_line = split(nav_split[j], '=');
		if(strcmp(nav_line[0], player) == 0){
			player_found = true;
			player_type = nav_line[1];
		}
	}
	free(navigator);
	free_arr(nav_split);
	if(!player_found){
		printf("Player not found!\n");
		return NULL; // no type match was found in nav file
	}
	return player_type;
}

char* get_prompt_code(char *player_name, int round){ // player_name:round:prompt
	char *prompt_info_filename = malloc(sizeof(char) * 50);
	sprintf(prompt_info_filename, "prompt_%d_info.txt", round);
	char *info = read_text(prompt_info_filename);
	free(prompt_info_filename);
	char **info_lines = split(info, '\n');
	char *character_code_type = get_type(player_name);
	bool round_found = false, type_found = false;
	char *prompt_code = malloc(sizeof(char) * 100);
	for(int i = 0; info_lines[i]; i++){ // loop through lines of prompt_info.txt
		char *line = info_lines[i];
		char **split_line = split(line, '=');
		if(round_found){
			if(type_found){
				switch(round){
					case 1: // round 1
					sprintf(prompt_code, "%s:%d:%d", player_name, round, 1);
					goto code_found_break;
					//case 2: // round 2									
				}
			}else if(strcmp(split_line[0], "CHARACTER_TYPE") == 0 && strcmp(split_line[1], character_code_type) == 0){
				type_found = true;
			}	
		}else if(strcmp(split_line[0], "ROUND") == 0 && atoi(split_line[1]) == round){
			round_found = true;
		}
		free_arr(split_line);	
	}
	code_found_break:
	free(info);
	free(character_code_type);
	free_arr(info_lines);
	return prompt_code;
}

char** get_option_codes(char *prompt_code){ // player_name:round#:prompt#:option#
	char **codes = split(prompt_code, ':');
	char *code_type = get_type(codes[0]);
	char *code_round = codes[1];
	char *code_num = codes[2];
	char *prompt_info_filename = malloc(sizeof(char) * 50);
	sprintf(prompt_info_filename, "prompt_%s_info.txt", code_round);
	char *info = read_text(prompt_info_filename);
	free(prompt_info_filename);
	char **lines = split(info, '\n');
	bool round_found = false;
	bool chartype_found = false;
	int num_options;
	for(int i = 0; lines[i]; i++){
		char **line = split(lines[i], '=');
		if(round_found){
			if(chartype_found){
				if(strcmp(line[0],"NUM_OPTIONS")==0){
					num_options = atoi(line[1]);
					break;
				}
			}else if(strcmp(line[0], "CHARACTER_TYPE") == 0 && strcmp(line[1], code_type)==0){
				chartype_found = true;
			}
		}else if (strcmp(line[0], "ROUND") == 0 && strcmp(line[1], code_round) == 0){
			round_found = true;
		}
	}
	char **option_code = malloc(sizeof(char*) * (num_options + 1));
	for(int i = 0; i < num_options; i++){
		option_code[i] = malloc(sizeof(char) * 25);
		sprintf(option_code[i], "%s:%d", prompt_code, i + 1);
	}
	option_code[num_options] = NULL;
	free(code_type);
	return option_code;
}

char** get_targets(char* option_code){
	char **temp = split(option_code, ':');
	char *name = temp[0];
	char *character_type = get_type(name);
	char *round_num = temp[1];
	char *prompt_num = temp[2];
	char *option_num = temp[3];
	char *prompt_info_filename = malloc(sizeof(char) * 50);
	sprintf(prompt_info_filename, "prompt_%s_info.txt", round_num);
	char *info = read_text(prompt_info_filename);
	free(prompt_info_filename);
	char **lines = split(info, '\n');
	char **targets;
	bool round_found = false, char_found = false, prompt_found = false, option_found = false, num_targets_found = false;
	int options = 0;
	int target_count = 0;
	int i;
	for(i = 0; lines[i]; i++){
		char *line = lines[i];
		char **line_info = split(lines[i], '=');
		if(round_found){
			if(char_found){
				char *prompt_compare = malloc(sizeof(char) * 100);
				sprintf(prompt_compare, "PROMPT_%s", prompt_num);
				if(prompt_found){
					char *option_compare = malloc(sizeof(char) * 100);
					sprintf(option_compare, "OPTION_%s", option_num);
					if(option_found){
						if(num_targets_found){
							for (int j = 0; j < target_count && lines[i]; j++, i++){
								targets[j] = malloc(sizeof(char) * 30);
								line_info = split(lines[i], '=');
								targets[j] = line_info[1];
							}
							targets[target_count] = NULL;
							break;
						}else if (strcmp(line_info[0], "NUM_TARGETS")==0){
							target_count = atoi(line_info[1]);
							targets = malloc(sizeof(char*) * (target_count + 1));
							num_targets_found = true;
						}	
					}else if (strcmp(line_info[0], option_compare) == 0){
						//free(option_compare);
						option_found = true;
					}
				}else if(strcmp(line_info[0], prompt_compare)==0){
					//free(prompt_compare);
					prompt_found = true;
					
				}
			}else if(strcmp(line_info[0], "CHARACTER_TYPE")==0 && strcmp(line_info[1], character_type)==0){
				char_found=true;
			}
		}else if(strcmp(line_info[0], "ROUND")==0 && strcmp(line_info[1], round_num)==0){
			round_found=true;
		}
		free_arr(line_info);
	}
	free(character_type);
	return targets;
}
//Targets is array of targets w/ attribute changes, option_code == "player_name:round#:prompt#:option#"

bool attr_change_single(char *target, char *player_name){
	char *player_atr_filename = malloc(sizeof(char) * 100);
	sprintf(player_atr_filename, "%s_attributes.txt", player_name);
	char **targets_split = split(target, ' ');
	char **attributes; // names of attributes to be changed
	int *attribute_changes; // corresponding values to change attributes by
	
	/* store pair attribute changes */
	int attribute_count = atoi(targets_split[1]);//Pulls the number of attributes that will be in use
	attributes = malloc(sizeof(char*) * (attribute_count + 1));
	for(int z = 0; z < attribute_count; z++){
		attributes[z] = malloc(sizeof(char) * 20);
	}
	attributes[attribute_count] = NULL;
	attribute_changes = malloc(sizeof(int) * attribute_count);
	for(int j = 2, change_index = 0, name_index = 0; targets_split[j]; j++){//And starts sorting them into their respective arrays
		if(j % 2 != 0){ // even = attribute change
			attribute_changes[change_index] = atoi(targets_split[j]);
			change_index++;
		}else{ // odd = attribute name
			attributes[name_index] = targets_split[j];
			name_index++;
		}
	}
	char *player_text = read_text(player_atr_filename);
	
	/* make changes in player's file */
	char **player_info = split(player_text, '\n');
	if(!player_info[0]) printf("error in player file\n");
	int num_player_atrs = atoi(player_info[0]);//and pulls the number of attributes that player has.
	// loop through names of attributes to be changed
	for(int i2 = 0; attributes[i2]; i2++){
		bool attribute_found = false;
		char **old_attr_line;
		int i3;
		for(i3 = 1; player_info[i3]; i3++){
			old_attr_line = split(player_info[i3], '=');
			if (strcmp(old_attr_line[0], attributes[i2]) == 0){
				// correct attr in player's file found, index i3 recorded
				attribute_found = true;
				break;
			}
			
		}
		if(attribute_found){
			int value = atoi(old_attr_line[1]);//We store the value
			value += attribute_changes[i2];//Add the change of the attribute
			char str[10];
			sprintf(str, "%d", value);
			old_attr_line[1] = str;//And store it back into the string.
		}else{ // attr expecting to be changed was not found in player's file
			printf("attribute \"%s\" is not %s\n", attributes[i2], player_atr_filename);
			printf("There is a typo!!!\n");
			return false;
		}
		char *new_attr_line = malloc(sizeof(char) * 100);
		sprintf(new_attr_line, "%s=%s", old_attr_line[0], old_attr_line[1]);//Puts the attribute equal to the value in string form again
		player_info[i3] = new_attr_line;
		
		/*free(new_attr_line);
		free(old_attr_line)*/
	}

	/* overwrite player attr file with new numbers */
	FILE *fp = fopen(player_atr_filename, "w+");
	for(int line = 0; player_info[line]; line++){
		fprintf(fp, "%s\n", player_info[line]);
	}
	fclose(fp);
	// freeing section
	free_arr(player_info);
	free_arr(attributes);
	//free_arr(targets_split); // seems to break program
	free(attribute_changes);
	return true;
}

bool attr_change_multiple(char *target, char *player_name){
	char **targets_split = split(target, ' ');
	char *type = targets_split[0];
	char *nav_text = read_text("nav_file.txt");
	char **nav_lines = split(nav_text, '\n');
	char *im_opl_text = read_text("im-opl.txt");
	char **im_opl_lines = split(im_opl_text, '\n');
	char *stakw_im_text = read_text("stakw-im.txt");
	char **stakw_im_lines = split(stakw_im_text, '\n');
	char **players = malloc(sizeof(char*) * 100);
	if(strcmp(type, "ALL_OPL") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "OPL") == 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ALL_IM_UNDER_OPL") == 0){
		int j;
		for(int i = 0, j = 0; im_opl_lines[i]; i++){
			char **line = split(im_opl_lines[i], '=');
			if(strcmp(line[1], player_name) == 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ALL_IM") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "IM") == 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ALL_STAKW") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "STAKW") == 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ALL_STAKW_UNDER_OPL") == 0){
		int j;
		for(int i = 0, j = 0; im_opl_lines[i]; i++){
			char **line = split(im_opl_lines[i], '=');
			if(strcmp(line[1], player_name) == 0){
				for(int k = 0; stakw_im_lines[k]; k++){
					char **stakw_im_line = split(stakw_im_lines[i], '=');
					if(strcmp(stakw_im_line[1], line[0]) == 0){
						players[j] = malloc(sizeof(char) * 100);
						players[j] = line[0];
						j++;
					}
					
				}
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ALL_NKVDO") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "NKVDO") == 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ALL_OTHER_OPL") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "OPL") == 0 && strcmp(line[0], player_name) != 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ALL_OPL_IN_ALLIANCE") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "OPL") == 0 && get_attr_val(line[0], "IN_ALLIANCE") == 1){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ALL_OTHER_STAKW") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "STAKW") == 0 && strcmp(line[0], player_name) != 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ALL_STAKW_UNDER_IM") == 0){
		int j;
		for(int i = 0, j = 0; stakw_im_lines[i]; i++){
			char **line = split(stakw_im_lines[i], '=');
			if(strcmp(line[1], player_name) == 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "ASSOCIATED_OPL") == 0){
		// need to check if player is STAKW or IM
		for(int i = 0; nav_lines[i]; i++){
			char **nav_line = split(nav_lines[i], '=');
			if(strcmp(nav_line[0], player_name) == 0){
				if(strcmp(nav_line[1], "STAKW") == 0){
					for(int j = 0; stakw_im_lines[j]; j++){
						char **line = split(stakw_im_lines[j], '=');
						if(strcmp(line[0], player_name) == 0){
							for(int k = 0; im_opl_lines[k]; k++){
								char **im_opl_line = split(im_opl_lines[k], '=');
								if(strcmp(im_opl_line[0], line[1]) == 0){
									players[0] = malloc(sizeof(char) * 100);
									players[0] = im_opl_line[1];
									players[1] = NULL;
									free(line);
									break;
								}
								free(line);
							}							
						}
						free(line);
					}						
				}else if (strcmp(nav_line[1], "IM") == 0){
					for(int j = 0; im_opl_lines[j]; j++){
						char **line = split(im_opl_lines[j], '=');
						if(strcmp(line[0], player_name) == 0){
							players[0] = malloc(sizeof(char) * 100);
							players[0] = line[1];
							players[1] = NULL;
							free(line);
							break;
						}
						free(line);
					}	
				}
			}
				
		}
	}else if(strcmp(type, "ASSOCIATED_IM") == 0){
		// assume player is stakw
		for(int i = 0; stakw_im_lines[i]; i++){
			char **line = split(stakw_im_lines[i], '=');
			if(strcmp(line[1], player_name) == 0){
				players[0] = malloc(sizeof(char) * 100);
				players[0] = line[1];
				players[1] = NULL;
				free(line);
				break;
			}
			free(line);
		}
	}else if(strcmp(type, "BD_STAKW") == 0){
		// character type change
	}else if(strcmp(type, "ALL_BD") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "BD") == 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[j] = NULL;
	}else if(strcmp(type, "YEZ_NKVDO") == 0){
		// character type change
	}else if(strcmp(type, "YAG_NKVDO") == 0){
		// character type change
	}else if(strcmp(type, "2_RANDOM_NKVDO") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "NKVDO") == 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		int rand = random(j);
		players[0] = players[random(j)];
		players[1] = players[rand == 0 ? rand + 1 : rand - 1];
		players[2] = NULL;
	}else if(strcmp(type, "1_RANDOM_NKVDO") == 0){
		int i, j;
		for(i = 0, j = 0; nav_lines[i]; i++){
			char **line = split(nav_lines[i], '=');
			if(strcmp(line[1], "NKVDO") == 0){
				players[j] = malloc(sizeof(char) * 100);
				players[j] = line[0];
				j++;
			}
			free(line);
		}
		players[0] = players[random(j)];
		players[1] = NULL;
	}else if(strcmp(type, "INVESTIGATED_OPL") == 0){
		// investigations file
	}else if(strcmp(type, "INVESTIGATED_STAKW") == 0){
		// investigations file
	}else if(strcmp(type, "ALL_NKVDO_INVESTIGATORS") == 0){
		// investigations file
	}else {
		printf("type \"%s\" is not accounted for!\n", type);
	}
	for(int i = 0; players[i]; i++){
		printf("%d = %s\n", i, players[i]);
	}
	/*for(int i = 0; players[i]; i++){
		char *player_atr_filename_temp = malloc(sizeof(char) * 100);
		sprintf(player_atr_filename_temp, "%s_attributes.txt", players[i]);
		attr_change_single(target, player_atr_filename_temp);
		free(player_atr_filename_temp);
	}*/
	
	// above commented for testing purposes
	
	
}

bool do_option(char * targets[], char * option_code){
	printf("Performing option code : %s\n", option_code);
	char **option_codes = split(option_code, ':');
	char *player_name = option_codes[0];

	/* record choice in the choosing player's file*/
	char player_choices_filename[100];
	sprintf(player_choices_filename, "%s_choices.txt", player_name);
	FILE *fp1 = fopen(player_choices_filename, "a+");
	fprintf(fp1, "%s\n", option_code);
	fclose(fp1);
	//char *player_atr_filename = malloc(sizeof(char) * 100);
	//sprintf(player_atr_filename, "%s_attributes.txt", player_name);
	for(int i = 0; targets[i]; i++){
		char **targets_split = split(targets[i], ' '); // Split the targets cell content by space character
		char *type = targets_split[0];//Stores the target's character type from split target line
		
		if(strcmp(type, "YAG") == 0 || strcmp(type, "YEZ") == 0 || strcmp(type, "STA") == 0){
			player_name = get_player(type);
			//sprintf(player_atr_filename, "%s_attributes.txt", player_name);

			bool result = attr_change_single(targets[i], player_name);
			// XXX free rest of stuff
			//free(player_atr_filename);
			//free_arr(option_codes);
			if(!result){
				printf("error with %s\n", targets_split[0]);
				return false;
			}
		}else{
			bool result = attr_change_multiple(targets[i], player_name);
			// XXX free rest of stuff
			//free(player_atr_filename);
			//free_arr(option_codes);
			if(!result){
				printf("error with %s\n", targets_split[0]);
				return false;
			}
		}
		free_arr(targets_split);
		//free(player_atr_filename);
	}
	return true;
}

char *get_choice(char *player_name, int round){
	char *file_name = malloc(sizeof(char)*50);
	sprintf(file_name,"%s_choices.txt", player_name);
	char *player_choices = read_text(file_name);
	char **player_lines = split(player_choices, '\n');
	char *catch = malloc(sizeof(char)*10);
	catch = "ERROR";
	for (int i = 0; player_lines[i]; i++)
	{
		char ** split_option_code = split(player_lines[i], ':');
		if(atoi(split_option_code[1])==round){
			sprintf(catch, "%s:%s", split_option_code[2], split_option_code[3]);
			free_arr(split_option_code);
			break;
		}
		free_arr(split_option_code);
	}
	free(file_name);
	free(player_choices);
	free_arr(player_lines);
	return catch;
}

// returns -100 if no ATR was found
int get_attr_val(char *player_name, char * attr_name){
	char *player_file = malloc(sizeof(char) * 50);
	sprintf(player_file, "%s_attributes.txt", player_name);
	char *player_attr = read_text(player_file);
	char **player_lines = split(player_attr,'\n');
	for(int i = 1; player_lines[i]; i++){ // starting at 1 to skip number of attrs
		char **attr = split(player_lines[i], '=');
		if(strcmp(attr[0], attr_name) == 0){
			return atoi(attr[1]);
		}
		free_arr(attr);
	}
	free_arr(player_lines);
	free(player_attr);
	free(player_file);
	printf("Could not find \"%s\"\n", attr_name);
	return -100;
}
