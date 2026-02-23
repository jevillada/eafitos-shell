#include "commands.h"
#include "shell.h"

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

static const Command COMMANDS[] = {
    /* Básicos obligatorios */
    {"listar",     cmd_listar,     "listar",                 "Lista archivos del directorio actual", 0},
    {"leer",       cmd_leer,       "leer <archivo>",         "Muestra el contenido de un archivo", 0},
    {"tiempo",     cmd_tiempo,     "tiempo",                 "Muestra fecha y hora actual", 0},
    {"calc",       cmd_calc,       "calc <a> <op> <b>",      "Calculadora simple (+,-,*,/)", 0},
    {"ayuda",      cmd_ayuda,      "ayuda [comando]",        "Muestra ayuda general o por comando", 0},
    {"salir",      cmd_salir,      "salir",                  "Cierra la shell", 0},

    /* Avanzados (para equipo de 3: 4 avanzados) */
    {"historial",  cmd_historial,  "historial",              "Muestra los últimos comandos", 1},
    {"limpiar",    cmd_limpiar,    "limpiar",                "Limpia la pantalla", 1},
    {"usuario",    cmd_usuario,    "usuario",                "Muestra usuario actual", 1},
    {"directorio", cmd_directorio, "directorio",             "Muestra ruta actual", 1}
};

static int parse_double_strict(const char *text, double *out_value) {
    char *endptr = NULL;

    if (text == NULL || out_value == NULL) {
        return 0;
    }

    errno = 0;
    double value = strtod(text, &endptr);

    if (errno != 0) {
        return 0;
    }

    if (endptr == text || *endptr != '\0') {
        return 0;
    }

    *out_value = value;
    return 1;
}

const Command *get_command_table(size_t *count) {
    if (count != NULL) {
        *count = sizeof(COMMANDS) / sizeof(COMMANDS[0]);
    }
    return COMMANDS;
}

const Command *find_command(const char *name) {
    size_t count = 0;
    const Command *table = get_command_table(&count);

    if (name == NULL) return NULL;

    for (size_t i = 0; i < count; i++) {
        if (strcmp(table[i].name, name) == 0) {
            return &table[i];
        }
    }
    return NULL;
}

int cmd_ayuda(int argc, char **argv) {
    size_t count = 0;
    const Command *table = get_command_table(&count);

    if (argc == 1) {
        printf("Comandos disponibles:\n");
        for (size_t i = 0; i < count; i++) {
            printf(" - %-10s | %s\n", table[i].name, table[i].description);
        }
        printf("\nUsa 'ayuda <comando>' para ver el uso.\n");
        return 0;
    }

    if (argc == 2) {
        const Command *cmd = find_command(argv[1]);
        if (cmd == NULL) {
            printf("No existe ayuda para el comando '%s'.\n", argv[1]);
            return 1;
        }

        printf("Comando: %s\n", cmd->name);
        printf("Uso: %s\n", cmd->usage);
        printf("Descripción: %s\n", cmd->description);
        printf("Tipo: %s\n", cmd->is_advanced ? "Avanzado" : "Básico");
        return 0;
    }

    printf("Uso: ayuda [comando]\n");
    return 1;
}

int cmd_salir(int argc, char **argv) {
    (void)argc;
    (void)argv;
    shell_request_exit();
    return 0;
}

int cmd_listar(int argc, char **argv) {
    (void)argv;

    if (argc != 1) {
        printf("Uso: listar\n");
        return 1;
    }

    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}

int cmd_leer(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: leer <archivo>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        fputs(buffer, stdout);
    }

    if (ferror(fp)) {
        perror("fgets");
        fclose(fp);
        return 1;
    }

    fclose(fp);
    return 0;
}

int cmd_tiempo(int argc, char **argv) {
    (void)argv;

    if (argc != 1) {
        printf("Uso: tiempo\n");
        return 1;
    }

    time_t now = time(NULL);
    if (now == (time_t)-1) {
        perror("time");
        return 1;
    }

    struct tm *local = localtime(&now);
    if (local == NULL) {
        perror("localtime");
        return 1;
    }

    char output[64];
    if (strftime(output, sizeof(output), "%Y-%m-%d %H:%M:%S", local) == 0) {
        printf("No se pudo formatear la fecha/hora.\n");
        return 1;
    }

    printf("%s\n", output);
    return 0;
}

int cmd_calc(int argc, char **argv) {
    if (argc != 4) {
        printf("Uso: calc <a> <op> <b>\n");
        printf("Ejemplo: calc 10 + 5\n");
        return 1;
    }

    double a = 0.0;
    double b = 0.0;

    if (!parse_double_strict(argv[1], &a)) {
        printf("Error: primer operando inválido ('%s').\n", argv[1]);
        return 1;
    }

    if (!parse_double_strict(argv[3], &b)) {
        printf("Error: segundo operando inválido ('%s').\n", argv[3]);
        return 1;
    }

    if (strlen(argv[2]) != 1) {
        printf("Error: operador inválido. Usa uno de: + - * /\n");
        return 1;
    }

    char op = argv[2][0];
    double result = 0.0;

    switch (op) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            if (b == 0.0) {
                printf("Error: división por cero.\n");
                return 1;
            }
            result = a / b;
            break;
        default:
            printf("Error: operador inválido. Usa uno de: + - * /\n");
            return 1;
    }

    printf("%g %c %g = %g\n", a, op, b, result);
    return 0;
}
