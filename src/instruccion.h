#ifndef INSTRUCCION_H
#define INSTRUCCION_H

#include <string>
#include <vector>
#include "enums.h"

/**
 * @class Instruccion
 * @brief Representa una instrucción dentro de un programa.
 *
 * Cada instrucción contiene una operación, parámetros asociados y una dirección lógica que la identifica.
 */
class Instruccion {
public:
    enum Operation Operation; /**< Operación que realiza la instrucción. */
    std::vector<int> parametros; /**< Lista de parámetros asociados a la instrucción. */

    /**
     * @brief Constructor por defecto.
     *
     * Crea una instrucción vacía.
     */
    Instruccion();

    /**
     * @brief Constructor con parámetros.
     *
     * Inicializa una instrucción con una operación, parámetros y una dirección lógica.
     *
     * @param operation Operación de la instrucción.
     * @param parametros Lista de parámetros de la instrucción.
     */
    Instruccion(enum Operation operation, std::vector<int> parametros);
};

#endif // INSTRUCCION_H
