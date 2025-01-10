#include "instruccion.h"

// Constructor por defecto de Instruccion.
// Inicializa una instrucción sin operación, parámetros ni dirección lógica.
Instruccion::Instruccion() {}

// Constructor con parámetros de Instruccion.
// Permite inicializar una instrucción con:
// - Una operación específica.
// - Una lista de parámetros asociados.
// - Una dirección lógica que identifica la instrucción.
Instruccion::Instruccion(enum Operation operation, std::vector<int> parametros)
    : Operation(operation), parametros(parametros) {}
