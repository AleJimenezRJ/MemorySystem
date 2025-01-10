#ifndef PROCESADOR_H
#define PROCESADOR_H

#include "instruccion.h"
#include "MMU.h"
#include "codigo.h"

/**
 * @class Procesador
 * @brief Representa un procesador que ejecuta instrucciones usando una MMU y un conjunto de instrucciones.
 */
class Procesador {
private:
    int id; /**< Identificador único del procesador. */
    MMU* mmu; /**< Puntero a la unidad de gestión de memoria (MMU). */
    Codigo* codigo; /**< Puntero al conjunto de instrucciones a ejecutar. */
    unsigned int pc = 0; /**< Contador de programa (Program Counter) que indica la instrucción actual. */

public:
    /**
     * @brief Constructor de la clase Procesador.
     * @param id Identificador único del procesador.
     * @param mmu Puntero a la MMU utilizada por el procesador.
     * @param codigo Puntero al conjunto de instrucciones.
     */
    Procesador(int id, MMU* mmu, Codigo* codigo);

    /**
     * @brief Solicita la traducción de una dirección lógica a física a través de la MMU.
     * @param direccionLogica Dirección lógica que será traducida.
     */
    void solicitarDireccion(int direccionLogica);

    /**
     * @brief Ejecuta la instrucción actual indicada por el contador de programa (PC).
     * @return `true` si se debe continuar con la ejecución de instrucciones, `false` si se debe detener.
     */
    bool ejecutarInstruccion();
};

#endif // PROCESADOR_H
