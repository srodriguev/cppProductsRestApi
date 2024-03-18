# Definición de variables
CXX = g++                # Compilador C++
CXXFLAGS = -std=c++11    # Opciones de compilación

# Objetivo predeterminado
all: master

# Reglas de compilación
master: src/main.cpp src/functions.cpp src/unitTest.cpp
    $(CXX) $(CXXFLAGS) -o $@ $^

# Regla para limpiar los archivos generados
clean:
    rm -f master
