#include "gregutils.h"

int main(int argc, char **argv){
  print_header();
  char *html_text = read_text("reset.html");
  printf("%s", html_text);
  free(html_text);
  return 1;
}