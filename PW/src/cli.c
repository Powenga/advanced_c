#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int parse_cli(int argc, char *argv[], CliOptions *options) {
  // Init options
  options->show_interation_count = 0;
  options->show_intersection_dots = 0;
  options->show_help = 0;

  int result; // arguments
  opterr = 0; // hide error messsage

  while ((result = getopt(argc, argv, "hid")) != -1) {
    switch (result) {
    case 'h':
      options->show_help = 1;
      break;
    case 'i':
      options->show_intersection_dots = 1;
      break;
    case 'd':
      options->show_intersection_dots = 0;
      break;
    case '?':
      return 0;
    default:
      return 0;
    }
  }
  return 1;
}

void print_cli_usage(const char *prog) {
  printf("Usage: %s -h -d -i\n", prog);
}

void print_help(char *prog) {
  printf("Calculate area of three fucntions.\n");
  printf("Usage: %s -h -d -i.\n", prog);
  printf("\t-h - Help text;  \n");
  printf("\t-d - Show intersection dots");
  printf("\t-i - Show iteraction count");
}
