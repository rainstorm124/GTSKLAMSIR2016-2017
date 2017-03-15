/*
 * admin_interface_v1.c
 *
 *  Created on: Mar 15, 2017
 *      Author: rcb
 */

#include "zoinka.h"
#include "prompt.h"
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>
#include "gregutils.h"


int main(void){

	int round = get_round();

	//HTML header
	printf("Content-type: text/html\n\n");
	printf("<html><head><title>");
	printf("WELCOME TO THE GULAG\n");
	printf("</title>");

	//CSS Stylesheet.
	printf("<style>");
	printf("#header_and_prompt {position:absolute;width:1230px;height:200px;padding:2px;}");
	printf("#choice_left {position:absolute;top:210px;width:400px;height:1000px;padding:5px;float:left;}");
	printf("#choice_center {position:absolute;top:210px;left:410px;width:400px;padding:5px;height:1000px;float:left;}");
	printf("#choice_right {position:absolute;top:210px;left:820px;width:400px;padding:5px;height:1000px;float:left;}");
	printf("#adminattributes {position:relative;width:1230px;height:200px;float:left;}");
	printf("#choiceform #submitbutton(margin-left:120px;margin_top:5px;width:90px;}");
	printf("</style>");

	//Javascript-based Menu
	printf("<script>");
	printf("function prompt() { document.getElementbyId(\"prompt\").style.display=\"block\"; document.getElementbyId(\"attr\").style.display=\"none\"; document.getElementbyId(\"history\").style.display=\"none\";document.getElementbyId(\"players_chosen\").style.display=\"none\";}");
	printf("function attr() { document.getElementbyId(\"attr\").style.display=\"block\"; document.getElementbyId(\"prompt\").style.display=\"none\";document.getElementbyId(\"history\").style.display=\"none\";document.getElementbyId(\"players_chosen\").style.display=\"none\";}");
	printf("function history() { document.getElementbyId(\"history\").style.display=\"block\"; document.getElementbyId(\"prompt\").style.display=\"none\";document.getElementbyId(\"attr\").style.display=\"none\";document.getElementbyId(\"players_chosen\").style.display=\"none\";}");
	printf("function players_chosen() { document.getElementbyId(\"players_chosen\").style.display=\"block\"; document.getElementbyId(\"attr\").style.display=\"none\"; ocument.getElementbyId(\"history\").style.display=\"none\";ocument.getElementbyId(\"prompt\").style.display=\"none\";}");
	printf("</script>");
	//end of head
	printf("</head>");

	//Gets and processes environment variable
	char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = malloc(text_len + 1);
	fgets(postdata, text_len + 1, stdin);
	char *user = malloc(sizeof(char) * 1024 * 1024);
	char **split_return = split(postdata, '&');
	sscanf(split_return[0], "user=%s", user);

	//Prepares the admin's files for reading
	char *admin_attributes_filename = malloc(sizeof(char) * 1024 * 1024);
	char *admin_choices_filename = malloc(sizeof(char) * 1024 * 1024);
	sprintf(admin_attributes_filename, "%s_attributes.txt", user);

	//Reads them and processes them
	char *admin_attributes = read_text(admin_attributes_filename);
	char **split_attributes = split(admin_attributes, '/n');

	char *prompt_code = get_prompt(user, round);
	char **prompt_choices = get_options(prompt_code);
	char *prompt_text = get_prompt_text(user, prompt_code);
	char **prompt_choices_texts = malloc(sizeof(char*) * 3);
	for(int i = 0; i<3; i++)
	{
		prompt_choices_texts[i] = malloc(sizeof(char) * 100);
		strcpy(prompt_choices_texts[i],get_option_texts_given_codes(prompt_choices[i]));
	}
	char **pre_prompt_code = split(prompt_code, ';');

	char *round_HTML_setup = malloc(sizeof(char)*30);
	char *prompt_HTML_setup = malloc(sizeof(char)*30);
	char *user_HTML_setup = malloc(sizeof(char)*30);

	sprintf(round_HTML_setup,"<input type=\"hidden\" name=\"round\" id=\"round\" value=\"%s\">", pre_prompt_code[1]);
	sprintf(prompt_HTML_setup = "<input type=\"hidden\" name=\"prompt\" id=\"prompt\" value=\"%s\">", pre_prompt_code[2]);
	sprintf(user_HTML_setup = "<input type=\"hidden\" name=\"name\" id=\"name\" value=\"%s\">", pre_prompt_code[0]);

	printf("<body> <button onclick=\"prompt();\"> Prompt </button>"
			"<button onclick=\"attr();\"> Attributes </button>"
			"<button onclick=\"history();\"> Choice History </button>"
			"<button onclick=\"players_chosen();\"> Player Status </button>"
			"<div id = \"prompt\">"
			"<div id=\"header_and_prompt\">"
			"<h1 style=\"color:black \"> <center> %s </center> </h1> </div>", prompt_text);
	printf("<div id=\"choice_left\"> <h1 style=\"color:black\"> <center> %s </center> </h1>", prompt_choices_texts[0]);
	printf("<center> <form id=\"choiceform\" action=\"admin_choice.cgi\">"
			"%s %s %s <input type=\"hidden\" name=\"adminchoice\" id=\"adminchoice\" value=\"1\">"
			"<input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\"> <\form> <\center> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup);
	printf("<body><div id=\"header_and_prompt\"> <h1 style=\"color:black \"> <center> %s </center> </h1> </div>", prompt_text);
	printf("<div id=\"choice_center\"> <h1 style=\"color:black\"> <center> %s </center> </h1>", prompt_choices_texts[0]);
	printf("<center> <form id=\"choiceform\" action=\"admin_choice.cgi\">"
			"%s %s %s <input type=\"hidden\" name=\"adminchoice\" id=\"adminchoice\" value=\"2\">"
			"<input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\"> <\form> <\center> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup);
	printf("<body><div id=\"header_and_prompt\"> <h1 style=\"color:black \"> <center> %s </center> </h1> </div>", prompt_text);
	printf("<div id=\"choice_right\"> <h1 style=\"color:black\"> <center> %s </center> </h1>", prompt_choices_texts[0]);
	printf("<center> <form id=\"choiceform\" action=\"admin_choice.cgi\"> <input type=\"hidden\" name=\"adminchoice\" id=\"adminchoice\" value=\"3\">"
			"%s %s %s <input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\">"
			"</form> </center> </div> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup);
	printf("<div id = \"attr\" style=\"display:none;\"");
	printf("<div id=\"adminattributes\"> <h1 style=\"color:black\"> <center> admin Attributes </center> </h1> <center> <table style=\"width:730px\">");
	printf("<tr><th colspan=\"2\"> Attributes</th> <th> Values> </th> </tr>");
	for (int i = 0; split_attributes[i]; i++)
	{
		char **attributes = split(split_attributes, '=');
		printf("<tr><td colspan=\"2\">%s</td><td>%s</td></tr>", attributes[0], attributes[1]);
		free_arr(attributes);
	}
	printf("</table> </center>");
	printf("</div></div>");
	printf("<div id = \"history\" style=\"display:none;\">");
	printf("<center><h1>Choice History</h1>");
	printf("<table><tr><th>Round Number</th><th>Prompt</th><th>Choice</th></tr>");

	//Open and process admin choice file.
	sprintf(admin_choices_filename, "%s_choices.txt", user);

	char *admin_choices = read(admin_choices_filename);
	char **split_choices = split(admin_choices, '/n');

	for (int i = 0; split_choices[i]; i++){
		char **choices = split(split_attributes, ':');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", choices[1], choices[2], choices[3]);
	}
	printf("</table></center></div>");

	printf("<div id = \"players_chosen\" style=\"display:none;\">");
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
	printf("</table></center></div>");
	printf("</body> </html>");

	free(text_length);
	free(postdata);
	free(user);
	free_arr(split_return);
	free_arr(split_attributes);
	free_arr(split_choices);
	free(admin_attributes_filename);
	free(admin_choices_filename);
	free(prompt_code);
	free_arr(prompt_choices);
	free_arr(prompt_choices_texts);
	free_arr(pre_prompt_code);
	free(round_HTML_setup);
	free(prompt_HTML_setup);
	free(user_HTML_setup);
}
