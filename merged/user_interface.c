/*
 * admin_interface_v1.c
 *
 *  Created on: Mar 15, 2017
 *      Author: rcb, greg, nick
 */

#include "zoinka.h"
#include "prompt.h"
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>
#include "gregutils.h"


int main(void){
  print_header();
	int round = get_round();

	//HTML header
	printf("<html><head><title>");
	printf("The Soviet Great Terror Simulation\n");
	printf("</title>");
  //Gets and processes environment variables
	char *text_length = getenv("CONTENT_LENGTH");
	long int text_len = strtol(text_length, NULL, 10);
	char *postdata = malloc(text_len + 1);
	fgets(postdata, text_len + 1, stdin);
	char *user = malloc(sizeof(char) * 4096);
	char **split_return = split(postdata, '&');
	sscanf(split_return[0], "user=%s", user);
  // stalin is the admin
  bool admin = !strcmp("STA", get_type(user));

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
	printf("function prompt() { document.getElementById(\"prompt\").style.display=\"block\"; document.getElementById(\"attr\").style.display=\"none\"; document.getElementById(\"history\").style.display=\"none\";document.getElementById(\"players_chosen\").style.display=\"none\";}");
	printf("function attr() { document.getElementById(\"attr\").style.display=\"block\"; document.getElementById(\"prompt\").style.display=\"none\";document.getElementById(\"history\").style.display=\"none\";document.getElementById(\"players_chosen\").style.display=\"none\";}");
	printf("function history() { document.getElementById(\"history\").style.display=\"block\"; document.getElementById(\"prompt\").style.display=\"none\";document.getElementById(\"attr\").style.display=\"none\";document.getElementById(\"players_chosen\").style.display=\"none\";}");
	if(admin)printf("function players_chosen() { document.getElementById(\"players_chosen\").style.display=\"block\"; document.getElementById(\"attr\").style.display=\"none\"; document.getElementById(\"history\").style.display=\"none\";document.getElementById(\"prompt\").style.display=\"none\";}");
	printf("</script>");
	//end of head
	printf("</head>");
  
  char *prompt_code = get_prompt_code(user, round);
  printf("<!-- prompt_code = %s -->", prompt_code);
	char **prompt_choices = get_option_codes(prompt_code);
  // get the prompt text
	char *prompt_text = get_prompt_text(prompt_code);
  //get the option texts
	char **option_texts = calloc(50, sizeof(char*));
  int num_options = 0;
	for(int i = 0; prompt_choices[i]; i++, num_options++) {
    char *option_special = calloc(sizeof(char), 1024);
    sprintf(option_special, "%s:%d", prompt_code, i + 1);
		option_texts[i] = malloc(sizeof(char) * 512);
		strcpy(option_texts[i],get_option_text(option_special));
    free(option_special);
	}
  
	char **pre_prompt_code = split(prompt_code, ':');
  char *round_HTML_setup = calloc(sizeof(char), 512);
	char *prompt_HTML_setup = calloc(sizeof(char), 512);
	char *user_HTML_setup = calloc(sizeof(char), 512);  

	sprintf(round_HTML_setup, "<input type=\"hidden\" name=\"round\" id=\"round\" value=\"%s\">", pre_prompt_code[1]);
	sprintf(prompt_HTML_setup, "<input type=\"hidden\" name=\"prompt\" id=\"prompt\" value=\"%s\">", pre_prompt_code[2]);
	sprintf(user_HTML_setup, "<input type=\"hidden\" name=\"user\" id=\"user\" value=\"%s\">", pre_prompt_code[0]);

	printf("<body background = \"/greg/background.png\"> <button onclick=\"prompt();\"> Prompt </button>"
			"<button onclick=\"attr();\"> Attributes </button>"
			"<button onclick=\"history();\"> Choice History </button>"
			"<button onclick=\"players_chosen();\"> Player Status </button>"
      "<label> <b>Round %d</b></label>"
			"<div id = \"prompt\">"
			"<div id=\"header_and_prompt\">"
			"<h1 style=\"color:black \"> <center> %s </center> </h1>", round, prompt_text);
  // check to see if we have already chosen
  char *code = get_user_choice(user);
  bool chosenp = (code != NULL);
  // this was better
  /*char *sn = calloc(snprintf(NULL, 0, "\n%s:", user)+1, sizeof(char));
  sprintf(sn, "\n%s:", user)
  if(strstr(update_text(*/
  // not always 3 opts
  if(!chosenp){
    for(int i = 0; i < num_options; i++){
       char* posn;
       switch(i){
       case 0:
         posn = "left";
         break;
       case 1:
         posn = "center";
         break;
       case 2:
         posn = "right";
         break;
       }
       printf("<div id=\"choice_%s\"> <h3 style=\"color:black\"> Option %d:<br><center> %s </center> </h3>", posn, i+1, option_texts[i]);
       printf("<center> <form id=\"choiceform\" action=\"user_choice.cgi\" method = \"post\">"
            "%s %s %s <input type=\"hidden\" name=\"choice\" id=\"choice\" value=\"%d\">"
            "<input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\">"
             "</form> </center> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup, i+1);
     }
  }else{
    char *txt = get_option_text(code);
    printf("<p>You have already chosen the option &quot;<!--%s-->%s&quot;.</p><br />", code, txt); 
  }
  printf("</div> </div>");    
	printf("<div id = \"attr\" style=\"display:none;\">");
	printf("<div id=\"attributes\"> <h1 style=\"color:black\"> <center> Your Attributes </center> </h1> <center> <table style=\"width:730px\">");
	printf("<tr><th colspan=\"2\"> Attributes</th> <th> Values </th> </tr>");
	
  free(round_HTML_setup);
  free(prompt_HTML_setup);
	free(user_HTML_setup);

  //Prepares the user's files for reading
	char *attributes_filename = calloc(4096, sizeof(char));
	sprintf(attributes_filename, "players/%s_attributes.txt", user);

	//Reads them and processes them
	char *attributes = read_text(attributes_filename);
	char **split_attributes = split(attributes, '\n');
  free(attributes);
  
  for (int i = 0; split_attributes[i]; i++) {
    if(i==0)continue;
		char **attributes = split(split_attributes[i], '=');
		printf("<tr><td colspan=\"2\">%s</td><td>%s</td></tr>", attributes[0], attributes[1]);
		free_arr(attributes);
	}
  free_arr(split_attributes);
	printf("</table> </center>");
	printf("</div></div>");
	printf("<div id = \"history\" style=\"display:none;\">");
  printf("<center><h3>Choice History during previous rounds</h3>");
	printf("<table><tr><th>Round Number</th><th>Prompt</th><th>Choice</th></tr>");

	//Open and process admin choice file.
  char *choices_filename = calloc(4096, sizeof(char));
	sprintf(choices_filename, "players/%s_choices.txt", user);
	char *choices = read_text(choices_filename);
	char **split_choices = split(choices, '\n');
  free(choices_filename);
  free(choices);

	for (int i = 0; split_choices[i]; i++){
		char **choices = split(split_choices[i], ':');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", choices[1], choices[2], choices[3]);
    free_arr(choices);
	}
  free_arr(split_choices);
	printf("</table></center></div>");

	printf("<div id = \"players_chosen\" style=\"display:none;\">");
	if(!admin) goto _not_admin;
  printf("<center><h1> Players Chosen </h1>");
	printf("<table><tr><th>Player Name</th><th>Chosen?</th></tr>");
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
  printf("</table></center>");
  printf("<br><b>Advance the Round?</b><br><form action=\"forced_update.cgi\"> <input type=\"submit\" name=\"force_update\" id=\"force_update\"> </form>");
  _not_admin: printf("</div>");
	printf("</body> </html>");
}
