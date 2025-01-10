#ifndef ENTRADA_PAGINA_H
#define ENTRADA_PAGINA_H

#include <ctime> // Necesario para std::time_t
#include "frame.h"

/**
 * @class EntradaPagina
 * @brief Representa una entrada en la tabla de páginas.
 *
 * Contiene información sobre una página, incluyendo su número, 
 * el marco asociado, si es válida, y la última vez que fue accedida.
 */
class EntradaPagina {
public:
    int numeroPagina; /**< Número de la página representada. */
    Frame* frame;     /**< Puntero al marco de memoria asociado a esta página. */
    bool valida;      /**< Indica si la página está validada en memoria física. */
    std::time_t ultimoAcceso; /**< Marca temporal del último acceso a esta página. */

    /**
     * @brief Constructor por defecto de la clase EntradaPagina.
     *
     * Inicializa los valores de la página, el marco y el estado de validez.
     */
    EntradaPagina();
};

#endif // ENTRADA_PAGINA_H
