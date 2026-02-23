#!/usr/bin/env bash
set -e

echo "[TEST] Ejecutando pruebas básicas..."

OUTPUT=$(./eafitos < tests/test_commands.txt)

echo "$OUTPUT" | grep -q "Comandos disponibles"
echo "$OUTPUT" | grep -q "Comando: usuario"
echo "$OUTPUT" | grep -q "Saliendo de EAFITos Shell"

echo "[OK] Smoke test completado."
