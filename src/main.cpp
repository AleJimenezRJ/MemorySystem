#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

#include "memoriaVirtual.h"
#include "MMU.h"
#include "procesador.h"
#include "codigo.h"
#include "instruccion.h"

#define TOTAL_FRAMES 16
#define DEFAULT_MAX_PROCESSES 4

int main(int argc, char* argv[]) {
    // Validar número de argumentos
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo de instrucciones> [número de procesadores]" << std::endl;
        return EXIT_FAILURE;
    }

    std::string archivoInstrucciones = argv[1];
    int numProcesadores = DEFAULT_MAX_PROCESSES;

    // Verificar si se pasa un argumento para el número de procesadores
    if (argc >= 3) {
        try {
            numProcesadores = std::stoi(argv[2]);
        } catch (std::invalid_argument&) {
            std::cerr << "Error: El número de procesadores debe ser un entero válido." << std::endl;
            return EXIT_FAILURE;
        }

        // Verificar límites del número de procesadores
        if (numProcesadores < 1) {
            std::cerr << "Error: El número de procesadores debe ser al menos 1." << std::endl;
            return EXIT_FAILURE;
        }

        if (numProcesadores > 4) {
            std::cerr << "Error: El número de procesadores no puede exceder 4." << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout << "Iniciando simulación con " << numProcesadores << " procesador(es) y archivo: " << archivoInstrucciones << std::endl;

    // Inicializa la memoria virtual y la MMU
    MemoriaVirtual memoria(TOTAL_FRAMES, "LRU");
    MMU mmu(&memoria);
    Codigo codigo(archivoInstrucciones);

    // Crear procesos simulando procesadores
    std::vector<pid_t> procesos;
    for (int i = 0; i < numProcesadores; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            // Código del hijo: Procesador ejecuta instrucciones
            Procesador procesador(i, &mmu, &codigo);

            while (true) {
                if (!procesador.ejecutarInstruccion()) {
                    break;
                }
            }

            exit(0);
        } else if (pid > 0) {
            procesos.push_back(pid);
        } else {
            std::cerr << "Error creando proceso hijo." << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Esperar a que todos los procesos terminen
    for (pid_t pid : procesos) {
        waitpid(pid, nullptr, 0);
    }

    std::cout << "Simulación completada." << std::endl;

    // memoria.mostrarEstadisticas();

    return 0;
}
