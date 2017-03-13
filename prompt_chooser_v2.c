#include "prompt_chooser.h"
#include "prompt.h"
#include "gregutils.h"
#include <stdlib.h>

int get_prompt_num_STAKW(char *player_name, int round){
	
	char *previous_round_choice = get_choice(player_name, 1);
	int SUS_attr_val = get_attr_val(player_name, "SUS");
	int FAT_attr_val = get_attr_val(player_name, "FAT");
	int PRES_attr_val = get_attr_val(player_name, "PRES");
	int HUNG_attr_val = get_attr_val(player_name, "HUNG");
	char *STA_choice_r5 = get_choice(get_player("STA"), 5);
	
  switch(round){
  case 1:
    return 1;
  case 2:
    if(!strcmp(previous_round_choice, "1:1")){
      return 2;
    }else if(!strcmp(previous_round_choice, "1:2")){
      return 3;
    }else if(!strcmp(previous_round_choice, "1:3")){
      return 1;
    }
    printf("problem in round 2 of STAKW!\n");
    break;
  case 3:
    if(SUS_attr_val) > 7){
      return 1;
    }else if(FAT_attr_val > 5){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
  case 4:
    if(PRES_attr_val > 7){
      return 1;
    }else if(HUNG_attr_val >= 5){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
  case 5:
    if(FAT_attr_val > 5){
      return 1;
    }else if(SUS_attr_val > 6){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
  case 6:
    if(!strcmp(STA_choice_r5, 5), "1:2")){
      return 1;
    }else if(!strcmp(STA_choice_r5, 5), "1:1")){
      return 2;
    }else if(!strcmp(STA_choice_r5, 5), "1:3")
      || !strcmp(STA_choice_r5, 5), "2:1")
      || !strcmp(STA_choice_r5, 5), "2:2")
      || !strcmp(STA_choice_r5, "2:3")){
      return 3;
    }
    printf("problem in round 6 of STAKW!\n");
    break;
  }
  printf("PROBLEM IN STAKW");
  abort();
  return -1;
}

