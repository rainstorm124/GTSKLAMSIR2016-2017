/*
 * admin_choice_v1.c
 *
 *  Created on: Mar 15, 2017
 *      Author: rcb
 */
#include "gregutils.h"
#include "prompt.h"
#include "prompt_chooser.h"
#include "zutils.h"
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>

int main(void){
  print_header();
  //
	int _round = get_round();
	// process stuff
  char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = calloc(text_len + 1, sizeof(char));
	fgets(postdata, text_len + 1, stdin);
  printf("<!DOCTYPE html>\n");
	char **split_return = split(postdata, '&');
  //variable scanning
	char round [1024];
	char prompt[1024];
	char user[1024];
	sscanf(split_return[3], "choice=%s", choice);
	sscanf(split_return[2], "user=%s", user);
	sscanf(split_return[1], "prompt=%s", prompt);
	sscanf(split_return[0], "round=%s", round);
  bool admin = !strcmp(get_type(user), "STA");
  // check that user has not already made a choice
  char *code = get_user_choice(user);
  bool chosenp = (code != NULL);
  //////
	char full_code[4096];
	sprintf(full_code, "%s:%s:%s:%s", user, round, prompt, choice);
	if(!chosenp)add_update_to_queue(full_code);
  else printf("<!-- Already chose %s-->\n", code);

  
	//char user_HTML_setup[512];
	//sprintf(user_HTML_setup, "<input type=\"hidden\" name=\"name\" id=\"name\" value=\"%s\">", split_return[0]);
	// return the user to the interface
  printf("<html><head><title>Loading: The Soviet Great Terror Simulation</title><script type=\"text/javascript\">"
             "function loaded(e){ document.forms[0].submit.click();}"
             "</script></head><body onload=\"loaded();\"><h1>Loading..."
			       "</h1><br><form name='user' id='user' action='user_interface.cgi' "
			       "method='POST'><input type='hidden' name='user'"
             "value='%s'><input type='submit' name='submit' "
			       "value='Submit'></form></body></html>",user);
  /*if (admin && count_players_chosen("update_file.txt") == count_nav_lines()){
		printf("</head>\n");
		printf("<body> <h1> All choices in round %d made, advancing to round %d. Please press the button below to return to your page. </h1>", round, round + 1);
		printf("<form action = admin_interface.cgi>"
			"%s"
			"<input type=\"submit\" name = \"submitbutton\" id=\"submitbutton\"> </form>", user_HTML_setup);
		printf("</body></html>");
    fflush(stdout);
		set_round(_round+1);
	} else {
		printf("<style>");
		printf("#header_and_prompt {"
					"position:absolute;"
					"width:1230px;"
					"height:200px;"
					"padding:2px;}");
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
		printf("</head> <body background = \"/greg/background.png\"");
		printf("<button onclick=\"prompt();\"> Prompt </button>"
				"<button onclick=\"attr();\"> Attributes </button>"
				"<button onclick=\"history();\"> Choice History </button>");
		printf("<div id=\"prompt\"");
		printf("<div id=\"header_and_prompt\"> <h1> Your fate has been sealed. Please wait for your peers to decide theirs. </h1> </div></div>");
		printf("<div id=\"attr\" style=\"display:none;\">");
		printf("<div id=\"playerattributes\">"
				"<h1 style=\"color:black\"><center> user Attributes </center></h1>"
				"<center><table style=\"width:730px\"> <tr> <th colspan=\"2\">Attributes</th>"
				"<th>Values</th></tr><tr><td colspan=\"2\"> attribute here </td><td> 1 </td>"
				"</tr></table></center></div></div>");
    //user history div
		printf("<div id = \"history\" style=\"display:none;\">");
		printf("<center><h1>Choice History</h1>");
		printf("<table><tr><th>Round Number</th><th>Prompt</th><th>Choice</th></tr>");

		char player_choices_filename[4096];
		sprintf(player_choices_filename, "players/%s_choices.txt", user);
		char *player_choices = read_text(player_choices_filename);
		char **split_choices = split(player_choices, '\n');
    free(player_choices);

		for (int i = 0; split_choices[i]; i++){
			char **choices = split(split_choices[i], ':');
			printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", choices[1], choices[2], choices[3]);
      free_arr(choices);
		}
    free_arr(split_choices);
		printf("</table></center></div>");
    // players chosen div
		printf("<div id=\"players_chosen\">");
		printf("<center><h1> Players Chosen </h1>");
		printf("<table><tr><th>user Name</th><th>Chosen?</th></tr>");

    char *students_text = read_text("students.txt");
	  char **players = split(students_text, '\n');
    free(students_text);
    //
    char *update_text = read_text("update_file.txt");
    char **update_lines = split(update_text, '\n');
    free(update_text);
    // Display a table listing players and whether they have chosen an option this round
    for(int i=0; players[i]; i++){
      int j = 0;
      for(; update_lines[j]; j++){
         char **line = split(update_lines[j], ':');
         if(!strcmp(line[0], players[i])){ free_arr(line); break;}
         free_arr(line);
      }
      int chosen = (update_lines[j] != NULL);
      printf("<tr><td>%s</td><td>%s</td></tr>", players[i], chosen ? "true":"false");
    }
    free_arr(update_lines);
    free_arr(players);
    ///
		printf("</table></center><br>FORCE UPDATE?<br><form action=\"forced_update.cgi\"> <input type=\"submit\" name=\"force_update\" id=\"force_update\"> </form> </div>");
		printf("</body> </html>");
	}*/
  exit(0);
}
