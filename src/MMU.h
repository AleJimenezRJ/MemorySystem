#ifndef MMU_H
#define MMU_H

#include <mutex>
#include "memoriaVirtual.h"

/**
 * @class MMU
 * @brief Unidad de gestión de memoria (MMU) encargada de traducir direcciones lógicas a físicas
 * y coordinar operaciones de lectura/escritura en la memoria virtual.
 */
class MMU {
private:
    std::mutex mmuMutex; /**< Mutex para proteger acceso concurrente a las operaciones de la MMU. */
    MemoriaVirtual* memoriaVirtual; /**< Puntero al sistema de memoria virtual. */

public:
    /**
     * @brief Constructor de la MMU.
     * @param memoriaVirtual Puntero al sistema de memoria virtual asociado.
     */
    MMU(MemoriaVirtual* memoriaVirtual);

    /**
     * @brief Traduce una dirección lógica a una dirección física.
     * @param direccionLogica Dirección lógica a traducir.
     * @param proceso ID del proceso que solicita la traducción.
     * @return Dirección física correspondiente.
     */
    int traducirDireccion(int direccionLogica, int proceso);

    /**
     * @brief Busca la página asociada a una dirección lógica.
     * @param direccionLogica Dirección lógica de la página.
     * @param proceso ID del proceso que realiza la búsqueda.
     * @return Puntero al marco de la página, o nullptr si no se encuentra.
     */
    Frame* buscarPagina(int direccionLogica, int proceso);

    /**
     * @brief Asigna un marco a una dirección lógica.
     * @param direccionLogica Dirección lógica a asignar.
     * @param proceso ID del proceso que realiza la asignación.
     * @return Dirección física del marco asignado.
     */
    int asignarFrame(int direccionLogica, int proceso);

    /**
     * @brief Lee un valor de la memoria virtual desde una dirección lógica.
     * @param direccionLogica Dirección lógica a leer.
     * @param proceso ID del proceso que realiza la lectura.
     * @return Valor almacenado en la dirección lógica.
     */
    int leerMemoria(int direccionLogica, int proceso);

    /**
     * @brief Escribe un valor en la memoria virtual en una dirección lógica.
     * @param direccionLogica Dirección lógica donde escribir.
     * @param proceso ID del proceso que realiza la escritura.
     * @param valor Valor a escribir.
     */
    void escribirMemoria(int direccionLogica, int proceso, int valor);
};

#endif // MMU_H