int get_prompt_num_EXK(char *player_name, int round){
	int HUNG_attr_val = get_attr_val(player_name, "HUNG");
	int LOY_attr_val = get_attr_val(player_name, "LOY");
	int FAT_attr_val = get_attr_val(player_name, "FAT");
	int PRES_attr_val = get_attr_val(player_name, "PRES");
	char *STA_choice_r5 = get_choice(get_player("STA"), 5)
	
  switch(round){
    case 1:
    return 1;
    case 2:
    if(HUNG_attr_val >= 5){
      return 1;
    }else if(LOY_attr_val >= 0 && LOY_attr_val <= 2){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
    case 3:
    if(HUNG_attr_val >= 5){
      return 1;
    }else if(FAT_attr_val <= 2){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
    case 4:
    if(PRES_attr_val >= 8){
      return 1;
    }else if(FAT_attr_val >= 5){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
    case 5:
    if(HUNG_attr_val >= 8){
      return 1;
    }else if(PRES_attr_val <= 8){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
    case 6:
    if(!strcmp(STA_choice_r5, "1:2")){
      return 1;
    }else if(!strcmp(STA_choice_r5, "1:1")){
      return 2;
    }else if(!strcmp(STA_choice_r5, "1:3")
      || !strcmp(STA_choice_r5, "2:1")
      || !strcmp(STA_choice_r5, "2:2")
      || !strcmp(STA_choice_r5, "2:3")){
      return 3;
    } 
    break;
  }
  printf("PROBLEM IN EXK\n");
  abort();
  return -1;
}

int get_prompt_num_BD(char *player_name, int round){
	int HUNG_attr_val = get_attr_val(player_name, "HUNG");
	int PRES_attr_val = get_attr_val(player_name, "PRES");
	int LOY_attr_val = get_attr_val(player_name, "LOY");
	int FAT_attr_val = get_attr_val(player_name, "FAT");
	char *STA_choice_r5 = get_choice(get_player("STA"), 5);
	
  switch(round){
    case 1:
    return 1;
    case 2:
    if(HUNG_attr_val >= 5){
      return 1;
    }else if(PRES_attr_val >= 6){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
    case 3:
    if(HUNG_attr_val >= 5){
      return 1;
    }else if(PRES_attr_val >= 6){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
    case 4:
    if(HUNG_attr_val >= 5){
      return 1;
    }else if(LOY_attr_val <= 4){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
    case 5:
    if(HUNG_attr_val >= 8){
      return 1;
    }else if(FAT_attr_val >= 8){
      return 2;
    }else{ // other criteria are not met
      return 3;
    }
    case 6:
    if(!strcmp(STA_choice_r5, "1:2")){
      return 1;
    }else if(!strcmp(STA_choice_r5, "1:1")){
      return 2;
    }else if(!strcmp(STA_choice_r5, "1:3")
      || !strcmp(STA_choice_r5, "2:1")
      || !strcmp(STA_choice_r5, "2:2")
      || !strcmp(STA_choice_r5, "2:3")){
      return 3;
    } 
    break;
  }
  printf("PROBLEM IN BD\n");
  abort();
  return -1;
}

 int get_prompt_num_OPL(char *player_name, int round){
	 int ALL_atr_val = get_attr_val(player_name,"ALL");
	 int PROD_attr_val = get_attr_val(player_name,"PROD");
	 int PRES_attr_val = get_attr_val(player_name,"PRES");
	 int SUS_attr_val = get_attr_val(player_name,"SUS");
	 int player_arrested = get_attr_val(player_name, "ARRESTED");
	 int player_alliance = get_attr_val(player_name, "IN_ALLIANCE");
	 char *STA_choice_r4 = get_choice(get_player("STA"),4);
	 char *STA_choice_r5 = get_choice(get_player("STA"),5);
	 
  switch(round){
  case 1:
    return 1;
  case 2:
    if(ALL_atr_val>1)
      return 1;
    else if(PROD_attr_val<5 && PRES_attr_val>4)
      return 2;
    else
      return 3;
  case 3:
    if((PROD_attr_val < get_DEC() || SUS_attr_val > 7) && player_alliance==0)
      return 1;
    else if(PRES_attr_val>10)
      return 2;
    else if((PROD_attr_val < get_DEC() || SUS_attr_val > 7) && player_alliance==1)
      return 4;
    else
      return 3;
  case 4:
    if (player_arrested==1)
      return 3;
    else if((PROD_attr_val<get_DEC() || SUS_attr_val > 6) && player_alliance==0)//Again, ask history people for last attr
      return 1;
    else if(PRES_attr_val>10)
      return 2;
    else if((PROD_attr_val<get_DEC() || SUS_attr_val>6) && player_alliance==1)
      return 5;
    else
      return 4;
  case 5:
    if (player_arrested==1)
      return 3;
    // XXX: WARNING MUST CHECK
    else if((((PROD_attr_val<get_DEC()+1 ||SUS_attr_val>9)&& strcmp(STA_choice_r4,"2:2")==0)
        || (PROD_attr_val<get_DEC()-1 ||SUS_attr_val>5) && strcmp(STA_choice_r4,"2:2")!=  0) && player_alliance==0)
    //      ((OPL                 Prod<EP+1 Dec             or              OPL Sus>9)          AND Stalin chose B2 in round 4)            or ((OPL Prod<EP-1 Dec                          or OPL Sus>5)                        AND Stalin didn’t choose B2 in round 4)     AND IN_ALLIANCE=false
      return 1;
    else if(PRES_attr_val>12 || PRES_attr_val>8)//IM Sup>4 then 2
      return 2;
    else if((((PROD_attr_val<=get_DEC()+1 ||SUS_attr_val>9)&& strcmp(STA_choice_r4,"2:2")==0)
      || (PROD_attr_val<get_DEC()-1 || SUS_attr_val>5) && strcmp(STA_choice_r4,"2:2")!=0) && player_alliance==1)
      return 5;
    else
      return 4;
  case 6:
    if(strcmp(STA_choice_r5, "1:2")==0)
      return 1;
    else if(player_arrested==1)
      return 3;
    else
      return 2;
  }
  printf("PROBLEM IN OPL\n");
  abort();
  return -1;
 }

int get_prompt_num_EP(char *player_name, int round) {
  int sta_ali = get_attr_val(get_player("STA"),"ALI");
  int player_pol = get_attr_val(player_name,"POL");
  int player_sus = get_attr_val(player_name,"SUS");
  int dec = get_DEC();
  int player_arrested = get_attr_val(player_name, "ARRESTED");
  char *STA_choice_r5 = get_choice(get_player("STA"), 5);
  
  switch(round){
    case 1: 
      return 1;
    case 2:
      if(dec > 5) return 1;
      else if(dec == 5) return 2;
      else return 3;
    case 3:
      if(dec > 5) return 1;
      else if(dec == 5) return 2;
      else return 3;
    case 4:
      if(sta_ali >6 && player_pol < 4 )return 1;
      else if (sta_ali < 4 && player_pol > 6) return 2;
      else return 3;
    case 5:
      if( (sta_ali < 4 && player_pol > 6) || (sta_ali > 6 && player_pol < 4) || player_sus) return 1;
      else return 2;
    case 6:
      if(!strcmp(STA_choice_r5, "1:2") ) return 1;
      else if (player_arrested==1) return 3;
      else return 2;
  }
  printf("PROBLEM IN EP\n");
  abort();
  return -1;
}

int get_prompt_num_IM(char *player_name, int round){
  int player_pres = get_attr_val(player_name, "PRES");
  int player_sup  = get_attr_val(player_name, "SUP");
  int player_prod = get_attr_val(player_name, "PROD");
  int player_sus  = get_attr_val(player_name, "SUS");
  int player_ali = get_attr_val(player_name, "ALL");
  int dec = get_DEC();
  int player_arrested = get_attr_val(player_name, "ARRESTED");
  int player_alliance = get_attr_val(player_name, "IN_ALLIANCE");
  int sta_r4b2 = !strcmp(get_choice(get_player("STA"), 4), "2:2");
  switch(round){
  case 1:
    return 1;
  case 2:
    if(player_pres > 4)
      return 1;
    else if(player_sup > 4)
      return 2;
    else
      return 3;
  case 3:
    if(player_prod < dec || player_sus > 7 || player_pres > 10)
      return 1;
    else if(player_ali > 1)
      return 2;
    else
      return 3;
  case 4:
    if(player_arrested && (player_prod < dec || player_pres > 10 || player_sus > 7) && !player_alliance)
	  return 1;
    else if (player_arrested)
      return 2;
    else if((player_prod < dec || player_pres > 10 || player_sus > 7) && player_alliance)
      return 4;
    else
      return 3;
  case 5:
    if(player_arrested)
      return 2;
    else if(!player_alliance && !sta_r4b2 && (player_prod < dec+1 || player_sus > 9 || player_sus > 12)
          || !sta_r4b2 && (player_prod < dec -1 || player_sus > 5 || player_pres > 8))
      return 1;
    else 
      return 3;
  case 6:
    if(player_pres > 4)
      return 1;
    else if(player_sup > 4)
      return 2;
    else
      return 3;
  }
  printf("PROBLEM IN IM\n");
  abort();
  return -1;
}
 
int get_prompt_num_STA(char *player_name, int round){
  int yez_pow = get_attr_val(get_player("YEZ"), "POW");
  int yag_sus = get_attr_val(get_player("YAG"), "SUS");
  int player_fear = get_attr_val(player_name, "FEAR");
  int player_r3a2 = strcmp(get_choice(player_name, 3), "1:2");
  int player_r3a3 = strcmp(get_choice(player_name, 3), "1:3");
  int player_r4b2 = strcmp(get_choice(player_name, 4), "2:2");
  int player_r5a1 = strcmp(get_choice(player_name, 5), "1:1");
  int player_r5a2 = strcmp(get_choice(player_name, 5), "1:2");
  switch (round){
  case 1:
    return 1;
  case 2:
    if(yez_pow < 3 && yag_sus >= 6)
      return 1;
    else if(player_fear >= 7)
      return 2;
    else
      return 3;
  case 3:
    return 1;
  case 4:
    if(!player_r3a2 || !player_r3a3)
      return 1;
    else
      return 2;
    break;
  case 5:
    if(!player_r4b2)
      return 1;
    else
      return 2;
  case 6:
    if(!player_r5a1 || !player_r5a2)
      return 1;
    else
      return 2;
  }
  printf("PROBLEM IN STA\n");
  abort();
  return -1;
}

int get_prompt_num_YAG(char *player_name, int round){
  int player_pres = get_attr_val(player_name, "PRES");
  int player_sus = get_attr_val(player_name, "SUS");
  int player_fav = get_attr_val(player_name, "FAV");
  int player_cred = get_attr_val(player_name, "CRED");
  int sta_r2a2 = strcmp(get_choice(get_player("STA"), 2), "1:2");
  int sta_r2a3 = strcmp(get_choice(get_player("STA"), 2), "1:2");
  int yez_r2a2 = strcmp(get_choice(get_player("YEZ"), 2), "1:2");
  int yez_r2b1 = strcmp(get_choice(get_player("YEZ"), 2), "2:1");
  int yez_r2b2 = strcmp(get_choice(get_player("YEZ"), 2), "2:2");
  int yez_r2c2 = strcmp(get_choice(get_player("YEZ"), 2), "3:2");
  int yez_r2c3 = strcmp(get_choice(get_player("YEZ"), 2), "3:3");
  int player_arrested = get_attr_val(player_name, "ARRESTED");
  int player_demoted = get_attr_val(player_name, "DEMOTED");
  int yez_arrested = get_attr_val(get_player("YEZ"), "ARRESTED");
  int yez_demoted = get_attr_val(get_player("YEZ"), "DEMOTED");
  int sta_r5a1 = strcmp(get_choice(get_player("STA"), 5), "1:1");
  int sta_r5a2 = strcmp(get_choice(get_player("STA"), 5), "1:2");
  
  switch(round){
  case 1:
    return 1;
  case 2:
    if(player_pres > 6 || player_sus > 6)
      return 1;
    else if(player_fav > 7 || player_cred > 7)
      return 2;
    else
      return 3;
  case 3:
    if(!sta_r2a2 || !sta_r2a3)
      return 1;
    else if(!yez_r2a2 || !yez_r2b1)
      return 2;
    else
      return 3;
  case 4:
    if((!yez_r2b2 || !yez_r2c2 || !yez_r2c3) && !player_arrested && !player_demoted){
      return 1;
    }else if(player_arrested || player_demoted){
      return 2;
    }else if((yez_arrested || yez_demoted) && !player_demoted && !player_arrested){
      return 3;
    }else return 4;
  case 5:
    if(!player_arrested && yez_arrested) return 1;
    else if(player_arrested) return 2;
    else return 3;
  case 6:
    if(!sta_r5a1 && !sta_r5a2) return 1;
    else return 2;
  }
  printf("PROBLEM IN YAG\n");
  abort();
  return -1;
}

int get_prompt_num_YEZ(char *player_name, int round){
  int prompt_number = 3;
  int FAV_attr_val = get_attr_val(player_name, "FAV");
  int POW_attr_val = get_attr_val(player_name, "POW");
  int CRED_attr_val = get_attr_val(player_name, "CRED");
  char *STA_choice_r2 = malloc(sizeof(char)*10);
  char *PLAYER_choice_r2 = malloc(sizeof(char)*10);
  char *YAG_choice_r3 = malloc(sizeof(char)*10);
  int YAG_arrested = get_attr_val(get_player("YAG"), "ARRESTED");
  int YEZ_arrested = get_attr_val(player_name, "ARRESTED");
  char *STA_choice_r5 = malloc(sizeof(char)*10);
  
  strcpy(YAG_choice_r3, get_choice(get_player("YAG"), 2));
  strcpy(PLAYER_choice_r2, get_choice(player_name, 2));
  strcpy(STA_choice_r2, get_choice(get_player("STA"), 2));
  strcpy(STA_choice_r5, get_choice(get_player("STA"), 2));
  
  switch(round){
  case 1:
    return 1;
  case 2:
    if(FAV_attr_val >6 || CRED_attr_val>6)
      return 1;
    else if(POW_attr_val>7)
      return 2;
    break;
  case 3:
    if((strcmp(STA_choice_r2, "1:1")==0) || (strcmp(STA_choice_r2, round-1), "1:3")==0))
      return 1;
    else if((strcmp(PLAYER_choice_r2, "1:2")==0) || (strcmp(PLAYER_choice_r2, "2:1")==0))
      return 2;
    break;
  case 4:
    if((strcmp(YAG_choice_r3, "2:2"))==0)
      prompt_number = 1;
    else if(YAG_arrested == 1)
      prompt_number = 2;
    else if(YEZ_arrested == 1)
      prompt_number = 3;
    else
      prompt_number = 4;
    break;
  case 5:
    if(YEZ_arrested == 0 && (YAG_arrested == 1))
      prompt_number = 1;
    else if(YEZ_arrested == 1)
      prompt_number = 2;
    break;
  case 6:
    if(strcmp(STA_choice_r5, "1:1")==0 || strcmp(STA_choice_r5, round-1), "1:2")==0){
      prompt_number = 1;
    }else{
      prompt_number = 2;
    }
    break;
  }
  return prompt_number;
}

int get_prompt_num_NKVDO(char *player_name, int round){
	
	int PROD_attr_val = get_attr_val(player_name, "PROD");
	int SUS_attr_val = get_attr_val(player_name, "SUS");
	int CRED_attr_val = get_attr_val(player_name, "CRED");
	char *past_round_choice = get_choice(player_name, round-1);
	char *third_round_choice = get_choice(player_name, 3);
	char *STA_choice_r5  = get_choice(get_player("STA"), 5);
	
  switch(round){
  case 1:
    return 1;
  case 2:
    if(PROD_attr_val<4 || SUS_attr_val>7)
      return 1;
    else if(SUS_attr_val<4 || CRED_attr_val>6)
      return 2;
    else
      return 3;
  case 3:
    if(strcmp(past_round_choice, "2:1") == 0)
      return 1;
    else if(strcmp(past_round_choice, "1:3") == 0)
      return 2;
    else
      return 3;
  case 4:
    return 1;
    break;
  case 5:
    if(strcmp(third_round_choice, "2:1") == 0)
      return 1;
    else if((strcmp(third_round_choice, "1:1")==0) || (strcmp(third_round_choice, "1:3")==0))
      return 2;
    else
      return 3;
  case 6:
    if(!strcmp(STA_choice_r5, "1:1") || !STA_choice_r5, "1:2")){
      return 1;
    }else{
      return 2;
    }
  }
  printf("PROBLEM IN NKVDO\n");
  abort();
  return -1;
}

double get_DEC(){
  char *nav_text = read_text("nav_file.txt");
  char **nav_lines = split(nav_text, '\n');
  char **players = malloc(sizeof(char*) * 100);
  int ep_count = 0, j = 0;
  for(int i = 0; nav_lines[i]; i++){
    char **nav_line = split(nav_lines[i], '=');
    if(nav_lines[i][0] == '\0') continue;
    if(strcmp(nav_line[1], "EP") == 0){
      players[j] = malloc(sizeof(char) * 100);
      players[j] = strdup(nav_line[0]);
      ep_count++;
      j++;
    }
    free_arr(nav_line);
  }
  players[j] = NULL;
  
  double DEC = 0;
  for(int i = 0; players[i]; i++){
    DEC += get_attr_val(players[i], "POL");
  }
  DEC /= (double)ep_count;
  free_arr(nav_lines);
  free_arr(players);
  free(nav_text);
  return DEC;
}