#include "commands.h"
#include "history.h"

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <sys/types.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

int cmd_historial(int argc, char **argv) {
    (void)argc;
    (void)argv;
    history_print();
    return 0;
}

int cmd_limpiar(int argc, char **argv) {
    (void)argc;
    (void)argv;
    printf("\033[2J\033[H");
    fflush(stdout);
    return 0;
}

int cmd_usuario(int argc, char **argv) {
    (void)argc;
    (void)argv;

    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw != NULL) {
        printf("Usuario: %s (UID: %d)\n", pw->pw_name, (int)uid);
    } else {
        printf("UID actual: %d\n", (int)uid);
    }

    return 0;
}

int cmd_directorio(int argc, char **argv) {
    (void)argc;
    (void)argv;

    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return 1;
    }

    printf("%s\n", cwd);
    return 0;
}
