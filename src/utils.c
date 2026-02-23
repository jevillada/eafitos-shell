#include "utils.h"
#include <stdio.h>
#include <string.h>

void strip_newline(char *s) {
    if (s == NULL) return;

    size_t len = strlen(s);

    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[len - 1] = '\0';
        len--;
    }
}

void print_prompt(void) {
    printf("\033[1;32mEAFITos>\033[0m ");
    fflush(stdout);
}

void print_error(const char *msg) {
    fprintf(stderr, "\033[1;31mError:\033[0m %s\n", msg);
}
