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
  print_header();
	int round = get_round();

	//HTML header
	printf("<html><head><title>");
	printf("The Soviet Great Terror Simulation\n");
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
	printf("function prompt() { document.getElementById(\"prompt\").style.display=\"block\"; document.getElementById(\"attr\").style.display=\"none\"; document.getElementById(\"history\").style.display=\"none\";document.getElementById(\"players_chosen\").style.display=\"none\";}");
	printf("function attr() { document.getElementById(\"attr\").style.display=\"block\"; document.getElementById(\"prompt\").style.display=\"none\";document.getElementById(\"history\").style.display=\"none\";document.getElementById(\"players_chosen\").style.display=\"none\";}");
	printf("function history() { document.getElementById(\"history\").style.display=\"block\"; document.getElementById(\"prompt\").style.display=\"none\";document.getElementById(\"attr\").style.display=\"none\";document.getElementById(\"players_chosen\").style.display=\"none\";}");
	printf("function players_chosen() { document.getElementById(\"players_chosen\").style.display=\"block\"; document.getElementById(\"attr\").style.display=\"none\"; document.getElementById(\"history\").style.display=\"none\";document.getElementById(\"prompt\").style.display=\"none\";}");
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
  
  char *prompt_code = get_prompt_code(user, round);
  printf("<!-- prompt_code = %s -->", prompt_code);
	char **prompt_choices = get_option_codes(prompt_code);
	char *prompt_text = get_prompt_text(user, prompt_code);
	char **prompt_choices_texts = calloc(50, sizeof(char*));
  
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

	sprintf(round_HTML_setup, "<input type=\"hidden\" name=\"round\" id=\"round\" value=\"%s\">", pre_prompt_code[1]);
	sprintf(prompt_HTML_setup, "<input type=\"hidden\" name=\"prompt\" id=\"prompt\" value=\"%s\">", pre_prompt_code[2]);
	sprintf(user_HTML_setup, "<input type=\"hidden\" name=\"name\" id=\"name\" value=\"%s\">", pre_prompt_code[0]);

	printf("<body background = \"/greg/background.png\"> <button onclick=\"prompt();\"> Prompt </button>"
			"<button onclick=\"attr();\"> Attributes </button>"
			"<button onclick=\"history();\"> Choice History </button>"
			"<button onclick=\"players_chosen();\"> Player Status </button>"
			"<div id = \"prompt\">"
			"<div id=\"header_and_prompt\">"
			"<h1 style=\"color:black \"> <center> %s </center> </h1> </div>", prompt_text);
      
  for(int i = 0; i < num_options; i++){
    switch(i){
    case 0:
      printf("<div id=\"choice_left\"> <h3 style=\"color:black\"> Option 1:<br><center> %s </center> </h3>", prompt_choices_texts[i]);
      printf("<center> <form id=\"choiceform\" action=\"admin_choice.cgi\" method = \"post\">"
          "%s %s %s <input type=\"hidden\" name=\"adminchoice\" id=\"adminchoice\" value=\"1\">"
          "<input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\">"
          "</form> </center> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup);
      break;
    case 1:
      printf("<div id=\"choice_center\"> <h3 style=\"color:black\"> Option 2:<br><center> %s </center> </h3>", prompt_choices_texts[i]);
      printf("<center> <form id=\"choiceform\" action=\"admin_choice.cgi\" method = \"post\">"
          "%s %s %s <input type=\"hidden\" name=\"adminchoice\" id=\"adminchoice\" value=\"2\">"
          "<input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\">"
          "</form> </center> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup);
      break;
    case 2:
      printf("<div id=\"choice_right\"> <h3 style=\"color:black\"> Option 3:<br><center> %s </center> </h3>", prompt_choices_texts[i]);
      printf("<center> <form id=\"choiceform\" action=\"admin_choice.cgi\" method = \"post\">"
          "%s %s %s <input type=\"hidden\" name=\"adminchoice\" id=\"adminchoice\" value=\"3\">"
          "<input type =\"submit\" name=\"submitbutton\" id=\"submitbutton\">"
          "</form> </center> </div>", round_HTML_setup, prompt_HTML_setup, user_HTML_setup);
      break;
    }
  }   
  printf("</div>");    
	printf("<div id = \"attr\" style=\"display:none;\">");
	printf("<div id=\"adminattributes\"> <h1 style=\"color:black\"> <center> Admin Attributes </center> </h1> <center> <table style=\"width:730px\">");
	printf("<tr><th colspan=\"2\"> Attributes</th> <th> Values </th> </tr>");
	
  free(round_HTML_setup);
  free(prompt_HTML_setup);
	free(user_HTML_setup);

  //Prepares the admin's files for reading
	char *admin_attributes_filename = calloc(4096, sizeof(char));
	sprintf(admin_attributes_filename, "players/%s_attributes.txt", user);

	//Reads them and processes them
	char *admin_attributes = read_text(admin_attributes_filename);
	char **split_attributes = split(admin_attributes, '\n');
  free(admin_attributes);
  
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
	printf("<center><h1>Choice History (All players must have decided)</h1>");
	printf("<table><tr><th>Round Number</th><th>Prompt</th><th>Choice</th></tr>");

	//Open and process admin choice file.
  char *admin_choices_filename = calloc(4096, sizeof(char));
	sprintf(admin_choices_filename, "players/%s_choices.txt", user);
	char *admin_choices = read_text(admin_choices_filename);
	char **split_choices = split(admin_choices, '\n');
  free(admin_choices_filename);
  free(admin_choices);

	for (int i = 0; split_choices[i]; i++){
		char **choices = split(split_choices[i], ':');
		printf("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", choices[1], choices[2], choices[3]);
    free_arr(choices);
	}
  free_arr(split_choices);
	printf("</table></center></div>");

	printf("<div id = \"players_chosen\" style=\"display:none;\">");
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
	printf("</table></center></div>");
	printf("</body> </html>");
}
