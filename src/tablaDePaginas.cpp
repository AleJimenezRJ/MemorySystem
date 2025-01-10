#include "tablaDePaginas.h"
#include <iostream> // Para depuración

// Constructor por defecto.
// Inicializa una tabla de páginas vacía.
TablaDePaginas::TablaDePaginas() : entradas() {}

// Constructor que inicializa la tabla con un número específico de páginas.
// Cada entrada en la tabla se inicializa como inválida.
TablaDePaginas::TablaDePaginas(int numPaginas) {
    for (int i = 0; i < numPaginas; ++i) {
        entradas.push_back(EntradaPagina());
    }
}

// Busca el marco asociado a una página específica.
// Retorna el puntero al marco si la página es válida, de lo contrario retorna nullptr.
Frame* TablaDePaginas::obtenerFrame(int numeroPagina) {
    std::cout << "Tabla de Páginas: Buscando marco para página " << numeroPagina << std::endl;

    // Verifica si el número de página está dentro del rango válido y si la entrada es válida.
    if (numeroPagina >= 0 && numeroPagina < static_cast<int>(entradas.size()) && entradas[numeroPagina].valida) {
        return entradas[numeroPagina].frame;
    }
    return nullptr;
}

// Actualiza la entrada de una página en la tabla con un marco específico.
// También marca la página como válida y actualiza el tiempo de acceso.
void TablaDePaginas::actualizarEntrada(int numeroPagina, Frame* frame) {
    std::cout << "Tabla de Páginas: Actualizando entrada para página " << numeroPagina
              << " con marco " << frame->numeroFrame << std::endl;

    // Verifica si el número de página está dentro del rango válido.
    if (numeroPagina >= 0 && numeroPagina < static_cast<int>(entradas.size())) {
        entradas[numeroPagina].frame = frame;
        entradas[numeroPagina].valida = true;
        entradas[numeroPagina].ultimoAcceso = std::time(nullptr); // Registra el tiempo actual como último acceso.
    }
}

// Actualiza el tiempo de último acceso para una página específica.
// Muestra un mensaje de error si la página no es válida.
void TablaDePaginas::actualizarUltimoAcceso(int numeroPagina) {
    // Verifica si el número de página está dentro del rango válido y si la entrada es válida.
    if (numeroPagina >= 0 && numeroPagina < static_cast<int>(entradas.size()) && entradas[numeroPagina].valida) {
        entradas[numeroPagina].ultimoAcceso = std::time(nullptr); // Registra el tiempo actual.
    } else {
        std::cerr << "Error: Intento de actualizar último acceso en una página inválida." << std::endl;
    }
}
