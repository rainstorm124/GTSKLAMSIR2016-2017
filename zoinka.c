//A file for functions concerning updating, checking player chosen counts, etc.

#include "prompt.h"
#include "gregutils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int main(int argc, char **argv){
	return 0;
}

char* add_update_to_queue(char* input_code)
{
	FILE *file;
	while (file = fopen("lock_file.txt", "r"))
		fclose(file);
	file = fopen("lock_file.txt", "w");
	fclose(file);
	FILE *fp = fopen("update_file.txt", "a+");
	fprintf(fp, "%s\n", input_code);
	if(count_players_chosen(fp) == MAX_PLAYERS)
		char *raw_updates = malloc(sizeof(char) *1024 * 1024);
		raw_updates = read_text(fp);
		char **raw_updates_lines = split(raw_updates, '/n');
		char **targets_for_updates = malloc(sizeof(char) * 1024 * 1024);
		for (int i = 0; raw_updates_lines[i]; i++)
		{
			targets_for_updates = get_targets(raw_updates_lines[i]);
			do_option(targets_for_updates, raw_update_lines[i]);
		}
	fclose(fp);
	fp = fopen("update_file.txt", "w");
	fclose(fp);
	unlink(file);
}

int count_players_chosen(FILE *fp)
{
	char* file_to_count = read_text(fp);
	int i = 0;
	char** file_lines = split(file_to_count, '/n');
	for (i = 0; file_lines[i]; i++)
		continue;
	return i;
}