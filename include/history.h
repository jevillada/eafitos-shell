#ifndef HISTORY_H
#define HISTORY_H

#define HISTORY_CAPACITY 10
#define HISTORY_ENTRY_MAX 256

void history_add(const char *line);
void history_print(void);

#endif
