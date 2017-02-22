/*
 * prompt_chooser_rain.c
 *
 *  Created on: Feb 8, 2017
 *      Author: rcb
 */

int prompt_chooser_STA(int round, char * player_name){
	int prompt_number = 3;
	switch (round);
	case 2:
		if(get_attr_val(get_player("YEZ"), "POW")<3 && get_attr_val(get_player("YAG"), "SUS")>=6)
			prompt_number = 1;
		else if(get_attr_val(player_name, "FEAR")>= 7 && prompt_number != 1)
			prompt_number = 2;
		break;
	case 3:
		prompt_number = 1;
		break;
	case 4:
		if((strcmp(get_choice(player_name, round-1), "1:2")==0)||(strcmp(get_choice(player_name, round-1), "1:3")))
			prompt_number = 1;
		else
			prompt_number = 2;
		break;
	case 5:
		if((strcmp(get_choice(player_name, round-1), "2:2")==0))
			prompt_number = 1;
		else
			prompt_number = 2;
		break;
	case 6:
		break;
	return prompt_number;

}

int prompt_chooser_YAG(int round, char * player_name)
{
	int prompt_number = 3;
	switch(round);
	case 2:
		if(get_attr_val(player_name, "PRES")> 6 || get_attr_val(player_name, "SUS")>6)
			prompt_number = 1;
		else if(get_attr_val(player_name, "FAV")>7 || get_attr_val(player_name, "CRED")>7 && prompt_number!=1)
			prompt_number = 2;
		break;
	case 3:
		if(((strcmp(get_choice(get_player("STA"), round-1), "1:2"))==0)||(strcmp(get_choice(get_player("STA"), round-1), "1:3")))
			prompt_number = 1;
		else if(((strcmp(get_choice(get_player("YEZ"), round-1), "1:2")==0))||(strcmp(get_choice(get_player("YEZ"), round-1), "2:1")))
			prompt_number = 2;
		break;
	case 4:
		if(((strcmp(get_choice(get_player("YEZ"), round-1), "2:2")==0) || (strcmp(get_choice(get_player("YEZ"), round-1), "3:2")==0) ||
				(strcmp(get_choice(get_player("YEZ"), round-1), "3:3")==0)))
			prompt_number = 1;
		else if(get_attr_val(player_name, "ARRESTED")==1)
			prompt_number = 2;
		else if(get_attr_val(get_player("YEZ"), "ARRESTED")==1)
			prompt_number = 3;
		else
			prompt_number = 4;
		break;
	case 5:
		if((get_attr_val(player_name, "ARRESTED")==0) && (get_attr_val(get_player("YEZ"), "ARRESTED")==1))
			prompt_number = 1;
		else if(get_attr_val(player_name,"ARRESTED")==1)
			prompt_number = 2;
		break;
	case 6:
		break;
	return prompt_number;
}

int prompt_chooser_YEZ(int round, char * player_name)
{
	int prompt_number = 3;
	switch(round);
	case 2:
		if(get_attr_val(player_name, "FAV")>6 || get_attr_val(player_name, "CRED")>6)
			prompt_number = 1;
		else if(get_attr_val(player_name, "POW")>7 && prompt_number != 1)
			prompt_number = 2;
		break;
	case 3:
		if((strcmp(get_choice(get_player("STA"), round-1), "1:1")==0) || (strcmp(get_choice(get_player("STA"), round-1), "1:3")==0))
			prompt_number = 1;
		else if((strcmp(get_choice(player_name, round-1), "1:2")==0) || (strcmp(get_choice(player_name, round-1), "2:1")==0))
			prompt_number = 2;
		break;
	case 4:
		if((strcmp(get_choice(get_player("YAG"), round-1), "2:2"))==0)
			prompt_number = 1;
		else if(get_attr_val(get_player("YAG"), "ARRESTED" == 1))
			prompt_number = 2;
		else if(get_attr_val(get_player("YEZ"), "ARRESTED") == 1)
			prompt_number = 3;
		else
			prompt_number = 4;
		break;
	case 5:
		if(get_attr_val(player_name, "ARRESTED") == 0 && (get_attr_val(get_player("YAG"), "ARRESTED") == 1))
			prompt_number = 1;
		else if(get_attr_val(player_name, "ARRESTED") == 1)
			prompt_number = 2;
		break;
	case 6:
		break;
	return prompt_number;
}

int prompt_chooser_NKVDO(int round, char * player_name)
{
	int prompt_number = 3;
	switch(round);
	case 2:
		if(get_attr_val(player_name, "PROD")<4 || get_attr_val(player_name, "SUS")>7)
			prompt_number=1;
		else if(get_attr_val(player_name, "SUSP")<4 || get_attr_val(player_name, "CRED")>6 && prompt_number != 1)
			prompt_number=2;
		break;
	case 3:
		if(strcmp(get_choice(player_name, round-1), "2:1") == 0)
			prompt_number = 1;
		else if(strcmp(get_choice(player_name, round-1), "1:3") == 0)
			prompt_number = 2;
		break;
	case 4:
		prompt_number = 1;
		break;
	case 5:
		if(strcmp(get_choice(player_name, 3), "2:1") == 0)
			prompt_number = 1;
		else if((strcmp(get_choice(player_name, 3), "1:1")==0) || (strcmp(get_choice(player_name, 3), "1:3")==0))
			prompt_number = 2;
		break;
	case 6:
		break;
	return prompt_number;
}

char * get_choice(char * player_name, int round)
{
	char * file_name = malloc(sizeof(char)*50);
	sprintf(file_name,"%s_choices.txt", player_name);
	char * player_choices = read_text(file_name);
	char ** player_lines = split(player_choices, '\n');
	char * catch = malloc(sizeof(char)*10);
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
