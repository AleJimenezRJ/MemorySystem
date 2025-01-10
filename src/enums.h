#ifndef ENUMS_H
#define ENUMS_H

#include <map>
#include <string>

/**
 * @enum Operation
 * @brief Enumera las operaciones soportadas por el sistema.
 * 
 * Este enumerador representa las operaciones disponibles y sus identificadores únicos.
 */
enum Operation {
    NOP,  /**< Operación de no operación (no hace nada). */
    EXIT, /**< Finaliza la ejecución. */
    SET,  /**< Establece un valor en una dirección de memoria. */
    ADD,  /**< Suma dos valores. */
    SUB,  /**< Resta dos valores. */
    JMP,  /**< Salta a una dirección específica. */
    CMP,  /**< Compara dos valores. */
    LOOP  /**< Crea un bucle con una dirección de inicio y fin. */
};

/**
 * @brief Mapa para convertir un valor de Operation a su representación en string.
 * 
 * Este mapa permite obtener una representación textual de una operación.
 */
static std::map<enum Operation, std::string> operationToString = {
    { NOP, "NOP" },
    { EXIT, "EXIT" },
    { SET, "SET" },
    { ADD, "ADD" },
    { SUB, "SUB" },
    { JMP, "JMP" },
    { CMP, "CMP" },
    { LOOP, "LOOP" },
};

/**
 * @brief Mapa para convertir una representación en string a un valor de Operation.
 * 
 * Este mapa permite obtener el valor enumerado correspondiente a una operación a partir de su texto.
 */
static std::map<std::string, enum Operation> stringToOperation = {
    { "NOP", NOP },
    { "EXIT", EXIT },
    { "SET", SET },
    { "ADD", ADD },
    { "SUB", SUB },
    { "JMP", JMP },
    { "CMP", CMP },
    { "LOOP", LOOP },
};

/**
 * @brief Mapa que asocia a cada operación el número esperado de argumentos.
 * 
 * Este mapa especifica cuántos argumentos requiere cada operación para ejecutarse correctamente.
 */
static std::map<enum Operation, int> operationArguments = {
    { NOP, 0 },
    { EXIT, 0 },
    { SET, 2 },
    { ADD, 2 },
    { SUB, 2 },
    { JMP, 1 },
    { CMP, 2 },
    { LOOP, 2 },
};

#endif // ENUMS_H
