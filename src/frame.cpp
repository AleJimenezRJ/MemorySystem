#include "frame.h"

// Constructor de Frame.
// Inicializa un marco con un número de marco único y su estado inicial de disponibilidad.
// El bitmap se establece en false para indicar que el marco no está ocupado inicialmente.
Frame::Frame(int numeroFrame, bool disponible) 
    : numeroFrame(numeroFrame), disponible(disponible), bitmap(false) {}

// Método para asignar una página al marco.
// Cambia el estado del marco a ocupado (disponible = false) y actualiza el bitmap a true 
// para indicar que el marco ahora contiene una página activa.
void Frame::asignarPagina() {
    disponible = false;  // El marco ya no está disponible para otras páginas.
    bitmap = true;       // Indica que el marco está asignado.
}
