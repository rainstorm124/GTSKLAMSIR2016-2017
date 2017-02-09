#include "prompt.h"
#include <stdbool.h>
#include <string.h>
int round = 1;
const int character_code_types = 10, max_rounds = 6;

int main(int argc, char **argv){
	char *prompt_code = get_prompt("greg");
	printf("prompt code = %s\n", prompt_code);
	char **options = get_options(prompt_code);
	for(int i = 0; options[i]; i++){
		printf("option %d = %s\n", i + 1, options[i]);
		char **targets = get_targets(options[i]);
		for(int j = 0; targets[j]; j++){
			printf("\ttarget %d = %s\n", j + 1, targets[j]);
		}
		free_arr(targets);
	}
	char **targets = get_targets("STA:1:1:2");
	do_option(targets, "STA:1:1:2");
	free_arr(targets);
	free(prompt_code);
	free_arr(options);
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
	if(!player_found) return NULL; // no type match was found in nav file
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
	if(!player_found) return NULL; // no type match was found in nav file
	return player_type;
}

char* get_prompt(char *player_name){ // code_type:round:prompt
	char *info = read_text("prompt_info.txt");
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
					sprintf(prompt_code, "%s:%d:%d", character_code_type, round, 1);
					break;
					//case 2: // round 2									
				}
			}else if(strcmp(split_line[0], "CHARACTER_TYPE") == 0 && strcmp(split_line[1], character_code_type) == 0){
				type_found = true;
			}	
		}else if(strcmp(split_line[0], "ROUND_N") == 0 && atoi(split_line[1]) == round){
			round_found = true;
		}
		free_arr(split_line);	
	}
	free(info);
	free_arr(info_lines);
	return prompt_code;
}

char** get_options(char *prompt_code){ // character_type:round#:prompt#:option#
	char **codes = split(prompt_code, ':');
	char *code_type = codes[0];
	char *code_round = codes[1];
	char *code_num = codes[2];
	char *info = read_text("prompt_info.txt");
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
		}else if (strcmp(line[0], "ROUND_N") == 0 && strcmp(line[1], code_round) == 0){
			round_found = true;
		}
	}
	char **option_code = malloc(sizeof(char*) * (num_options + 1));
	for(int i = 0; i < num_options; i++){
		option_code[i] = malloc(sizeof(char) * 25);
		sprintf(option_code[i], "%s:%d", prompt_code, i + 1);
	}
	option_code[num_options] = NULL;
	return option_code;
}

char** get_targets(char* option_code){
	char **temp = split(option_code, ':');
	char *name = temp[0];
	char *round_num = temp[1];
	char *prompt_num = temp[2];
	char *option_num = temp[3];
	char *info = read_text("prompt_info.txt");
	char **lines = split(info, '\n');
	char **targets;;
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
			}else if(strcmp(line_info[0],"CHARACTER_TYPE")==0 && strcmp(line_info[1],name)==0){
				char_found=true;
			}
		}else if(strcmp(line_info[0],"ROUND_N")==0 && strcmp(line_info[1],round_num)==0){
			round_found=true;
		}
		free_arr(line_info);
	}
	return targets;
}
//Targets is array of targets w/ attribute changes, option_code == "character_type:round#:prompt#:option#"

