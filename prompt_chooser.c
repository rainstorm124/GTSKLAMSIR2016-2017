#include "prompt_chooser.h"
#include "prompt.h"
#include "gregutils.h"

int main(int argc, char **argv){
	printf("game DEC = %f\n", get_DEC());
	return 0;
}

int get_prompt_num_STAKW(char *player_name, int round){
	switch(round){
		case 1:
		return 1;
		case 2:
		switch(get_player_choice(player_name, 2)){
			case 1: // player chose option 1 in round 1
			return 2; // the result is prompt 2
			case 2: // player chose option 2 in round 1
			return 3; // the result is prompt 3
			case 3: // player chose option 3 in round 1
			return 1; // the result is prompt 1
		}
		printf("problem in round 2 of STAKW!\n");
		break;
		case 3:
		if(get_attr_val(player_name, "SUS") > 7){
			return 1;
		}else if(get_attr_val(player_name, "FAT") > 5){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 4:
		if(get_attr_val(player_name, "PRES") > 7){
			return 1;
		}else if(get_attr_val(player_name, "HUNG") >= 5){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 5:
		if(get_attr_val(player_name, "FAT") > 5){
			return 1;
		}else if(get_attr_val(player_name, "SUS") > 6){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 6:
		// TODO add round 6 checks
		break;
	}
}

int get_prompt_num_EXK(char *player_name, int round){
	switch(round){
		case 1:
		return 1;
		case 2:
		if(get_attr_val(player_name, "HUNG") >= 5){
			return 1;
		}else if(get_attr_val(player_name, "LOY") >= 0 && get_attr_val(player_name, "LOY") <= 2){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 3:
		if(get_attr_val(player_name, "HUNG") >= 5){
			return 1;
		}else if(get_attr_val(player_name, "FAT") <= 2){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 4:
		if(get_attr_val(player_name, "PRES") >= 8){
			return 1;
		}else if(get_attr_val(player_name, "FAT") >= 5){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 5:
		if(get_attr_val(player_name, "HUNG") >= 8){
			return 1;
		}else if(get_attr_val(player_name, "PRES") <= 8){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 6:
		// TODO add round 6 checks
			break;
	}
}

int get_prompt_num_BD(char *player_name, int round){
	switch(round){
		case 1:
		return 1;
		case 2:
		if(get_attr_val(player_name, "HUNG") >= 5){
			return 1;
		}else if(get_attr_val(player_name, "PRES") >= 6){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 3:
		if(get_attr_val(player_name, "HUNG") >= 5){
			return 1;
		}else if(get_attr_val(player_name, "PRES") >= 6){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 4:
		if(get_attr_val(player_name, "HUNG") >= 5){
			return 1;
		}else if(get_attr_val(player_name, "LOY") <= 4){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 5:
		if(get_attr_val(player_name, "HUNG") >= 8){
			return 1;
		}else if(get_attr_val(player_name, "FAT") >= 8){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 6:
		// TODO add round 6 checks
			break;
	}
}

 //things that need to be fixed are marked with a ??
 int get_prompt_num_OPL(char *player_name, int round){	
	if(round==1)
	{
		return 1;
	}
	else if(round==2)
	{
		if(get_attr_val(player_name,"ALI")>1)//IM pres>4 then 1
		return 1;
		else if(get_attr_val(player_name,"PROD")<5 && get_attr_val(player_name,"PRES")>4)//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
	else if(round==3)
	{
		if(get_attr_val(player_name,"PROD") < get_DEC() || (get_attr_val(player_name,"SUS") > 7 && ))
		return 1;
		else if(get_attr_val(player_name,"PRES")>10)//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
	else if(round==4)
	{
	  if (get_attr_val(player_name,"ARRESTED")==1)
		return 3;//else then 3
      else if(get_attr_val(player_name,"PROD")<get_attr_val(get_attr_val(player_name,"EP"),"DEC") || get_attr_val(player_name,"SUS")>6)//Again, ask history people for last attr
		return 1;
	  else if(get_attr_val(player_name,"PRES")>10)//IM Sup>4 then 2
		return 2;
      else
      return 4;
	}
	else if(round==5)
	{
		if (get_attr_val(player_name,"ARRESTED")==1)
		return 3;//else then 3
		else if((get_attr_val(player_name,"PROD")<=get_attr_val(get_attr_val(player_name,"EP"),"DEC") ||get_attr_val(player_name,"SUS")>9) || get_attr_val(player_name,"PROD")<get_attr_val(get_attr_val(player_name,"EP"),"DEC")-1 ||get_attr_val(player_name,"SUS")>5)//IM pres>4 then 1
		return 1;
		else if(get_attr_val(player_name,"PRES")>12 || get_attr_val(player_name,"PRES")>8)//IM Sup>4 then 2
		return 2;
		else if
		return 4;//else then 3
	}
	else if(round==6)
	{
		if(get_choice(get_player("STA"),5)=="A2")//IM pres>4 then 1
		return 1;
		else if(get_attr_val(player_name,"ARRESTED")==1)//IM Sup>4 then 2
		return 3;
		else
		return 2;//else then 3
	}
 }

  int get_prompt_num_EP(char *player_name, int round)
 {
	
	if(round==1)
	{
		return 1;
	}
	else if(round==2)
	{
		if(get_attr_val(player_name,"DEC")>5)//IM pres>4 then 1
		return 1;
		else if(get_attr_val(player_name,"DEC")==5)//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
	else if(round==3)
	{
		if(get_DEC()>5)//IM pres>4 then 1
		return 1;
		else if(get_DEC()==5)//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
	else if(round==4)
	{
		if(get_attr_val(get_player("STA"),"ALI")>6 && (get_attr_val(player_name,"POL")<4 ))//Again, ask history people for last attr
		return 1;
		else if(get_attr_val(get_player("STA"),"ALI")<4 && (get_attr_val(player_name,"POL")>6 ))//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
	else if(round==5)
	{
		if((get_attr_val(get_player("STA"),"ALI")<4 && (get_attr_val(player_name,"POL")>6 )) || (get_attr_val(get_player("STA"),"ALI")>6 && (get_attr_val(player_name,"POL")<4 )) || get_attr_val(player_name,"SUS")>7)//IM pres>4 then 1
		return 1;
		else
		return 2;
	}
	else if(round==6)
	{
		if(get_choice(get_player("STA"),5)=="A2")//IM pres>4 then 1
		return 1;
		else if(get_attr_val(player_name,"ARRESTED")==1)//IM Sup>4 then 2
		return 3;
		else
		return 2;//else then 3
	}
 }

int get_prompt_num_IM(char *player_name, int round){	
	if(round==1)
	{
		return 1;
	}
	else if(round==2)
	{
		if(get_attr_val(player_name,"PRES")>4)//IM pres>4 then 1
		return 1;
		else if(get_attr_val(player_name,"SUP")>4)//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
	else if(round==3)
	{
		if(get_attr_val(player_name,"PROD")<get_DEC() || get_attr_val(player_name,"SUS")>7 || get_attr_val(player_name,"PRES")>10)
		return 1;
		else if(get_attr_val(player_name,"ALI")>1)//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
	else if(round==4)
	{
		if(get_attr_val(player_name,"ARR")==1 && (get_attr_val(player_name,"PROD")<get_DEC() || get_attr_val(player_name,"PRES")>10 ||get_attr_val(player_name,"SUS")>7))//Again, ask history people for last attr
		return 1;//?? stuff got added
		else if(get_attr_val(player_name,"ARR")==1)//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
	else if(round==5)
	{
		if(get_attr_val(player_name,"ARR")==0)//IM pres>4 then 1
		return 1;
		else if(get_attr_val(player_name,"ARR")==1)//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
	else if(round==6)
	{
		if(get_attr_val(player_name,"PRES")>4)//IM pres>4 then 1
		return 1;
		else if(get_attr_val(player_name,"SUP")>4)//IM Sup>4 then 2
		return 2;
		else
		return 3;//else then 3
	}
 }
 
 /*
 * prompt_chooser_rain.c
 *
 *  Created on: Feb 8, 2017
 *      Author: rcb
 */

int get_prompt_num_STA(char *player_name, int round){
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

int get_prompt_num_YAG(char *player_name, int round){
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

int get_prompt_num_YEZ(char *player_name, int round){
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

int get_prompt_num_NKVDO(char *player_name, int round)
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

double get_DEC(){
	char *nav_text = read_text("nav_file.txt");
	char **nav_lines = split(nav_text, '\n');
	char **players = malloc(sizeof(char*) * 100);
	int ep_count = 0, j;
	for(int i = 0, j = 0; nav_lines[i]; i++){
		char nav_line = split(nav_lines[i], '=');
		if(strcmp(nav_line[1], "EP"){
			players[j] = malloc(sizeof(char) * 100);
			players[j] = line[0];
			ep_count++;
			j++;
		}
		free_arr(nav_line);
	}
	players[j] = NULL;
	
	int DEC = 0;
	for(int i = 0; players[i]; i++){
		DEC += get_attr_val(players[i], "POL");
	}
	DEC /= ep_count;
	
	return DEC;
}