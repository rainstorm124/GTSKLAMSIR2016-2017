#include "setup.h"
#include "gregutils.h"
#include "linked_list.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "prompt.h"
#include <stdint.h>
#include <stddef.h>

#define MINIMUM_PLAYERS 60
/*

27 Stakhanovite Workers 3StakW/IM (1)
9 Industrial Managers 3IMs/OPL (2)
7 Bedniaks (3)
5 NKVD Officers (4)
3 Economic Planners (5)
3 Oblast Party Leaders (6)
3 Ex-Kulaks (7)
1 Stalin (8)
1 Yagoda (9)
1 Yezhov (10)
*/
int ask_prompt;
typedef struct player_type{
	char *type;
	int count;
} player_type;

player_type* create_player_type(char *type, int count){
	player_type *pt = malloc(sizeof(player_type));
	pt->type = type;
	pt->count = count;
	return pt;
}

void free_player_type(void *ptype){
  free(ptype);
}

int compare_player_type(void *a, void *b){
	return strcmp(((player_type*)a)->type, ((player_type*)b)->type);
}

void print_type(void *ptr){
	printf("%s", ((player_type*)ptr)->type);
}

int main(int argc, char **argv){
  if(argc > 1 && !strcmp(argv[1], "-y")) ask_prompt = 0;
  else ask_prompt = 1;
	initialize("students.txt");
	return 0;
}

