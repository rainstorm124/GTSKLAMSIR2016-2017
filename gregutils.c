#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED
#define _GNU_SOURCE
#include <unistd.h>
#include "gregutils.h"
#include <time.h>
#include <string.h>


char* read_text(char *filename){
  FILE *fp = fopen(filename, "r");
  if(!fp){
		printf("File \"%s\" not found\n", filename);
		return NULL;
	}
  char c;
  int num = 0;
  while((c=fgetc(fp)) != EOF){
    if(c == '\r') continue;
    num++;
  }
  fseek(fp, 0, SEEK_SET);
  char *total = calloc(sizeof(char), num + 1);
  int i = 0;
  while((c=fgetc(fp)) != EOF){
    if(c == '\r') continue;
    total[i] = c;
    i++;
  }
  total[i] = '\0';
  fclose(fp);
  return total;
}

/*char* read_text(char *filename){
	FILE *fp = fopen(filename, "r");
	if(!fp){
		printf("File \"%s\" not found\n", filename);
		return NULL;
	}	
	fseek(fp, 0, SEEK_END);
	size_t length = ftell(fp);
  printf("length = %d\n", length);
	fseek(fp, 0, SEEK_SET);
	char *data = calloc(sizeof(char), (length + 1));
	fread(data, sizeof(char), length, fp);
	fclose(fp);
  data[length] = '\0';
	return data;
}*/

char** split(char *src, char delimiter){
	int element_count = 1;
	for(int i = 0; src[i]; i++){
		if(src[i] != delimiter)continue;
    if(src[i+1] != '\0' && src[i+1] != delimiter) element_count++;
	}
	char **arr = calloc(sizeof(char*), (element_count + 1));
	for(int i = 0, index = 0; i < element_count; i++){
		int word_length = 0;
		while(src[index + word_length] && src[index + word_length] != delimiter) word_length++;
		arr[i] = calloc(sizeof(char), (word_length + 1));
		memcpy(arr[i], src+index, word_length);
    //for(int j = 0; j < word_length; j++){
		//	arr[i][j] = src[index + j];
		//}
		arr[i][word_length] = '\0';
		index += word_length;
    // skip all delimiters
    while(src[index] == delimiter)index++;
	}
	arr[element_count] = NULL;
	return arr;	
}

void free_arr(char **arr){
	for(int i = 0; *(arr + i); i++){
		free(*(arr + i));
	}
	free(arr);
}

int grandom(int max){
	if(max <= 0) return 0;
	return (rand() + 1) % max;
}

void print_arr(char **arr){
  for(int i = 0; arr[i]; i++){
    printf("[%d] = %s\n", i, arr[i]);
  }
}

void print_header(){
	puts("Content-type: text/html\n");
}
#ifdef __MINGW32__
char *crypt(char *pass, const char *b){
	return pass;
}
#endif
char *hash_pw(char *pass){
	const char *salt = "$6$eM6XDFpkQy0IWZOy$";
	return strdup(crypt(pass, salt));
}

int check_pass(char *user, char *pass, char *pswd_file){
	char *fulltext = read_text(pswd_file);
	char **arr = split(fulltext, '\n');
	int retval = 0;
	for(int i = 0; arr[i]; i++){
      char **line = split(arr[i], '=');
	  if(strcmp(line[0], user)==0){
		  char *hash = hash_pw(pass);
		  retval = !strcmp(hash, line[1]);
		  free(hash);
	  }
	  free_arr(line);
	  break;
    }
	free_arr(arr);
	free(fulltext);
	return retval;
}