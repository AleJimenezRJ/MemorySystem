#ifndef CODIGO_H
#define CODIGO_H

#include <vector>
#include "instruccion.h"

/**
 * @class Codigo
 * @brief Representa el conjunto de instrucciones cargadas desde un archivo.
 *
 * La clase se encarga de cargar instrucciones desde un archivo y almacenarlas
 * en una lista. También mantiene un registro de la dirección actual del conjunto
 * de instrucciones.
 */
class Codigo {
public:
    /**
     * @brief Contiene el conjunto de instrucciones cargadas.
     */
    std::vector<Instruccion> Instrucciones;

    /**
     * @brief Constructor que inicializa el código cargando instrucciones desde un archivo.
     * @param archivoInstrucciones Ruta al archivo que contiene las instrucciones.
     */
    Codigo(const std::string& archivoInstrucciones);

private:
    /**
     * @brief Carga las instrucciones desde un archivo de texto.
     *
     * Este método se encarga de leer un archivo línea por línea, interpretar cada línea
     * como una instrucción y almacenarla en un vector.
     *
     * @param archivoInstrucciones Ruta al archivo de texto con las instrucciones.
     * @return Un vector de instrucciones cargadas desde el archivo.
     */
    std::vector<Instruccion> CargarInstrucciones(const std::string& archivoInstrucciones);

    /**
     * @brief Lee una línea y la interpreta como una instrucción.
     *
     * Convierte una línea de texto en una instancia de la clase `Instruccion`,
     * extrayendo la operación y los argumentos.
     *
     * @param linea Una línea de texto que representa una instrucción.
     * @return Una instancia de la clase `Instruccion` correspondiente a la línea dada.
     */
    Instruccion LeerInstruccion(const std::string& linea);
};

#endif // CODIGO_H
