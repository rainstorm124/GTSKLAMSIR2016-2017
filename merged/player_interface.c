/*
 * player_interface_v2.1.c
 *
 *  Created on: Mar 15, 2017
 *      Author: rcb, greg, nick
 */


#include <stdio.h>
#include <strings.h>
#include "prompt.h"
#include "gregutils.h"

int main(void){

	int round = get_round();

	//HTML header
  print_header();
	printf("<html><head><title>");
	printf("The Soviet Great Terror Simulation\n");
	printf("</title>");
  
  printf("<!-- round = %d-->", round);

	//CSS Stylesheet.
	printf("<style>");
	printf("#header_and_prompt {position:absolute;width:1230px;height:200px;padding:2px;}");
	printf("#choice_left {position:absolute;top:210px;width:400px;height:1000px;padding:5px;float:left;}");
	printf("#choice_center {position:absolute;top:210px;left:410px;width:400px;padding:5px;height:1000px;float:left;}");
	printf("#choice_right {position:absolute;top:210px;left:820px;width:400px;padding:5px;height:1000px;float:left;}");
	printf("#playerattributes {position:relative;width:1230px;height:200px;float:left;}");
	printf("#choiceform #submitbutton(margin-left:120px;margin_top:5px;width:90px;}");
	printf("</style>");

	//Javascript-based Menu
	printf("<script>");
	
	printf("function prompt() { document.getElementById(\"prompt\").style.display=\"block\";"
		"document.getElementById(\"attr\").style.display=\"none\";"
		"document.getElementById(\"history\").style.display=\"none\";}");
	printf("function attr() { document.getElementById(\"attr\").style.display=\"block\";" 
		"document.getElementById(\"prompt\").style.display=\"none\";"
		"document.getElementById(\"history\").style.display=\"none\";}");
	printf("function history() { document.getElementById(\"history\").style.display=\"block\";"
		"document.getElementById(\"prompt\").style.display=\"none\";"
    "document.getElementById(\"attr\").style.display=\"none\";}");
	printf("</script>");
	//end of head
	printf("</head>");
	
	//Gets and processes environment variable
	char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = malloc(text_len + 1);
	fgets(postdata, text_len + 1, stdin);
	char *user = malloc(sizeof(char) * 4096);
	char **split_return = split(postdata, '&');
	sscanf(split_return[0], "user=%s", user);

	//Prepares the player's files for reading
	char *player_attributes_filename = malloc(sizeof(char) * 4096);
	char *player_choices_filename = malloc(sizeof(char) * 4096);
	sprintf(player_attributes_filename, "players/%s_attributes.txt", user);

	//Reads them and processes them
	char *player_attributes = read_text(player_attributes_filename);
	char **split_attributes = split(player_attributes, '\n');
	//Dead check
	bool player_dead = false;
	bool player_gulag = false;
	for(int i = 0; split_attributes[i]; i++){
		char **split_attribute_line = split(split_attributes[i], '=');
		if(strcmp(split_attribute_line[0], "DEAD")==0 && strcmp(split_attribute_line[1], "1")==0)
			player_dead = true;
		else if(strcmp(split_attribute_line[0], "GULAG")==0 && strcmp(split_attribute_line[1], "1")==0)
			player_gulag = true;
		else continue;
	}
	//The player isn't dead.
	if(!player_dead && !player_gulag){
		char *prompt_code = get_prompt_code(user, round);
    printf("<!-- prompt_code = %s -->", prompt_code);
		char **prompt_choices = get_option_codes(prompt_code);
		char *prompt_text = get_prompt_text(user, prompt_code);
		char **prompt_choices_texts = calloc(4, sizeof(char*));
    
    
    int num_options = 0;
		for(int i = 0; prompt_choices[i]; i++, num_options++) {
      char *option_special = calloc(sizeof(char), 1024);
      sprintf(option_special, "%s:%d", prompt_code, i + 1);
			prompt_choices_texts[i] = malloc(sizeof(char) * 512);
			strcpy(prompt_choices_texts[i],get_option_texts_given_codes(option_special));
      free(option_special);
		}
		char **pre_prompt_code = split(prompt_code, ':');

		char *round_HTML_setup = calloc(sizeof(char), 512);
		char *prompt_HTML_setup = calloc(sizeof(char), 512);
		char *user_HTML_setup = calloc(sizeof(char), 512);

		sprintf(round_HTML_setup,"<input type=\"hidden\" name=\"round\" id=\"round\" value=\"%s\">", pre_prompt_code[1]);
		sprintf(prompt_HTML_setup, "<input type=\"hidden\" name=\"prompt\" id=\"prompt\" value=\"%s\">", pre_prompt_code[2]);
		sprintf(user_HTML_setup, "<input type=\"hidden\" name=\"name\" id=\"name\" value=\"%s\">", pre_prompt_code[0]);

		printf("<body background = \"/greg/background.png\">"
        "<button onclick=\"prompt();\"> Prompt </button>"
				"<button onclick=\"attr();\"> Attributes </button>"
				"<button onclick=\"history();\"> Choice History </button>"
				"<div id = \"prompt\">"
				"<div id=\"header_and_prompt\">"
				"<h1 style=\"color:black \"> <center> %s </center> </h1> </div>", prompt_text);
    for(int i = 0; i < num_options; i++){
      switch(i){
      case 0:
        printf("<div id=\"choice_left\"> <h3 style=\"color:black\"> Option 1:<br><center> %s </center> </h3>", prompt_choices_texts[i]);
        printf("<center> <form id=\"choiceform\" action=\"player_choice.cgi\" method = \"post\">"
            "%s %s %s <input type=\"hidden\" name=\"playerchoice\" id=\"playerchoice\" value=\"1\">"
            "<input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\">"
            "</form> </center> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup);
        break;
      case 1:
        printf("<div id=\"choice_center\"> <h3 style=\"color:black\"> Option 2:<br><center> %s </center> </h3>", prompt_choices_texts[i]);
        printf("<center> <form id=\"choiceform\" action=\"player_choice.cgi\" method = \"post\">"
            "%s %s %s <input type=\"hidden\" name=\"playerchoice\" id=\"playerchoice\" value=\"2\">"
            "<input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\">"
            "</form> </center> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup);
        break;
      case 2:
        printf("<div id=\"choice_right\"> <h3 style=\"color:black\"> Option 3:<br><center> %s </center> </h3>", prompt_choices_texts[i]);
        printf("<center> <form id=\"choiceform\" action=\"player_choice.cgi\" method = \"post\">"
            "%s %s %s <input type=\"hidden\" name=\"playerchoice\" id=\"playerchoice\" value=\"3\">"
            "<input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\">"
            "</form> </center> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup);
        break;
      }
    }
        
		printf("<div id = \"attr\" style=\"display:none;\">");
		printf("<div id=\"playerattributes\"> <h1 style=\"color:black\"> <center> Player Attributes </center> </h1> <center> <table style=\"width:730px\">");
		printf("<tr><th colspan=\"2\"> Attributes</th> <th> Values </th> </tr>");
		if(split_attributes[0]) for (int i = 0; split_attributes[i]; i++){
      if(i==0)continue;
			char **attributes = split(split_attributes[i], '=');
			printf("<tr><td colspan=\"2\">%s</td><td>%s</td></tr>", attributes[0], attributes[1]);
			free_arr(attributes);
		}
		printf("</table> </center>");
		printf("</div><center><h1>");
		// XXX TODO ??? BUG FIXME for ()
		printf("<div id = \"history\" style=\"display:none;\">");
		printf("<center><h1>Choice History</h1>");
		printf("<table><tr><th>Round Number</th><th>Prompt</th><th>Choice</th></tr>");

		//Open and process player choice file.
		sprintf(player_choices_filename, "players/%s_choices.txt", user);

		char *player_choices = read_text(player_choices_filename);
		char **split_choices = split(player_choices, '\n');

		if(split_choices[0] && split_choices[0][0]) for (int i = 0; split_choices[i]; i++){
			char **choices = split(split_choices[i], ':');
      printf("facts %s facts\n", split_choices[i]);
			printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", choices[1], choices[2], choices[3]);
      free_arr(choices);
		}
		printf("</table></center></div>");
		printf("</body> </html>");

		free(postdata);
		free(user);
		free_arr(split_return);
		free_arr(split_attributes);
		free_arr(split_choices);
		free(player_attributes_filename);
		free(player_choices_filename);
		free(prompt_code);
		free_arr(prompt_choices);
		free_arr(prompt_choices_texts);
		free_arr(pre_prompt_code);
		free(round_HTML_setup);
		free(prompt_HTML_setup);
		free(user_HTML_setup);
	} else if (player_dead){
	//The player IS dead.
		printf("<body> <button onclick=\"prompt();\"> Prompt </button>"
				"<button onclick=\"attr();\"> Attributes </button>"
				"<button onclick=\"history();\"> Choice History </button>"
				"<div id = \"prompt\">"
				"<div id=\"header_and_prompt\">"
				"<h1 style=\"color:black \"> <center> You're dead. Sorry. </center> </h1> </div> </div>");
		printf("<div id = \"attr\" style=\"display:none;\">");
		printf("<div id=\"playerattributes\"> <h1 style=\"color:black\"> <center> Player Attributes </center> </h1> <center> <table style=\"width:730px\">");
		printf("<tr><th colspan=\"2\"> Attributes</th> <th> Values </th> </tr>");
		if(split_attributes[0]) for (int i = 0; split_attributes[i]; i++){
      if(i==0)continue;
			char **attributes = split(split_attributes[i], '=');
			printf("<tr><td colspan=\"2\">%s</td><td>%s</td></tr>", attributes[0], attributes[1]);
			free_arr(attributes);
		}
		printf("</table> </center>");
		printf("</div><center><h1>");
		//for ()
		printf("<div id = \"history\" style=\"display:none;\">");
		printf("<center><h1>Choice History</h1>");
		printf("<table><tr><th>Round Number</th><th>Prompt</th><th>Choice</th></tr>");

		//Open and process player choice file.
		sprintf(player_choices_filename, "player/%s_choices.txt", user);

		char *player_choices = read_text(player_choices_filename);
		char **split_choices = split(player_choices, '\n');
    if(split_choices[0]) for (int i = 0; split_choices[i]; i++){
			char **choices = split(split_choices[i], ':');
      printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", choices[1], choices[2], choices[3]);
      free_arr(choices);
		}
		printf("</table></center></div>");
		printf("</body> </html>");

		free(postdata);
		free(user);
		free_arr(split_return);
		free_arr(split_attributes);
		free_arr(split_choices);
		free(player_attributes_filename);
		free(player_choices_filename);
	} else if (player_gulag){
	//The player IS gulaged.
		printf("<body> <button onclick=\"prompt();\"> Prompt </button>"
				"<button onclick=\"attr();\"> Attributes </button>"
				"<button onclick=\"history();\"> Choice History </button>"
				"<div id = \"prompt\">"
				"<div id=\"header_and_prompt\">"
				"<h1 style=\"color:black \"> <center> You're in the Gulag. Sorry. </center> </h1> </div> </div>");
		printf("<div id = \"attr\" style=\"display:none;\">");
		printf("<div id=\"playerattributes\"> <h1 style=\"color:black\"> <center> Player Attributes </center> </h1> <center> <table style=\"width:730px\">");
		printf("<tr><th colspan=\"2\"> Attributes</th> <th> Values </th> </tr>");
		for (int i = 0; split_attributes[i]; i++) {
      if(i==0)continue;
			char **attributes = split(split_attributes[i], '=');
			printf("<tr><td colspan=\"2\">%s</td><td>%s</td></tr>", attributes[0], attributes[1]);
			free_arr(attributes);
		}
		printf("</table> </center>");
		printf("</div><center><h1>");
		/// XXX FIXME BUGS for ()
		printf("<div id = \"history\" style=\"display:none;\">");
		printf("<center><h1>Choice History (All players must have decided)</h1>");
		printf("<table><tr><th>Round Number</th><th>Prompt</th><th>Choice</th></tr>");

		//Open and process player choice file.
		sprintf(player_choices_filename, "players/%s_choices.txt", user);

		char *player_choices = read_text(player_choices_filename);
		char **split_choices = split(player_choices, '\n');

		if(split_choices[0]) for (int i = 0; split_choices[i]; i++){
			char **choices = split(split_choices[i], ':');
			printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", choices[1], choices[2], choices[3]);
      free_arr(choices);
		}
		printf("</table></center></div>");
		printf("</body> </html>");

		free(postdata);
		free(user);
		free_arr(split_return);
		free_arr(split_attributes);
		free_arr(split_choices);
		free(player_attributes_filename);
		free(player_choices_filename);
	}
}
