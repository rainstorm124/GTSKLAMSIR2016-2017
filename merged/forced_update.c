/*
 * forced_update.c
 *
 *  Created on: Mar 15, 2017
 *      Author: rcb
 */
#include "gregutils.h"
#include "prompt.h"
#include "prompt_chooser.h"
#include "zoinka.h"
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>

int main(void){
  print_header();
	char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = malloc(text_len + 1);
	fgets(postdata, text_len + 1, stdin);
	char *choice = malloc(sizeof(char) * 1024 * 1024);
	char **split_return = split(postdata, '&');
	char *character_name = malloc(sizeof(char) * 1024);
	sscanf(split_return[2], "name=%s", character_name);
	char *user_HTML_setup = malloc(sizeof(char)*30);
	sprintf(user_HTML_setup, "<input type=\"hidden\" name=\"name\" id=\"name\" value=\"%s\">", split_return[2]);

	admin_override();
	int round = get_round();
	round++;
	set_round(round);

	if (count_players_chosen("update_file.txt") == count_nav_lines()){
		printf("<html><head><title>");
		printf("WELCOME TO THE GULAG\n");
		printf("</title>");
		printf("<body> <h1> All updates in this round made. Please press the button below to continue. </h1>");
		printf("<form action = admin_interface.cgi>"
			"%s"
			"<input type=\"submit\" name = \"submitbutton\" id=\"submitbutton\"> </form>", user_HTML_setup);
		printf("</body></html>");
	}
}
