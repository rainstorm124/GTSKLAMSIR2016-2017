#include "prompt_chooser.h"

int get_prompt_num_STAKW(char *player_name, int round){
	switch(round){
		case 1:
		return 1;
		case 2:
		switch(get_player_choice(player_name, 2)){
			case 1: // player chose option 1 in round 1
			return 2 // the result is prompt 2
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
		}else if(get_attr_val(player_name, "HUN") >= 5){
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
		if(get_attr_val(player_name, "HUN") >= 5){
			return 1;
		}else if(get_attr_val(player_name, "LOY") >= 0 && get_attr_val(player_name, "LOY") <= 2){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 3:
		if(get_attr_val(player_name, "HUN") >= 5){
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
		if(get_attr_val(player_name, "HUN") >= 8){
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
		if(get_attr_val(player_name, "HUN") >= 5){
			return 1;
		}else if(get_attr_val(player_name, "PRES") >= 6){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 3:
		if(get_attr_val(player_name, "HUN") >= 5){
			return 1;
		}else if(get_attr_val(player_name, "PRES") >= 6){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 4:
		if(get_attr_val(player_name, "HUN") >= 5){
			return 1;
		}else if(get_attr_val(player_name, "LOY") <= 4){
			return 2;
		}else{ // other criteria are not met
			return 3;
		}
		case 5:
		if(get_attr_val(player_name, "HUN") >= 8){
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