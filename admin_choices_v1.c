/*
 * admin_choice_v1.c
 *
 *  Created on: Mar 15, 2017
 *      Author: rcb
 */

#include "prompt.h"
#include "prompt_chooser.h"
#include "zoinka.h"
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>

int main(void){

	int round = get_round();

	char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = malloc(text_len + 1);
	fgets(postdata, text_len + 1, stdin);
	char *choice = malloc(sizeof(char) * 1024 * 1024);
	char **split_return = split(postdata, '&');
	sscanf(split_return[3], "player_choice=%s", choice);
	char *choice_round = malloc(sizeof(char) * 1024);
	char *prompt = malloc(sizeof(char) * 1024);
	char *character_name = malloc(sizeof(char) * 1024);
	sscanf(split_return[2], "name=%s", character_name);
	sscanf(split_return[1], "prompt=%s", prompt);
	sscanf(split_return[0], "round=%s", round);

	char *full_code = malloc(sizeof(char) * 1024 * 1024 * 2);
	sprintf(full_code, "%s:%s:%s:%s", character_name, round, prompt, choice);
	add_update_to_queue(full_code);

	char *user_HTML_setup = malloc(sizeof(char)*30);
	sprintf(user_HTML_setup, "<input type=\"hidden\" name=\"name\" id=\"name\" value=\"%s\">", split_return[0]);

	if (count_players_chosen("update_file.txt") == true){
		printf("Content-type: text/html\n\n");
		printf("<html><head><title>");
		printf("WELCOME TO THE GULAG\n");
		printf("</title>");
		printf("<body> <h1> All choices in this round made. Please press the button below to continue. </h1>");
		printf("<form action = player_interface_v2.cgi>"
			"%s"
			"<input type=\"submit\" name = \"submitbutton\" id=\"submitbutton\"> </form>", user_HTML_setup);
		printf("</body></html>");
		increment_round();
	}
	else {
		printf("Content-type: text/html\n\n");
		printf("<html><head><title>");
		printf("WELCOME TO THE GULAG\n");
		printf("</title>");
		printf("<style>");
		printf("#header_and_prompt {"
					"position:absolute;"
					"width:1230px;"
					"height:200px;"
					"padding:2px;"
				"}");
		printf("#playerattributes {"
					"position:absolute;"
					"top:410px;"
					"width:1230px;"
					"height:400px;"
					"float:left;}");
		printf("</style>");
		printf("<script>");
		printf("function prompt() { document.getElementbyId(\"prompt\").style.display=\"block\"; document.getElementbyId(\"attr\").style.display=\"none\"; document.getElementbyId(\"history\").style.display=\"none\"; document.getElementbyId(\"players_chosen\").style.display=\"none\";}");
		printf("function attr() { document.getElementbyId(\"attr\").style.display=\"block\"; document.getElementbyId(\"prompt\").style.display=\"none\";document.getElementbyId(\"history\").style.display=\"none\"; document.getElementbyId(\"players_chosen\").style.display=\"none\";}");
		printf("function history() { document.getElementbyId(\"history\").style.display=\"block\"; document.getElementbyId(\"prompt\").style.display=\"none\";document.getElementbyId(\"attr\").style.display=\"none\"; document.getElementbyId(\"players_chosen\").style.display=\"none\";}");
		printf("function players_chosen() { document.getElementbyId(\"players_chosen\").style.display=\"block\"; document.getElementbyId(\"prompt\").style.display=\"none\";document.getElementbyId(\"attr\").style.display=\"none\"; document.getElementbyId(\"history\").style.display=\"none\";}");
		printf("</script>");
		printf("</head> <body background = \"background.png\"");
		printf("<button onclick=\"prompt();\"> Prompt </button>"
				"<button onclick=\"attr();\"> Attributes </button>"
				"<button onclick=\"history();\"> Choice History </button>");
		printf("<div id=\"prompt\"");
		printf("<div id=\"header_and_prompt\"> <h1> Your fate has been sealed. Please wait for your peers to decide theirs. </h1> </div></div>");
		printf("<div id=\"attr\" style=\"display:none;\"");
		printf("<div id=\"playerattributes\">"
				"<h1 style=\"color:black\"><center> Player Attributes </center></h1>"
				"<center><table style=\"width:730px\"> <tr> <th colspan=\"2\">Attributes</th>"
				"<th>Values</th></tr><tr><td colspan=\"2\"> attribute here </td><td> 1 </td>"
				"</tr></table></center></div></div>");
		printf("<div id = \"history\" style=\"display:none;\">");
		printf("<center><h1>Choice History</h1>");
		printf("<table><tr><th>Round Number</th><th>Prompt</th><th>Choice</th></tr>");

		//Open and process player choice file.
		char *player_choices_filename = malloc(sizeof(char) * 1024 * 1024);
		sprintf(player_choices_filename, "%s_choices.txt", character_name);

		char *player_choices = read(player_choices_filename);
		char **split_choices = split(player_choices, '/n');

		for (int i = 0; split_choices[i]; i++){
			char **choices = split(split_choices[i], ':');
			printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", choices[1], choices[2], choices[3]);
		}
		printf("</table></center></div>");
		printf("<div id=\"players_chosen\">");
		printf("<center><h1> Players Chosen </h1>");
		printf("<table><tr><th>Player Name</th><th>Chosen?</th></tr>");

		char *navigatorfile = read_text("nav_file.txt");
		char **nav_split_by_line = split(navigatorfile, '/n');
		char *choicesfile = read_text("update_file.txt");
		char **update_split_by_line = split(navigatorfile, '/n');
		char ***nav_lines_split = malloc(sizeof(char)*1024);
		for (int i = 0; nav_split_by_line[i]; i++){
			char **split_nav_line = split(nav_split_by_line, '=');
			strcpy(nav_lines_split[i][0], split_nav_line[0]);
			strcpy(nav_lines_split[i][1], split_nav_line[1]);
		}
		for (int i = 0; update_split_by_line[i]; i++){
			char **split_update_line = split(update_split_by_line, ';');
			char *update_submit_true = "true";
			char *update_submit_false = "false";
			int j = 0;
			for(j = 0;(strcmp(split_update_line[0], nav_lines_split[j][0])!=0) && nav_lines_split[j]; j++)
				continue;
			if(strcmp(split_update_line[0], nav_lines_split[j][0])==0)
				printf("<tr><td>%s</td><td>%s</td></tr>", nav_lines_split[j][0], update_submit_true);
			else
				printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", nav_lines_split[j][0], update_submit_false);
		}
		printf("</table></center><br><br><form action=\"forced_update.cgi\"> <input type=\"submit\" name=\"force_update\" id=\"force_update\"> </form> </div>");
		printf("</body> </html>");
	}

}
