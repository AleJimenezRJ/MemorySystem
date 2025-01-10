#include <climits>
#include <iostream>
#include <map>
#include <mutex>
#include "memoriaVirtual.h"

std::map<int, int> memoriaFisica; // Simula la memoria física

// Constructor de MemoriaVirtual.
// Inicializa los marcos de memoria física y las tablas de páginas para cada proceso.
MemoriaVirtual::MemoriaVirtual(int totalFrames, const std::string& algoritmo)
    : algoritmoReemplazo(algoritmo), hits(0), misses(0) {
    for (int i = 0; i < totalFrames; ++i) {
        framesMemoria.emplace_back(i);
    }

    // Crear tablas de páginas independientes por proceso
    for (int procesoId = 0; procesoId < 4; ++procesoId) {
        tablaPaginas.emplace(procesoId, TablaDePaginas(1024)); // Ejemplo: 1024 páginas por proceso
    }
}

// Encuentra un marco libre en la memoria física.
// Retorna el índice del marco, o -1 si no hay marcos disponibles.
int MemoriaVirtual::obtenerMarcoLibre() {
    for (auto& frame : framesMemoria) {
        if (frame.disponible) {
            frame.asignarPagina(); // Marca el marco como ocupado inmediatamente
            return frame.numeroFrame;
        }
    }
    return -1; // No hay marcos libres
}

void MemoriaVirtual::incrementarHit() {
    hits++;
}

void MemoriaVirtual::incrementarMiss() {
    misses++;
}

// void MemoriaVirtual::mostrarEstadisticas() const {
//     std::cout << "Estadísticas de la memoria virtual:" << std::endl;
//     std::cout << "Hits: " << hits << std::endl;
//     std::cout << "Misses: " << misses << std::endl;
// }

// Obtiene el marco correspondiente a una dirección lógica para un proceso específico.
Frame* MemoriaVirtual::obtenerFrameDePagina(int direccionLogica, int proceso) {
    if (tablaPaginas.find(proceso) == tablaPaginas.end()) {
        std::cerr << "[ERROR] Proceso " << proceso << " no tiene tabla de páginas asignada." << std::endl;
        return nullptr;
    }

    int numeroPagina = direccionLogica / 4096; // Tamaño de página = 4 KB
    TablaDePaginas& tabla = tablaPaginas[proceso];
    Frame* frame = tabla.obtenerFrame(numeroPagina);
    if (frame) {
        tabla.actualizarUltimoAcceso(numeroPagina); // Actualiza el acceso
    }
    return frame;
}
// Maneja un fallo de página asignando un nuevo marco o reemplazando una página existente.
void MemoriaVirtual::manejarFalloPagina(int proceso, int numeroPagina) {
    std::unique_lock<std::mutex> lock(mutexMemoria);
    if (tablaPaginas.find(proceso) == tablaPaginas.end()) {
        std::cerr << "[ERROR] Proceso " << proceso << " no tiene tabla de páginas asignada." << std::endl;
        return;
    }

    int marcoLibre = obtenerMarcoLibre();
    if (marcoLibre == -1) {
        reemplazarPagina(proceso, numeroPagina);
    } else {
        framesMemoria[marcoLibre].asignarPagina();
        tablaPaginas[proceso].actualizarEntrada(numeroPagina, &framesMemoria[marcoLibre]);
    }
    incrementarMiss();
}

// Reemplazar la página usando LRU
void MemoriaVirtual::reemplazarPagina(int proceso, int numeroPagina) {
    validarMarcosLibres(); // Validar antes de reemplazar una página
    if (tablaPaginas.find(proceso) == tablaPaginas.end()) {
        std::cerr << "[ERROR] Proceso " << proceso << " no tiene tabla de páginas asignada." << std::endl;
        return;
    }

    if (algoritmoReemplazo == "LRU") { // Reemplazo por LRU
        int paginaLRU = -1;
        int tiempoMinimo = INT_MAX;
        for (auto& entrada : tablaPaginas[proceso].entradas) {
            if (entrada.valida && entrada.ultimoAcceso < tiempoMinimo) {
                tiempoMinimo = entrada.ultimoAcceso;
                paginaLRU = entrada.numeroPagina;
            }
        }

        if (paginaLRU != -1) {
            std::cout << "Usando LRU para página menos recientemente usada: " << paginaLRU << std::endl;
            tablaPaginas[proceso].entradas[paginaLRU].valida = false;
            tablaPaginas[proceso].entradas[numeroPagina].frame = tablaPaginas[proceso].entradas[paginaLRU].frame;
            tablaPaginas[proceso].entradas[numeroPagina].valida = true;
        }
    } // else { // Reemplazo por FIFO
    //     static int indiceFIFO = 0;
    //     for (auto& entrada : tablaPaginas[proceso].entradas) {
    //         if (entrada.valida) {
    //             entrada.valida = false;
    //             tablaPaginas[proceso].entradas[numeroPagina].frame = entrada.frame;
    //             tablaPaginas[proceso].entradas[numeroPagina].valida = true;
    //             break;
    //         }
    //     }
    //     indiceFIFO = (indiceFIFO + 1) % tablaPaginas[proceso].entradas.size();
    // }
    validarMarcosLibres(); // Validar después de reemplazar una página
}

// Traduce una dirección lógica a física, manejando fallos de página si es necesario.
int MemoriaVirtual::traducirDireccion(int direccionLogica, int proceso) {
    if (tablaPaginas.find(proceso) == tablaPaginas.end()) {
        std::cerr << "[ERROR] Proceso " << proceso << " no tiene tabla de páginas asignada." << std::endl;
        return -1;
    }

    int numeroPagina = direccionLogica / 4096;
    Frame* frame = tablaPaginas[proceso].obtenerFrame(numeroPagina);
    if (!frame) {
        manejarFalloPagina(proceso, numeroPagina);
        frame = tablaPaginas[proceso].obtenerFrame(numeroPagina);
        if (!frame) {
            std::cerr << "[CRITICAL ERROR] No se pudo asignar un marco para la página " << numeroPagina << std::endl;
            std::exit(EXIT_FAILURE);
        }
    } else {
        incrementarHit();
        tablaPaginas[proceso].actualizarUltimoAcceso(numeroPagina);
    }

    return frame->numeroFrame * 4096 + (direccionLogica % 4096);
}
// Leer valor de la memoria física
int MemoriaVirtual::leerValor(int direccionFisica) {
    std::lock_guard<std::mutex> lock(mutexMemoria);
    if (memoriaFisica.find(direccionFisica) != memoriaFisica.end()) {
        return memoriaFisica[direccionFisica];
    } else {
        std::cerr << "[ERROR] Dirección física " << direccionFisica << " no contiene datos válidos." << std::endl;
        return 0;
    }
}
// Escribir valor de la memoria física
void MemoriaVirtual::escribirValor(int direccionFisica, int valor) {
    std::lock_guard<std::mutex> lock(mutexMemoria);
    memoriaFisica[direccionFisica] = valor;
    // std::cout << "[DEBUG] Valor " << valor << " escrito en la dirección física " << direccionFisica << std::endl;
}
// Validar la cantidad de marcos libres con propósitos de debuggear
void MemoriaVirtual::validarMarcosLibres() const {
    int marcosLibres = 0;
    for (const auto& frame : framesMemoria) {
        if (frame.disponible) {
            marcosLibres++;
        }
    }
    std::cout << "Marcos libres: " << marcosLibres << "/" << framesMemoria.size() << std::endl;
}
