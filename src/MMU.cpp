#include "MMU.h"

// Constructor de la MMU.
// Inicializa la MMU con un puntero al sistema de memoria virtual.
MMU::MMU(MemoriaVirtual* memoriaVirtual) : memoriaVirtual(memoriaVirtual) {}

// Busca el marco asociado a una dirección lógica para un proceso específico.
// Retorna un puntero al marco encontrado, o nullptr si no existe.
Frame* MMU::buscarPagina(int direccionLogica, int proceso) {
    return memoriaVirtual->obtenerFrameDePagina(direccionLogica, proceso);
}

// Traduce una dirección lógica a física para un proceso.
// Protege la operación con un mutex para evitar accesos concurrentes.
int MMU::traducirDireccion(int direccionLogica, int proceso) {
    std::lock_guard<std::mutex> lock(mmuMutex); // Bloquea el acceso concurrente.
    return memoriaVirtual->traducirDireccion(direccionLogica, proceso);
}

// Asigna un marco físico a una dirección lógica para un proceso.
// Usa la función traducirDireccion del sistema de memoria virtual.
int MMU::asignarFrame(int direccionLogica, int proceso) {
    return memoriaVirtual->traducirDireccion(direccionLogica, proceso);
}

// Lee un valor de la memoria virtual a partir de una dirección lógica.
// Protege la operación completa con un mutex.
int MMU::leerMemoria(int direccionLogica, int proceso) {
    std::lock_guard<std::mutex> lock(mmuMutex); // Bloquea la operación completa.
    int direccionFisica = memoriaVirtual->traducirDireccion(direccionLogica, proceso);
    return memoriaVirtual->leerValor(direccionFisica);
}

// Escribe un valor en la memoria virtual en una dirección lógica.
// Traduce la dirección lógica a física y almacena el valor en la memoria física.
void MMU::escribirMemoria(int direccionLogica, int proceso, int valor) {
    std::lock_guard<std::mutex> lock(mmuMutex); // Bloquea la operación completa.
    int direccionFisica = memoriaVirtual->traducirDireccion(direccionLogica, proceso);
    memoriaVirtual->escribirValor(direccionFisica, valor);
}
