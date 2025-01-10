#ifndef TABLA_DE_PAGINAS_H
#define TABLA_DE_PAGINAS_H

#include <vector>
#include "entradaPagina.h"
#include "frame.h"

/**
 * @class TablaDePaginas
 * @brief Representa la tabla de páginas para gestionar la traducción entre páginas y marcos de memoria.
 */
class TablaDePaginas {
public:
    /**
     * @brief Vector que almacena las entradas de la tabla de páginas.
     */
    std::vector<EntradaPagina> entradas;

    /**
     * @brief Constructor por defecto. Inicializa la tabla de páginas vacía.
     */
    TablaDePaginas();

    /**
     * @brief Constructor que inicializa la tabla con un número específico de páginas.
     * @param numPaginas Número total de páginas que tendrá la tabla.
     */
    TablaDePaginas(int numPaginas);

    /**
     * @brief Obtiene el marco asociado a una página específica.
     * @param numeroPagina Número de la página a buscar.
     * @return Puntero al marco asociado, o `nullptr` si no está asignado o no es válido.
     */
    Frame* obtenerFrame(int numeroPagina);

    /**
     * @brief Actualiza la entrada de una página con un marco específico.
     * @param numeroPagina Número de la página a actualizar.
     * @param frame Puntero al marco que se asignará a la página.
     */
    void actualizarEntrada(int numeroPagina, Frame* frame);

    /**
     * @brief Actualiza el último acceso de una página.
     * @param numeroPagina Número de la página cuyo tiempo de acceso será actualizado.
     */
    void actualizarUltimoAcceso(int numeroPagina);
};

#endif // TABLA_DE_PAGINAS_H
