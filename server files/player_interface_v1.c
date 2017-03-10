#import <stdio.h>
#import <strings.h>
#import "prompt.h"

int main(int argc, char **argv){
	print_header();
	printf("<html><head>\n");
	printf("<title>WELCOME TO THE GULAG</title>");
	printf("<style>");
	printf("#header_and_prompt {position:absolute;width:1230px;height:200px;padding:2px;}");
	printf("#choice_left {position:absolute;top:210px;width:400px;height:1000px;padding:5px;float:left;}");
	printf("#choice_center {position:absolute;top:210px;left:410px;width:400px;padding:5px;height:1000px;float:left;}");
	printf("#choice_right {position:absolute;top:210px;left:820px;width:400px;padding:5px;height:1000px;float:left;}")
	printf("#playerattributes {position:relative;width:1230px;height:200px;float:left;}");
	printf("#choiceform #submitbutton(margin-left:120px;margin_top:5px;width:90px;}");
	printf("</style>");
	printf("</head><body background='/greg/background.png'>");
	
	char *len_ = getenv("CONTENT_LENGTH");
	long int len = strtol(len_, NULL, 10);
	char *postdata = malloc(len + 1);
	fgets(postdata, len + 1, stdin);
	char *user = calloc(sizeof(char), len+1);
	char **split_return = split(postdata, '&');
	sscanf(split_return[0], "user=%s", user);
	
	char *player_attributes_filename = calloc(sizeof(char), len + 20);
	char *player_choices_filename = calloc(sizeof(char), len + 20);
	sprintf(player_attributes_filename, "%s_attributes.txt", user);
	
	char *player_attributes = read_text(player_attributes_filename);
	char **split_attributes = split(player_attributes, '\n');
	
	free(player_attributes_filename);
	
	char *prompt_code = get_prompt(user);
	char **prompt_choices = get_options(prompt_code);
	char *prompt_text = get_prompt_text(user, prompt_code);
	char **prompt_choices_texts = malloc(size_of(char*) * 3);
	for(int i = 0; i<3; i++) {
		prompt_choices_texts[i] = malloc(sizeof(char) * 100);
		prompt_choices_texts[i] = get_option_texts_given_codes(prompt_choices[i]);
	}
	
	// print out the body main text
	printf("<div id="header_and_prompt"> <h1 style="color:black"> <center> %s </center> </h1> </div>", prompt_text);
	printf("<div id="choice_left"> <h1 style="color:black"> <center> %s </center> </h1>", prompt_choices_texts[0]);
	printf("<center> <form id="choiceform"> <input type="hidden" name="playerchoice" id="playerchoice" value="1"> <input type ="submit" name="submitbutton" id="submitbutton"> </form> </center> </div>");
	printf("<body><div id="header_and_prompt"> <h1 style="color:black"> <center> %s </center> </h1> </div>", prompt_text);
	printf("<div id="choice_center"> <h1 style="color:black"> <center> %s </center> </h1>", prompt_choices_texts[1]);
	printf("<center> <form id="choiceform"> <input type="hidden" name="playerchoice" id="playerchoice" value="2"> <form id="choiceform"> <input type ="submit" name="submitbutton" id="submitbutton"> </form> </center> </div>");
	printf("<body><div id="header_and_prompt"> <h1 style="color:black"> <center> %s </center> </h1> </div>", prompt_text);
	printf("<div id="choice_center"> <h1 style="color:black"> <center> %s </center> </h1>", prompt_choices_texts[2]);
	printf("<center> <form id="choiceform"> <input type="hidden" name="playerchoice" id="playerchoice" value="3"> <input type ="submit" name="submitbutton" id="submitbutton"> </form> </center> </div>");
	printf("<div id="playerattributes"> <h1 style="color:black"> <center> Player Attributes </center> </h1> <center> <table style="width:730px">");
	printf("<tr><th colspan="2"> Attributes</th> <th> Values> </th> </tr>");
	// print the attributes
	for (int i = 0; split_attributes[i]; i++) {
		char **attributes = split(split_attributes, '=');
		printf("<tr><td colspan="2">%s</td><td>%s</td></tr>", attributes[0], attributes[1]);
	}
	// end the text
	printf("</table> </center>");
	printf("</body> </html>");
}