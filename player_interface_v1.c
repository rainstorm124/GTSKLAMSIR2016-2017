/*
 * player_interface_v1.c
 *
 *  Created on: Mar 8, 2017
 *      Author: rcb
 */


#include <stdio.h>
#include <strings.h>
#include "prompt.h"
#include "gregutils.h"

int main(void)
{
	printf("Content-type: text/html\n\n");
	printf("<html><head><title>");
	printf("WELCOME TO THE GULAG\n");
	printf("</title>");
	printf("<style>");
	printf("#header_and_prompt {position:absolute;width:1230px;height:200px;padding:2px;}");
	printf("#choice_left {position:absolute;top:210px;width:400px;height:1000px;padding:5px;float:left;}");
	printf("#choice_center {position:absolute;top:210px;left:410px;width:400px;padding:5px;height:1000px;float:left;}");
	printf("#choice_right {position:absolute;top:210px;left:820px;width:400px;padding:5px;height:1000px;float:left;}");
	printf("#playerattributes {position:relative;width:1230px;height:200px;float:left;}");
	printf("#choiceform #submitbutton(margin-left:120px;margin_top:5px;width:90px;}");
	printf("</style>");
	printf("</head>");

	char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = malloc(text_len + 1);
	fgets(postdata, text_len + 1, stdin);
	char *user = malloc(sizeof(char) * 1024 * 1024);
	char **split_return = split(postdata, '&');
	sscanf(split_return[0], "user=%s", user);

	char *player_attributes_filename = malloc(sizeof(char) * 1024 * 1024);
	char *player_choices_filename = malloc(sizeof(char) * 1024 * 1024);
	sprintf(player_attributes_filename, "%s_attributes.txt", user);

	char *player_attributes = read(player_attributes_filename);
	char **split_attributes = split(player_attributes, '/n');

	char *prompt_code = get_prompt(user);
	char **prompt_choices = get_options(prompt_code);
	char *prompt_text = get_prompt_text(user, prompt_code);
	char **prompt_choices_texts = malloc(sizeof(char*) * 3);
	for(int i = 0; i<3; i++)
	{
		prompt_choices_texts[i] = malloc(sizeof(char) * 100);
		prompt_choices_texts[i] = get_option_texts_given_codes(prompt_choices[i]);
	}


	printf("<body><div id=\"header_and_prompt\"> <h1 style=\"color:black \"> <center> %s </center> </h1> </div>", prompt_text);
	printf("<div id=\"choice_left\"> <h1 style=\"color:black\"> <center> %s </center> </h1>", prompt_choices_texts[0]);
	printf("<center> <form id=\"choiceform\"> <input type=\"hidden\" name=\"playerchoice\" id=\"playerchoice\" value=\"1\"> <input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\"> <\form> <\center> </div>");
	printf("<body><div id=\"header_and_prompt\"> <h1 style=\"color:black \"> <center> %s </center> </h1> </div>", prompt_text);
	printf("<div id=\"choice_center\"> <h1 style=\"color:black\"> <center> %s </center> </h1>", prompt_choices_texts[0]);
	printf("<center> <form id=\"choiceform\"> <input type=\"hidden\" name=\"playerchoice\" id=\"playerchoice\" value=\"2\"> <input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\"> <\form> <\center> </div>");
	printf("<body><div id=\"header_and_prompt\"> <h1 style=\"color:black \"> <center> %s </center> </h1> </div>", prompt_text);
	printf("<div id=\"choice_right\"> <h1 style=\"color:black\"> <center> %s </center> </h1>", prompt_choices_texts[0]);
	printf("<center> <form id=\"choiceform\"> <input type=\"hidden\" name=\"playerchoice\" id=\"playerchoice\" value=\"3\"> <input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\"> <\form> <\center> </div>");
	printf("<div id=\"playerattributes\"> <h1 style=\"color:black\"> <center> Player Attributes </center> </h1> <center> <table style=\"width:730px\">");
	printf("<tr><th colspan=\"2\"> Attributes</th> <th> Values> </th> </tr>");
	for (int i = 0; split_attributes[i]; i++)
	{
		char **attributes = split(split_attributes, '=');
		printf("<tr><td colspan=\"2\">%s</td><td>%s</td></tr>", attributes[0], attributes[1]);
	}
	printf("</table> </center>");
	printf("</body> </html>");
}