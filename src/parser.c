#include "parser.h"
#include <string.h>

int parse_line(char *line, char **argv, int max_tokens) {
    int argc = 0;
    char *token = strtok(line, " \t");

    while (token != NULL && argc < max_tokens - 1) {
        argv[argc++] = token;
        token = strtok(NULL, " \t");
    }

    argv[argc] = NULL;
    return argc;
}
