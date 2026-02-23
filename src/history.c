#include "history.h"
#include <stdio.h>
#include <string.h>

static char history_buffer[HISTORY_CAPACITY][HISTORY_ENTRY_MAX];
static int history_count = 0;
static int history_start = 0; /* índice del más antiguo */

void history_add(const char *line) {
    if (line == NULL || line[0] == '\0') return;

    int index;
    if (history_count < HISTORY_CAPACITY) {
        index = (history_start + history_count) % HISTORY_CAPACITY;
        history_count++;
    } else {
        index = history_start;
        history_start = (history_start + 1) % HISTORY_CAPACITY;
    }

    strncpy(history_buffer[index], line, HISTORY_ENTRY_MAX - 1);
    history_buffer[index][HISTORY_ENTRY_MAX - 1] = '\0';
}

void history_print(void) {
    if (history_count == 0) {
        printf("Historial vacío.\n");
        return;
    }

    for (int i = 0; i < history_count; i++) {
        int index = (history_start + i) % HISTORY_CAPACITY;
        printf("%d. %s\n", i + 1, history_buffer[index]);
    }
}
