#ifndef COMMANDS_H
#define COMMANDS_H

#include <stddef.h>

typedef int (*command_handler_t)(int argc, char **argv);

typedef struct {
    const char *name;
    command_handler_t handler;
    const char *usage;
    const char *description;
    int is_advanced; /* 0 = básico, 1 = avanzado */
} Command;

const Command *get_command_table(size_t *count);
const Command *find_command(const char *name);

/* Comandos básicos */
int cmd_listar(int argc, char **argv);
int cmd_leer(int argc, char **argv);
int cmd_tiempo(int argc, char **argv);
int cmd_calc(int argc, char **argv);
int cmd_ayuda(int argc, char **argv);
int cmd_salir(int argc, char **argv);

/* Comandos avanzados */
int cmd_historial(int argc, char **argv);
int cmd_limpiar(int argc, char **argv);
int cmd_usuario(int argc, char **argv);
int cmd_directorio(int argc, char **argv);

#endif
