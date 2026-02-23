# DECISIONES DE DISEÑO

## 1. Arquitectura modular (`src/` + `include/`)
Se separó el proyecto en carpetas para implementación (`src`) y cabeceras (`include`) con el fin de mejorar:
- organización
- mantenibilidad
- claridad para pruebas y sustentación

### Beneficios
- Facilita dividir el trabajo entre integrantes
- Hace más sencilla la navegación del código
- Reduce dependencias desordenadas

---

## 2. Shell tipo REPL
La aplicación se implementó con un ciclo **REPL**:
1. mostrar prompt
2. leer entrada
3. parsear
4. ejecutar comando
5. repetir

### Razón
Este modelo cumple de manera directa el objetivo del reto de construir una shell educativa.

---

## 3. Parser simple con `strtok`
Se utilizó `strtok` para separar la línea por espacios.

### Razón
- Es suficiente para el alcance del reto
- Es simple de implementar y explicar
- Reduce complejidad innecesaria

### Limitación
No soporta:
- comillas
- pipes
- redirecciones
- escaping complejo

---

## 4. Tabla de comandos (comando → handler)
Los comandos se gestionan a través de una tabla con información asociada:
- nombre
- función handler
- uso
- descripción

### Razón
- Centraliza la definición de comandos
- Facilita la implementación de `ayuda`
- Hace más limpio el proceso de búsqueda y ejecución

---

## 5. Separación entre comandos básicos y avanzados
Se dividieron en:
- `commands_basic.c`
- `commands_system.c`

### Razón
- Mejor organización lógica
- Facilita la lectura y la sustentación
- Permite asignar trabajo por módulos

---

## 6. Historial básico en memoria
Se implementó un historial simple de comandos recientes con capacidad limitada.

### Razón
- Cumple funcionalidad avanzada útil para la shell
- Mantiene implementación controlada y sencilla
- Evita complejidad de persistencia en archivos

---

## 7. Manejo de errores y robustez de entrada
Se agregaron validaciones para:
- comandos no reconocidos
- argumentos inválidos
- división por cero
- lectura de archivos inexistentes
- fallos de entrada (`fgets == NULL`)
- limpieza de saltos de línea `\n` y `\r\n`

### Razón
Mejora la experiencia de uso y evita comportamientos incorrectos (por ejemplo, bucles de prompt por fallos de lectura).

---

## 8. Manejo básico de `Ctrl+C` (SIGINT)
Se incorporó un manejo simple de `SIGINT` para evitar que la shell se cierre accidentalmente cuando el usuario presiona `Ctrl+C`.

### Razón
Aumenta la robustez y muestra control sobre señales del sistema sin agregar complejidad excesiva.

---

## 9. Uso de `Makefile`
Se definió un `Makefile` con objetivos de:
- compilación
- ejecución
- limpieza
- pruebas
- memcheck

### Razón
- Estandariza la ejecución del proyecto
- Facilita la evaluación por parte del profesor
- Mejora la reproducibilidad

---

## 10. Validación con pruebas y Valgrind
Se incluyó:
- `make test` (smoke test)
- `make memcheck` / ejecución con `valgrind`

### Razón
- Evidencia calidad técnica
- Permite detectar errores de memoria
- Mejora la confiabilidad de la entrega
