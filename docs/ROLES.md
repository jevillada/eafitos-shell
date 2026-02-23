```md
# ROLES DEL EQUIPO

## Integrantes y responsabilidades

### 1. Juan Esteban Villada Orozco
**Rol principal:** Integración / validación final / soporte de shell  
**Responsabilidades:**
- Configuración de entorno (WSL + Ubuntu + VS Code)
- Integración del proyecto en estructura modular (`src`, `include`, `tests`, `docs`)
- Compilación y validación general (`make`, `make test`, `make memcheck`)
- Correcciones de robustez en lectura de entrada
- Conexión del repositorio local con GitHub y push inicial

---

### 2. [Nombre integrante 2]
**Rol principal:** Comandos básicos  
**Responsabilidades:**
- Implementación y/o soporte de comandos básicos:
  - `listar`
  - `leer`
  - `tiempo`
  - `calc`
- Validaciones de argumentos y mensajes de error
- Ajustes de salidas de usuario para comandos básicos

---

### 3. [Nombre integrante 3]
**Rol principal:** Comandos avanzados / pruebas / documentación de apoyo  
**Responsabilidades:**
- Implementación y/o soporte de comandos avanzados:
  - `historial`
  - `limpiar`
  - `usuario`
  - `directorio`
- Soporte en historial de comandos
- Pruebas básicas (`tests/smoke_test.sh`)
- Apoyo en documentación y revisión final

---

## Forma de trabajo del equipo

- Se trabajó sobre **Linux/WSL (Ubuntu)**.
- Se utilizó **Visual Studio Code** como editor principal.
- Se utilizó **Git/GitHub** para control de versiones.
- El proyecto se validó con:
  - compilación (`make`)
  - pruebas básicas (`make test`)
  - verificación de memoria (`Valgrind`)

---

## Estrategia de integración

1. Definición de estructura modular del proyecto.
2. Implementación separada por módulos (shell, parser, comandos, historial, utilidades).
3. Integración progresiva de comandos.
4. Pruebas de funcionamiento manual y automática.
5. Ajustes de robustez y documentación final.
