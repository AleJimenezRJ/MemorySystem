#ifndef TLB_H
#define TLB_H

#include <deque>
#include <unordered_map>
#include "frame.h"

/**
 * @class TLB
 * @brief Implementa una Translation Lookaside Buffer (TLB) para optimizar las traducciones de direcciones.
 * @note Este componente no está completamente implementado en el programa debido a limitaciones de tiempo 
 * y errores encontrados durante el desarrollo.
 */
class TLB {
private:
    int size;                    ///< Tamaño máximo de la TLB.
    std::deque<int> fifoQueue;   ///< Cola FIFO para manejar reemplazos de entradas en la TLB.
    std::unordered_map<int, Frame*> cache; ///< Mapa para traducciones de dirección lógica a marco.
    int hits;                    ///< Contador de accesos exitosos en la TLB.
    int misses;                  ///< Contador de accesos fallidos en la TLB.

public:
    /**
     * @brief Constructor de la TLB.
     * @param size Tamaño máximo de la TLB.
     */
    TLB(int size);

    /**
     * @brief Consulta una dirección lógica en la TLB.
     * @param direccionLogica Dirección lógica a consultar.
     * @return Un puntero al marco correspondiente si se encuentra en la TLB, o nullptr si no.
     */
    Frame* consultar(int direccionLogica);

    /**
     * @brief Actualiza la TLB con una nueva traducción de dirección lógica a marco.
     * @param direccionLogica Dirección lógica a actualizar.
     * @param frame Puntero al marco asociado a la dirección lógica.
     */
    void actualizar(int direccionLogica, Frame* frame);

    /**
     * @brief Muestra estadísticas de uso de la TLB.
     */
    void mostrarEstadisticas() const;

    /**
     * @brief Destructor de la TLB.
     */
    ~TLB();
};

#endif // TLB_H
