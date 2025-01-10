#ifndef FRAME_H
#define FRAME_H

/**
 * @class Frame
 * @brief Representa un marco de memoria física en el sistema.
 * 
 * Un marco es una unidad de memoria física asignada a una página lógica.
 */
class Frame {
public:
    int numeroFrame;   /**< Número identificador del marco en memoria física. */
    bool disponible;   /**< Indica si el marco está disponible para ser asignado. */
    bool bitmap;       /**< Indica si el marco está actualmente ocupado (true) o libre (false). */

    /**
     * @brief Constructor de la clase Frame.
     * 
     * Inicializa un marco con su número identificador y su estado de disponibilidad.
     * 
     * @param numeroFrame Número del marco en memoria física.
     * @param disponible (Opcional) Estado inicial del marco, true si está libre, false si está ocupado. Por defecto, true.
     */
    Frame(int numeroFrame, bool disponible = true);

    /**
     * @brief Marca el marco como ocupado.
     * 
     * Cambia el estado del marco a no disponible y actualiza el bitmap para reflejar que está ocupado.
     */
    void asignarPagina();
};

#endif // FRAME_H
