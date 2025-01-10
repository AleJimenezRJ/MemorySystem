#ifndef MEMORIA_VIRTUAL_H
#define MEMORIA_VIRTUAL_H

#include <mutex>
#include <unordered_map>
#include <vector>
#include <string>
#include "tablaDePaginas.h"
#include "frame.h"

/**
 * @class MemoriaVirtual
 * @brief Simula un sistema de memoria virtual, administrando tablas de páginas y marcos físicos.
 */
class MemoriaVirtual {
private:
    std::mutex memoriaMutex; /**< Mutex para proteger acceso a memoria física. */
    std::mutex mutexMemoria; /**< Mutex para sincronización general. */
    std::unordered_map<int, TablaDePaginas> tablaPaginas; /**< Tablas de páginas separadas por proceso. */
    std::vector<Frame> framesMemoria; /**< Lista de marcos de memoria física. */
    std::string algoritmoReemplazo; /**< Algoritmo de reemplazo (FIFO o LRU). */
    int hits; /**< Contador de accesos exitosos en la memoria. */
    int misses; /**< Contador de fallos de página. */

    /**
     * @brief Encuentra un marco de memoria libre.
     * @return El índice del marco libre, o -1 si no hay marcos disponibles.
     */
    int obtenerMarcoLibre();

    /**
     * @brief Ejecuta la lógica de reemplazo de páginas según el algoritmo configurado.
     * @param proceso ID del proceso que requiere la página.
     * @param numeroPagina Número de página a reemplazar.
     */
    void reemplazarPagina(int proceso, int numeroPagina);

public:
    /**
     * @brief Constructor de MemoriaVirtual.
     * @param totalFrames Número total de marcos de memoria física.
     * @param algoritmo Algoritmo de reemplazo a usar (FIFO o LRU).
     */
    MemoriaVirtual(int totalFrames, const std::string& algoritmo);

    /**
     * @brief Traduce una dirección lógica a una dirección física.
     * @param direccionLogica Dirección lógica a traducir.
     * @param proceso ID del proceso que realiza la traducción.
     * @return Dirección física correspondiente.
     */
    int traducirDireccion(int direccionLogica, int proceso);

    /**
     * @brief Maneja un fallo de página para un proceso específico.
     * @param proceso ID del proceso afectado.
     * @param numeroPagina Número de página que generó el fallo.
     */
    void manejarFalloPagina(int proceso, int numeroPagina);

    /**
     * @brief Obtiene el marco que corresponde a una dirección lógica.
     * @param direccionLogica Dirección lógica solicitada.
     * @param proceso ID del proceso que accede.
     * @return Puntero al marco asociado, o nullptr si no existe.
     */
    Frame* obtenerFrameDePagina(int direccionLogica, int proceso);

    /**
     * @brief Incrementa el contador de hits.
     */
    void incrementarHit();

    /**
     * @brief Incrementa el contador de misses.
     */
    void incrementarMiss();

    /**
     * @brief Muestra estadísticas de la memoria virtual (hits y misses).
     */
    void mostrarEstadisticas();

    /**
     * @brief Lee un valor desde la memoria física.
     * @param direccionFisica Dirección física a leer.
     * @return Valor almacenado en la dirección física.
     */
    int leerValor(int direccionFisica);

    /**
     * @brief Escribe un valor en la memoria física.
     * @param direccionFisica Dirección física donde escribir.
     * @param valor Valor a escribir.
     */
    void escribirValor(int direccionFisica, int valor);

    /**
     * @brief Valida y cuenta los marcos de memoria libres.
     */
    void validarMarcosLibres() const;
};

#endif // MEMORIA_VIRTUAL_H
