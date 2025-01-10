#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "codigo.h"
#include "instruccion.h"

// Constructor de la clase Codigo
// Inicializa la dirección lógica actual en 0x1000 y carga las instrucciones desde el archivo proporcionado.
Codigo::Codigo(const std::string& nombreArchivo)
{
    this->Instrucciones = CargarInstrucciones(nombreArchivo);
}

// Método para cargar instrucciones desde un archivo de texto.
// Lee el archivo línea por línea, procesa cada línea como una instrucción
// y asegura que no haya duplicados basados en la dirección lógica.
std::vector<Instruccion> Codigo::CargarInstrucciones(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo); // Abrir el archivo
    std::string linea;
    std::vector<Instruccion> instrucciones; // Contenedor para almacenar las instrucciones

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de instrucciones " << nombreArchivo << std::endl;
        std::exit(EXIT_FAILURE); // Termina el programa si no se puede abrir el archivo
    }

    // Leer el archivo línea por línea
    while (std::getline(archivo, linea)) {
        if (!linea.empty()) { // Ignorar líneas vacías
            Instruccion instruccion = LeerInstruccion(linea); // Procesar la línea como instrucción
            instrucciones.push_back(instruccion);
        }
    }

    archivo.close(); // Cerrar el archivo después de leer
    return instrucciones; // Devolver el conjunto de instrucciones
}

// Método para leer y procesar una línea de texto como una instrucción.
// Convierte una línea en una instancia de la clase `Instruccion` y valida los parámetros.
Instruccion Codigo::LeerInstruccion(const std::string& linea) {
    std::stringstream ss(linea); // Crear un flujo de entrada desde la línea
    std::string s;
    int expectedArguments = 0; // Número esperado de argumentos para la instrucción
    int readArguments = 0; // Número de argumentos leídos
    Instruccion instruccion;

    // Leer el primer token como la operación
    ss >> s;
    instruccion.Operation = stringToOperation[s]; // Convertir el nombre de la operación en un enum
    expectedArguments = operationArguments[instruccion.Operation]; // Obtener el número esperado de argumentos

    // Leer los parámetros restantes
    while (ss >> s) {
        long n = strtol(s.c_str(), NULL, 0); // Convertir el parámetro en un número
        instruccion.parametros.push_back(n); // Añadir el parámetro a la lista
        readArguments++;
    }

    // Validar que el número de argumentos leídos coincida con lo esperado
    if (readArguments != expectedArguments) {
        std::cerr << "Error: Número de argumentos no coincide en la instrucción: " << linea << ", revise el archivo de prueba cargado." << std::endl;
        std::exit(EXIT_FAILURE); // Terminar si hay un error de formato
    }

    return instruccion; // Devolver la instrucción procesada
}
