#!/bin/bash

# Ruta del binario de tu proyecto (ajusta según corresponda)
EXECUTABLE="./build/spydroid"

# Directorio donde se copiarán las bibliotecas
DEST_DIR="./include"

# Crear el directorio si no existe
mkdir -p "$DEST_DIR"

echo "Copiando dependencias para: $EXECUTABLE"

# Usar ldd para listar las dependencias y copiar cada una
ldd "$EXECUTABLE" | grep "=> /" | awk '{print $3}' | while read LIB; do
    if [ -f "$LIB" ]; then
        echo "Copiando: $LIB -> $DEST_DIR"
        cp -v "$LIB" "$DEST_DIR"
    fi
done

# Asegurarse de que también se copian las bibliotecas del cargador dinámico
cp -v /lib64/ld-linux-x86-64.so.2 "$DEST_DIR" 2>/dev/null || true
