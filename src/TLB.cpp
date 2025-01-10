#include <iostream>
#include "TLB.h"

// Constructor de la TLB.
// Inicializa el tamaño máximo permitido, así como los contadores de hits y misses.
TLB::TLB(int size) : size(size), hits(0), misses(0) {}

// Consulta una dirección lógica en la TLB.
// Retorna el puntero al marco correspondiente si está en el cache,
// o nullptr si no se encuentra.
Frame* TLB::consultar(int direccionLogica) {
    std::cout << "TLB: Consultando dirección lógica " << direccionLogica << std::endl;

    // Busca la dirección lógica en el mapa.
    auto it = cache.find(direccionLogica);
    if (it != cache.end()) {
        std::cout << "TLB: HIT para dirección lógica " << direccionLogica << std::endl;
        hits++; // Incrementa el contador de hits.
        return it->second;
    }

    // Si no está en el cache, es un miss.
    std::cout << "TLB: MISS para dirección lógica " << direccionLogica << std::endl;
    misses++; // Incrementa el contador de misses.
    return nullptr;
}

// Actualiza la TLB con una nueva entrada de dirección lógica a marco.
// Si la TLB está llena, aplica la política de reemplazo FIFO.
void TLB::actualizar(int direccionLogica, Frame* frame) {
    std::cout << "TLB: Actualizando entrada para dirección lógica " << direccionLogica << std::endl;

    // Si la dirección ya está en la TLB, no hacer nada.
    if (cache.find(direccionLogica) != cache.end()) {
        return;
    }

    // Si la TLB está llena, eliminar la entrada más antigua según FIFO.
    if (fifoQueue.size() >= static_cast<size_t>(size)) {
        int direccionVieja = fifoQueue.front(); // Obtiene la dirección más antigua.
        fifoQueue.pop_front();                 // Elimina de la cola FIFO.
        cache.erase(direccionVieja);           // Elimina del mapa.
    }

    // Agregar la nueva entrada a la TLB.
    fifoQueue.push_back(direccionLogica);
    cache[direccionLogica] = frame;
}

// Muestra estadísticas de uso de la TLB, incluyendo hits y misses.
void TLB::mostrarEstadisticas() const {
    std::cout << "Estadísticas de la TLB:" << std::endl;
    std::cout << "Hits: " << hits << std::endl;
    std::cout << "Misses: " << misses << std::endl;
}

// Destructor de la TLB.
TLB::~TLB() = default;
