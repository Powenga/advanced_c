#ifndef CLI_H
#define CLI_H

#include <stdint.h>

typedef struct {
  uint8_t show_interation_count;
  uint8_t show_intersection_dots;
  uint8_t show_help;
  uint8_t test;
} CliOptions;

int parse_cli(int argc, char *argv[], CliOptions *options);
void print_cli_usage(const char *prog);
void print_help(char *prog);

#endif