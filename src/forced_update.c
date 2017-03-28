/*
 * forced_update.c
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
	char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = malloc(text_len + 1);
	fgets(postdata, text_len + 1, stdin);
	char choice[1024];
	char **split_return = split(postdata, '&');
	char user[1024];
	sscanf(split_return[0], "user=%s", user);

	admin_override();

	//if (count_players_chosen("update_file.txt") == count_nav_lines()){
		printf("<html><head>\n<title>The Soviet Great Terror Simulation\n</title>\n");
    printf("<script type=\"text/javascript\">function loaded(e){ document.forms[0].submit.click();}</script>\n</head>");
		printf("<body onload=\"loaded();\"> <h1> Round forcefully advanced. Please press the button below to continue or wait 3 seconds. </h1>");
		printf("<form action = user_interface.cgi><input type='hidden' name='user' id='user' value='%s' /><input type=\"submit\" name = \"submitbutton\" id=\"submitbutton\"> </form>", user);
		printf("</body></html>");
	/*}else{
    printf("<html><head><title>ERROR?</title> </head>");
		printf("<body> <h1> Warning: not everyone in this round has updated.  Press the button below to try again! </h1>");
		printf("<form action = forced_update.cgi> %s <input type='hidden' name='user' id='user' value='%s' /> <input type=\"submit\" name = \"submitbutton\" id=\"submitbutton\"> </form>", user_HTML_setup, user);
		printf("</body></html>");
  }*/
}