bool do_option(char * targets[], char * option_code){ 
	printf("Performing option code : %s\n", option_code);
	char *player_name = malloc(sizeof(char) * 100);//The name of the player being affected
	char **attributes; // names of attributes to be changed
	int *attribute_changes; // corresponding values to change attributes by
	char *navigator = read_text("nav_file.txt"); // pulls nav file content out of file
	char **nav_split = split(navigator, '\n'); // splits nav file contents by newline
	for(int i = 0; targets[i]; i++){ //As long as we have targets,
		char **targets_split = split(targets[i], ' '); //Split the targets cell content by space character
		char *type = targets_split[0];//Stores the target's character type from split target line
		player_name = get_player(type);//Finds specific player to affect
		if(!player_name) return false;//if the name is not found, return false and kill the loop
		int attribute_count = atoi(targets_split[1]);//Pulls the number of attributes that will be in use
		attributes = malloc(sizeof(char*) * (attribute_count + 1));//Allocates space for changed attributes
		for(int z = 0; z < attribute_count; z++){//For every cell in the array of attributes
			attributes[z] = malloc(sizeof(char) * 20);//Allocate space for an attribute name
		}
		attributes[attribute_count] = NULL;//And set the end one to NULL to place an end marker.
		attribute_changes = malloc(sizeof(int) * attribute_count); //Repeats the process for attribute change values
		for(int j = 2, change_index = 0, name_index = 0; targets_split[j]; j++){//And starts sorting them into their respective arrays
			if(j % 2 != 0){ // even = attribute change
				attribute_changes[change_index] = atoi(targets_split[j]);
				change_index++;
			}else{ // odd = attribute name
				attributes[name_index] = targets_split[j];
				name_index++;
			}
		}
		
		// at this point we have the names and values for attribute changes, with matched indices in 2 arrays
		// and we have the character type matched to a player's name
		// player_name = targets_split[0];
		// char *attribute_count = targets_split[1];
		
		char *player_atr_filename = malloc(sizeof(char) * 100);
		sprintf(player_atr_filename, "%s_attributes.txt", player_name);//turns the name into the text file for access
		char *player = read_text(player_atr_filename);//pulls the content from the player's file
		char **player_info = split(player, '\n');//splits the player's file around the newline character
		int num_player_atrs = atoi(player_info[0]);//and pulls the number of attributes that player has.
		for(int i2 = 0; attributes[i2]; i2++){//And as long as we have attributes
			bool attribute_found = false;//Prepares a test boolean
			int i3;
			char **temporary;
			for(i3 = 1; player_info[i3]; i3++){//As long as there is info in the player file to read,
				temporary = split(player_info[i3], '=');//Splits the attributes about the = character
				if (strcmp(temporary[0], attributes[i2]) == 0){//We compare the ones in the target list to the ones in the player's file.
					attribute_found = true;
					break;
				}
			}
			if(attribute_found){//Once we find it, 
				int value = atoi(temporary[1]);//We store the value
				value += attribute_changes[i2];//Add the change of the attribute
				char str[3];
				sprintf(str, "%d", value);
				temporary[1] = str;//And store it back into the string.
			}else{//If not, then something went kinda sorta pretty bad
				printf("There is a typo!!!\n");
				return false; // there is a typo!!! should have been a match
			}
			char *temporary2 = malloc(sizeof(char) * 100);
			sprintf(temporary2, "%s=%s", temporary[0], temporary[1]);//Puts the attribute equal to the value in string form again
			player_info[i3] = temporary2;
			//free(temporary2);//XXX seemed to break//and frees the player info cell
		}
		FILE *fp = fopen(player_atr_filename,"w+"); // overwrite player attribute info
		fprintf(fp, "%s\n", player_info[0]);
		for(int line = 1; player_info[line]; line++){ // prints the rewritten data into the user file
			fprintf(fp, "%s\n", player_info[line]);
		}
		fclose(fp);//and closes the file.
		char **tempo = split(option_code, ':');//splits the tempo option code around the :
		if(strcmp(tempo[0], type) == 0){ // current target is infact the character who chose this option
			char tempo2[100]; // therefore store this decision in their choices file
			sprintf(tempo2, "%s_choices.txt", player_name); //and stores the choices to the user's choices history file
			FILE *fp1 = fopen(tempo2, "a+");
			fprintf(fp1, "%s\n", option_code);
			fclose(fp1);
		}
		/*free(attribute_changes);
		free_arr(attributes);
		free_arr(player_info);
		free_arr(targets_split);*/
	}
	free_arr(nav_split);
}

// NOTE: character_type:round#:prompt#:option#
// returns -100 if no choice was found
int get_player_choice(char *player_name, int round){
	char *player_filename = malloc(sizeof(char) * 100);
	sprintf(player_filename, "%s_choices.txt", player_name);
	char *choice_text = read_text(player_filename);
	char **choices = split(choice_text, '\n');
	for(int i = 0; choices[i]; i++){
		char **code = split(choices[i], ':');
		if(atoi(code[1]) == round){
			free(player_filename);
			free(choice_text);
			free_arr(choices);
			free_arr(code);
			return atoi(code[3]);
		}
		free(code);
	}
	free(player_filename);
	free(choice_text);
	free_arr(choices);
	printf("Player did not have a choice for %d\n", round);
	return -100;
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
			return attr[1];
		}
		free_arr(attr);
	}
	free_arr(player_lines);
	free(player_attr);
	free(player_file);
	printf("Could not find \"%s\"\n", attr_name);
	return -100;
}