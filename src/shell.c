#include "shell.h"
#include "parser.h"
#include "commands.h"
#include "history.h"
#include "utils.h"

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

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

    /* Manejo básico de Ctrl+C */
    signal(SIGINT, handle_sigint);

    printf("Bienvenido a EAFITos Shell\n");
    printf("Escribe 'ayuda' para ver comandos.\n");

    while (g_running) {
        print_prompt();

        errno = 0;
        if (fgets(line, sizeof(line), stdin) == NULL) {
            /* EOF normal (Ctrl+D o fin de pipe) */
            if (feof(stdin)) {
                printf("\n");
                break;
            }

            /* Error de lectura/interrupción: evitar loop infinito */
            if (ferror(stdin)) {
                clearerr(stdin);

                if (errno == EINTR) {
                    continue;
                }

                print_error("Entrada inválida o interrumpida. Cerrando shell para evitar bucle.");
                break;
            }

            print_error("No se pudo leer la entrada. Cerrando shell.");
            break;
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
