#include "shell.h"
#include "parser.h"
#include "commands.h"
#include "history.h"
#include "utils.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int g_running = 1;

static void handle_sigint(int sig) {
    (void)sig;
    const char msg[] = "\nUsa 'salir' para terminar.\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

void shell_request_exit(void) {
    g_running = 0;
}

void shell_run(void) {
    char line[MAX_LINE_LENGTH];
    char *argv[MAX_TOKENS];

    /* Manejo básico de Ctrl+C (simple y suficiente para el reto) */
    signal(SIGINT, handle_sigint);

    printf("Bienvenido a EAFITos Shell\n");
    printf("Escribe 'ayuda' para ver comandos.\n");

    while (g_running) {
        print_prompt();

        if (fgets(line, sizeof(line), stdin) == NULL) {
            /*
             * Si fue Ctrl+D (EOF), salimos limpio.
             * Si fue interrupción o error de lectura, limpiamos y seguimos.
             */
            if (feof(stdin)) {
                printf("\n");
                break;
            }

            clearerr(stdin);
            continue;
        }

        strip_newline(line);

        if (line[0] == '\0') {
            continue;
        }

        history_add(line);

        int argc = parse_line(line, argv, MAX_TOKENS);
        if (argc == 0) {
            continue;
        }

        const Command *cmd = find_command(argv[0]);
        if (cmd == NULL) {
            print_error("Comando no reconocido. Usa 'ayuda'.");
            continue;
        }

        (void)cmd->handler(argc, argv);
    }

    printf("Saliendo de EAFITos Shell...\n");
}
