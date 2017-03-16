#include "zoinka.h"
#include <stdio.h>
#include <strings.h>
#include "prompt.h"
#include "gregutils.h"

int main(void){
  print_header();
	char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = malloc(text_len + 1);
	fgets(postdata, text_len + 1, stdin);
	char *choice = calloc(sizeof(char), 1024);
	char **split_return = split(postdata, '&');
	sscanf(split_return[3], "playerchoice=%s", choice);
	char *round = calloc(sizeof(char), 1024);
	char *prompt = calloc(sizeof(char), 1024);
	char *player_name = calloc(sizeof(char), 1000);
	sscanf(split_return[2], "name=%s", player_name);
	sscanf(split_return[1], "prompt=%s", prompt);
	sscanf(split_return[0], "round=%s", round);
printf("<html><head><title>");
		printf("WELCOME TO THE GULAG\n");
		printf("</title><body>round=%s prompt=%s name=%s choice=%s</body>", round, prompt, player_name, choice);
	char *full_code = calloc(sizeof(char), 2000);
	sprintf(full_code, "%s:%s:%s:%s", player_name, round, prompt, choice);
	add_update_to_queue(full_code);
  char *prompt_code = calloc(sizeof(char), 2000);
  sprintf(prompt_code, "%s:%s:%s", player_name, round, prompt);
  
	char *user_HTML_setup = calloc(sizeof(char), 128);
	sprintf(user_HTML_setup, "<input type=\"hidden\" name=\"name\" id=\"name\" value=\"%s\">", split_return[2]);

	if (count_players_chosen("update_file.txt") == count_nav_lines()){
		printf("<html><head><title>");
		printf("WELCOME TO THE GULAG\n");
		printf("</title>");
		printf("<body> <h1> All choices in this round made. Please press the button below to continue. </h1>");
		printf("<form action = player_interface.cgi>"
			"%s"
			"<input type=\"submit\" name = \"submitbutton\" id=\"submitbutton\"> </form>", user_HTML_setup);
		printf("</body></html>");
		set_round(get_round()+1);
	} else {
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
		printf("function prompt() { document.getElementbyId(\"prompt\").style.display=\"block\"; document.getElementbyId(\"attr\").style.display=\"none\"; document.getElementbyId(\"history\").style.display=\"none\";}");
		printf("function attr() { document.getElementbyId(\"attr\").style.display=\"block\"; document.getElementbyId(\"prompt\").style.display=\"none\";document.getElementbyId(\"history\").style.display=\"none\";}");
		printf("function history() { document.getElementbyId(\"history\").style.display=\"block\"; document.getElementbyId(\"prompt\").style.display=\"none\";document.getElementbyId(\"attr\").style.display=\"none\";");
		printf("</script>");
		printf("</head> <body background = \"/greg/background.png\"");
		printf("<button onclick=\"prompt();\"> Prompt </button>"
				"<button onclick=\"attr();\"> Attributes </button>"
				"<button onclick=\"history();\"> Choice History </button>");
		printf("<div id=\"prompt\"> <!-- %s --> <h3>%s</h3> </div>", full_code, get_prompt_text(player_name, prompt_code));
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
		sprintf(player_choices_filename, "players/%s_choices.txt", player_name);

		char *player_choices = read_text(player_choices_filename);
		char **split_choices = split(player_choices, '\n');

		if(split_choices[0] && split_choices[0][0]) for (int i = 0; split_choices[i]; i++){
			char **choices = split(split_choices[i], ':');
			printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", choices[1], choices[2], choices[3]);
		}
		printf("</table></center></div>");
	  printf("</body> </html>");
  }
  exit(0);
}