#include <iostream>
#include <algorithm>
#include "procesador.h"

// Constructor del procesador.
// Inicializa el procesador con un ID, una MMU y un conjunto de instrucciones.
Procesador::Procesador(int id, MMU* mmu, Codigo* codigo) : id(id), mmu(mmu), codigo(codigo) {}

// Solicita la traducción de una dirección lógica a física utilizando la MMU.
// Muestra en consola la traducción realizada.
void Procesador::solicitarDireccion(int direccionLogica) {
    int direccionFisica = mmu->asignarFrame(direccionLogica, id);
    std::cout << "Procesador " << id << ": Dirección lógica " << direccionLogica
              << " traducida a dirección física " << direccionFisica << std::endl;
}

// Ejecuta la instrucción actual apuntada por el contador de programa (PC).
// Maneja diferentes tipos de instrucciones y realiza operaciones en la memoria virtual a través de la MMU.
bool Procesador::ejecutarInstruccion() {
    // Verifica si el contador de programa está dentro del rango de instrucciones.
    if (pc >= codigo->Instrucciones.size()) {
        std::cerr << "Error: PC fuera de rango, valor actual: " << pc << std::endl;
        return false;
    }

    // Indica si se debe continuar ejecutando instrucciones.
    bool executeNext = true;
    // Indica si el contador de programa debe incrementarse.
    bool incrementPC = true;

    std::cout << "Ejecutando instrucción " << pc << std::endl;

    // Obtiene la instrucción actual.
    Instruccion instruccion = codigo->Instrucciones[pc];

    // Maneja cada operación según su tipo.
    switch (instruccion.Operation) {
        case Operation::NOP: // Instrucción NOP no realiza ninguna operación.
            std::cout << "Procesador " << id << ": Ejecutando NOP" << std::endl;
            break;

        case Operation::EXIT: // Instrucción EXIT termina la ejecución.
            executeNext = false;
            incrementPC = false;
            std::cout << "Procesador " << id << ": Ejecutando EXIT" << std::endl;
            break;

        case Operation::SET: { // Instrucción SET asigna un valor a una dirección lógica.
            int direccion = instruccion.parametros[0];
            int valor = instruccion.parametros[1];
            mmu->escribirMemoria(direccion, id, valor);
            std::cout << "Procesador " << id << ": SET dirección lógica " << direccion
                      << " valor " << valor << std::endl;
            break;
        }

        case Operation::ADD: { // Instrucción ADD suma los valores de dos direcciones lógicas.
            int direccion1 = instruccion.parametros[0];
            int direccion2 = instruccion.parametros[1];
            int valor1 = mmu->leerMemoria(direccion1, id);
            int valor2 = mmu->leerMemoria(direccion2, id);
            int resultado = valor1 + valor2;
            mmu->escribirMemoria(direccion1, id, resultado);
            std::cout << "Procesador " << id << ": ADD resultado " << resultado
                      << " almacenado en " << direccion1 << std::endl;
            break;
        }

        case Operation::SUB: { // Instrucción SUB resta los valores de dos direcciones lógicas.
            int direccion1 = instruccion.parametros[0];
            int direccion2 = instruccion.parametros[1];
            int valor1 = mmu->leerMemoria(direccion1, id);
            int valor2 = mmu->leerMemoria(direccion2, id);
            int resultado = valor1 - valor2;
            mmu->escribirMemoria(direccion1, id, resultado);
            std::cout << "Procesador " << id << ": SUB resultado " << resultado
                      << " almacenado en " << direccion1 << std::endl;
            break;
        }

        case Operation::JMP: { // Instrucción JMP salta a una dirección lógica específica.
            int direccion = instruccion.parametros[0];
            int valor = mmu->leerMemoria(direccion, id);

            pc = valor;
            incrementPC = false;
            std::cout << "Procesador " << id << ": Saltando a PC " << valor << std::endl;
            break;
        }

        case Operation::CMP: { // Instrucción CMP compara los valores de dos direcciones lógicas.
            int direccion1 = instruccion.parametros[0];
            int direccion2 = instruccion.parametros[1];
            int valor1 = mmu->leerMemoria(direccion1, id);
            int valor2 = mmu->leerMemoria(direccion2, id);
            std::cout << "Procesador " << id << ": dirección lógica " << direccion1 << "(" << valor1 << ") "
                      << (valor1 == valor2 ? " == " : " != ") << " dirección lógica " << direccion2 << "(" << valor2 << ")" << std::endl;
            break;
        }

        case Operation::LOOP: { // Instrucción LOOP decrementa un contador y salta si es mayor a cero.
            int direccionContador = instruccion.parametros[0];
            int direccionJMP = instruccion.parametros[1];
            int valorContador = mmu->leerMemoria(direccionContador, id);
            int valorDireccion = mmu->leerMemoria(direccionJMP, id);
            if (valorContador > 0) {
                pc = valorDireccion;
                incrementPC = false;
                std::cout << "Procesador " << id << ": LOOP Saltando a PC " << pc << std::endl;
            }
            valorContador--;
            mmu->escribirMemoria(direccionContador, id, valorContador);
            break;
        }

        default: // Operación no reconocida.
            break;
    }

    // Incrementa el contador de programa si no se realizó un salto.
    if (incrementPC) {
        pc++;
    }

    return executeNext;
}