void initialize(char *student_file){
	FILE *fp = fopen(student_file, "r");
	if(fp){
    if(!ask_prompt) goto b;
		printf("This action will overwrite all assignment files. Continue? (y/n): ");
		while(true){
			char c = getchar();
			if(c == 'y'){
				break;
			}else if(c == 'n'){
				printf("quitting...\n");
				return;
			}else{
				printf("\"%c\" is invalid\n", c);
				continue;
			}
		}
	}else{
		printf("\"%s\" does not exist\n", student_file);
	}
  b:
	srand(time(NULL));
	char *student_text = read_text(student_file);
	char **students = split(student_text, '\n');
	int student_count = 0;
	while(students[student_count]) student_count++;
	if(student_count < MINIMUM_PLAYERS){
		printf("ERROR: %d players is less than the minimum number of players (%d)\n", student_count, MINIMUM_PLAYERS);
		return;
	}else{
		//printf("students = %d\n", student_count);
	}
	int peasants = student_count - MINIMUM_PLAYERS;
	int bedniaks = peasants == 1 ? 1 : peasants * 2.0 / 3.0; // 2:1 ratio between bediaks and ex_kulaks
	int ex_kulaks = peasants - bedniaks;
	linked_list *type_list = create_linked_list(compare_player_type, free_player_type, print_type);

	// number of each type of player in the game
	add_node(type_list, create_node(create_player_type("STAKW", 27)));
	add_node(type_list, create_node(create_player_type("IM", 9)));
	add_node(type_list, create_node(create_player_type("BD", 7 + bedniaks)));
	add_node(type_list, create_node(create_player_type("NKVDO", 5)));
	add_node(type_list, create_node(create_player_type("EP", 3)));
	add_node(type_list, create_node(create_player_type("OPL", 3)));
	add_node(type_list, create_node(create_player_type("EXK", 3 + ex_kulaks)));
	add_node(type_list, create_node(create_player_type("YAG", 1)));
	add_node(type_list, create_node(create_player_type("YEZ", 1)));
	add_node(type_list, create_node(create_player_type("STA", 1)));
	//printf("extra peasants total = %d, bd = %d, exk = %d\n", peasants, bedniaks, ex_kulaks);
	// clear navigation file
	FILE *nav_file_clear = fopen("nav_file.txt", "w");
	fclose(nav_file_clear);
	for(int i = 0; students[i]; i++){
		int r = grandom(type_list->size);
		node *node = get_node_at(type_list, r);
    if(i==0){
      node = get_node_at(type_list, 9);
    }
    
    
		char *dir = malloc(sizeof(char) * 30);
		sprintf(dir, "./players/");
		struct stat st = {0};
		if (stat(dir, &st) == -1) {
      #ifdef WIN32
			mkdir(dir);
      #else
      mkdir(dir, ~0);
      #endif
		}
		char **character_attirbute_names;
		if(strcmp(((player_type*)node->data)->type, "STAKW") == 0){
			character_attirbute_names = split("MOT,5 SUS,2 PRES,4 FAT,0 ARRESTED,0 GULAG,0 DEAD,0", ' ');
		}else if(strcmp(((player_type*)node->data)->type, "IM") == 0){
			character_attirbute_names = split("PRES,4 ALL,1 SUP,4 SUS,4 PROD,5 IN_ALLIANCE,0 ARRESTED,0 GULAG,0 DEAD,0", ' ');
		}else if(strcmp(((player_type*)node->data)->type, "BD") == 0){
			character_attirbute_names = split("HUNG,4 LOY,3 FAT,3 PRES,5 ARRESTED,0 GULAG,0 DEAD,0", ' ');
		}else if(strcmp(((player_type*)node->data)->type, "NKVDO") == 0){
			character_attirbute_names = split("PRES,6 SUS,4 CRED,6 FAV,5 PROD,5 ARRESTED,0 GULAG,0 DEAD,0 DEMOTED,0 POW,0", ' ');
		}else if(strcmp(((player_type*)node->data)->type, "EP") == 0){
			character_attirbute_names = split("POL,5 ALI,10 SUS,4 ARRESTED,0 GULAG,0 DEAD,0", ' ');
		}else if(strcmp(((player_type*)node->data)->type, "OPL") == 0){
			character_attirbute_names = split("PRES,4 ALL,1 SUP,4 SUS,4 PROD,5 IN_ALLIANCE,0 ARRESTED,0 GULAG,0 DEAD,0", ' ');
		}else if(strcmp(((player_type*)node->data)->type, "EXK") == 0){
			character_attirbute_names = split("HUNG,3 LOY,2 FAT,2 PRES,7 ARRESTED,0 GULAG,0 DEAD,0", ' ');
		}else if(strcmp(((player_type*)node->data)->type, "YAG") == 0){
			character_attirbute_names = split("FAV,5 CRED,6 SUS,6 POW,7 PRES,7 ARRESTED,0 GULAG,0 DEAD,0 DEMOTED,0", ' ');
		}else if(strcmp(((player_type*)node->data)->type, "YEZ") == 0){
			character_attirbute_names = split("FAV,7 CRED,5 SUS,4 POW,3 PRES,5 ARRESTED,0 GULAG,0 DEAD,0 DEMOTED,0", ' ');
		}else if(strcmp(((player_type*)node->data)->type, "STA") == 0){
			character_attirbute_names = split("SUP,7 ALL,7 FEAR,6 POW,8 ALI,5 ARRESTED,0 GULAG,0 DEAD,0", ' ');
		}else{
			printf("error, unmatched character!!!\n");
		}
		int num_attrs = 0;
		while(character_attirbute_names[num_attrs]){ 
			num_attrs++;
		};
		
		// create player attribute files
		char *attribute_filepath = calloc(sizeof(char) , 100);
		sprintf(attribute_filepath, "%s/%s_attributes.txt", dir, students[i]);
		FILE *player_attributes = fopen(attribute_filepath, "w+");
		fprintf(player_attributes, "%d\n", num_attrs);
		for(int x = 0; character_attirbute_names[x]; x++){
			char **attr_info = split(character_attirbute_names[x], ',');
			fprintf(player_attributes, "%s=%d\n", attr_info[0], atoi(attr_info[1]));
			free_arr(attr_info);
		}
		fclose(player_attributes);
		free(attribute_filepath);
		// create player choice files
		char *choice_filepath = calloc(sizeof(char) , 100);
		sprintf(choice_filepath, "%s/%s_choices.txt", dir, students[i]);
		FILE *player_choices = fopen(choice_filepath, "w+");
		fclose(player_choices);
		free(choice_filepath);
		// add character assignment to navigation file
		FILE *nav_file = fopen("nav_file.txt", "a+");
		fprintf(nav_file, "%s=%s\n", students[i], ((player_type*)node->data)->type);
		fclose(nav_file);
		
		((player_type*)(node->data))->count--;
		if(((player_type*)(node->data))->count == 0){
			delete_node(type_list, node);
		}
    free(dir);
    free_arr(character_attirbute_names);
	}
	
	// populate arrays of opl, im and stakw
	char *opl_list[3+1], *im_list[9+1], *stakw_list[27+1], *nkvdo_list[5+1];
	int opl = 0, im = 0, stakw = 0, nkvdo = 0;
	char *nav_text = read_text("nav_file.txt");
	char **nav_lines = split(nav_text, '\n');
	for(int i = 0; nav_lines[i]; i++){
		char **entry = split(nav_lines[i], '=');
		if(!entry[1]){
			continue; 
		}// last empty line has no 2nd element;
		if(strcmp(entry[1], "OPL") == 0){
			opl_list[opl] = strdup(entry[0]);
			opl++;
		}
		if(strcmp(entry[1], "IM") == 0){
			im_list[im] = strdup(entry[0]);
			im++;
    }
		if(strcmp(entry[1], "STAKW") == 0){
			stakw_list[stakw] = strdup(entry[0]);
			stakw++;
		}
    if(strcmp(entry[1], "NKVDO") == 0){
      nkvdo_list[nkvdo] = strdup(entry[0]);
      nkvdo++;
    }
    free_arr(entry);
	}
  free(nav_text);
  free_arr(nav_lines);
  opl_list[opl] = NULL;
  im_list[im] = NULL;
  stakw_list[stakw] = NULL;
  nkvdo_list[nkvdo] = NULL;
	
	// create IM-OPL assignments
	FILE *im_opl = fopen("im-opl.txt", "w+");
	for(int i = 0; i < 3; i++){
		for(int j = i * 3; j < i * 3 + 3; j++){
			fprintf(im_opl, "%s=%s\n", im_list[j], opl_list[i]); // IM=OPL
		}
	}
	fclose(im_opl);
	
	// create STAKW-IM assignments
	FILE *stakw_im = fopen("stakw-im.txt", "w+");
	for(int i = 0; i < 9; i++){
		for(int j = i * 3; j < i * 3 + 3; j++){
			fprintf(stakw_im, "%s=%s\n", stakw_list[j], im_list[i]); // STAKW=IM
		}
	}
	fclose(stakw_im);
  
  char *player_yag = get_player("YAG");
  char *player_yez = get_player("YEZ");
  
  // create STAKW, IM and OPL investigation assignment files
  FILE *stakw_investigations = fopen("stakw_investigations.txt", "w+");
  char **random_stakw = get_random_players("STAKW", 5);
  int stakw_i = 0;
  fprintf(stakw_investigations, "%s=%s\n", stakw_list[stakw_i++], player_yag);
  fprintf(stakw_investigations, "%s=%s\n", stakw_list[stakw_i++], player_yez);
  for(int i = 0; nkvdo_list[i]; i++){
    fprintf(stakw_investigations, "%s=%s\n", random_stakw[i], nkvdo_list[i]);
  }
  free_arr(random_stakw);
  fclose(stakw_investigations);
  FILE *im_investigations = fopen("im_investigations.txt", "w+");
  char **random_nkvdo= get_random_players("NKVDO", 5);
  int im_i = 0;
  fprintf(im_investigations, "%s=%s\n", im_list[im_i++], player_yag);
  fprintf(im_investigations, "%s=%s\n", im_list[im_i++], player_yez);
  for(int i = im_i; im_list[i]; i++){
    fprintf(im_investigations, "%s=%s\n", im_list[i], random_nkvdo[i % 5]);
  }
  free_arr(random_nkvdo);
  fclose(im_investigations);
  FILE *opl_investigations = fopen("opl_investigations.txt", "w+");
  char **random_opl = get_random_players("OPL", 3);
  int opl_i = 0;
  fprintf(opl_investigations, "%s=%s\n", opl_list[opl_i++], player_yag);
  fprintf(opl_investigations, "%s=%s\n", opl_list[opl_i++], player_yez);
  for(int i = 0; nkvdo_list[i]; i++){
    fprintf(opl_investigations, "%s=%s\n", random_opl[i % 3], nkvdo_list[i]);
  }
  fclose(opl_investigations);
  free_arr(random_opl);
	fclose(fp); // close students' names files
  free(student_text);
  free_arr(students);
  free(player_yag);
  free(player_yez);
}