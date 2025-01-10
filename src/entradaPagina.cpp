#include "entradaPagina.h"
#include <ctime>

// Constructor por defecto de la clase EntradaPagina.
// Inicializa los miembros de la clase con valores predeterminados:
// - `numeroPagina` se inicializa como -1 para indicar que no está asignada.
// - `frame` se inicializa como nullptr, indicando que no hay un marco asignado.
// - `valida` se inicializa como false, indicando que la página no está validada.
// - `ultimoAcceso` se inicializa con el tiempo actual.
EntradaPagina::EntradaPagina() 
    : numeroPagina(-1),       // Página no asignada por defecto.
      frame(nullptr),         // Sin marco asociado.
      valida(false),          // Página no válida inicialmente.
      ultimoAcceso(std::time(nullptr)) // Último acceso en el momento de creación.
{}
