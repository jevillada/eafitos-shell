# EAFITos Shell

Proyecto del **Reto 1 - SEHELL** (Sistemas Operativos / XV6) desarrollado en **C**, con arquitectura modular y enfoque educativo.

## Integrantes
- Juan Esteban Villada Orozco
- David Zapata Orozco
- [Nombre integrante 3]


---

## Descripción del proyecto

**EAFITos Shell** es una shell educativa implementada en C que permite ejecutar un conjunto de comandos definidos por el equipo dentro de un entorno interactivo tipo REPL (Read-Eval-Print Loop).

La shell:
- muestra un prompt (`EAFITos>`)
- lee la entrada del usuario
- parsea la línea en tokens
- busca el comando en una tabla de comandos
- ejecuta el handler correspondiente
- mantiene un historial básico de comandos
- maneja errores de entrada y comandos inválidos
- permite cerrar de forma controlada con `salir`

---

## Objetivos cumplidos

- Implementar una shell básica en C.
- Organizar el proyecto de forma modular (`src/`, `include/`, `tests/`, `docs/`).
- Incluir comandos básicos y avanzados.
- Agregar pruebas automáticas básicas.
- Incluir `Makefile` con tareas de compilación y verificación.
- Validar memoria con **Valgrind** (sin fugas y sin errores detectados en la prueba realizada).

---

## Características implementadas

- REPL interactivo (`EAFITos>`)
- Parser simple por espacios (`strtok`)
- Tabla de comandos con:
  - nombre
  - descripción
  - uso
  - handler
- Historial de comandos
- Manejo de errores de comandos y argumentos
- Manejo de `Ctrl+C` (SIGINT) para evitar cierre accidental
- Soporte de limpieza de saltos de línea `\n` y `\r\n` (compatible con pegado desde Windows/WSL)
- Prevención de bucle infinito de prompt en fallos de lectura de entrada
- `make test` (smoke test)
- `make memcheck` (Valgrind)

---

## Estructura del proyecto

```text
eafitos/
├── src/
│   ├── main.c
│   ├── shell.c
│   ├── parser.c
│   ├── commands_basic.c
│   ├── commands_system.c
│   ├── history.c
│   └── utils.c
├── include/
│   ├── shell.h
│   ├── parser.h
│   ├── commands.h
│   ├── history.h
│   └── utils.h
├── tests/
│   ├── smoke_test.sh
│   └── test_commands.txt
├── docs/
│   ├── ROLES.md
│   └── DESIGN_DECISIONS.md
├── CONTRIBUTION.md
├── README.md
├── Makefile
└── .gitignore
