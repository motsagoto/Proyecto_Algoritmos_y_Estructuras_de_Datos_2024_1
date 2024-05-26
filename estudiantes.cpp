#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <numeric> 
#include <cstdlib>
#include <ctime> 

class Estudiante {
public:
    std::string nombre;
    std::string apellido;
    std::vector<int> notas;

    std::string nombreCompleto() const {
        return nombre + " " + apellido;
    }

    void agregarNota(int nota) {
        notas.push_back(nota);
    }

    void cambiarNota(int indice, int nuevaNota) {
        if (indice >= 0 && indice < notas.size()) {
            notas[indice] = nuevaNota;
        }
    }

    void eliminarNota(int indice) {
        if (indice >= 0 && indice < notas.size()) {
            notas.erase(notas.begin() + indice);
        }
    }

    void mostrarCalificaciones() const {
        std::cout << "Calificaciones de " << nombreCompleto() << ":\n";
        for (size_t i = 0; i < notas.size(); ++i) {
            std::cout << i + 1 << ". " << notas[i] << std::endl;
        }
    }

    float calcularPromedio() const {
        if (notas.empty()) {
            return 0.0;
        }
        int suma = std::accumulate(notas.begin(), notas.end(), 0);
        return static_cast<float>(suma) / notas.size();
    }

    void cambiarNombre(const std::string& nuevoNombre) {
        nombre = nuevoNombre;
    }

    void cambiarApellido(const std::string& nuevoApellido) {
        apellido = nuevoApellido;
    }
};

int obtenerEntradaNumerica() {
    int valor;
    while (!(std::cin >> valor)) {
        std::cout << "Entrada inválida. Por favor, ingrese un número: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

std::string obtenerEntradaTexto() {
    std::string texto;
    std::getline(std::cin, texto);
    return texto;
}

bool deseaReintentar() {
    char opcion;
    std::cout << "¿Desea reintentar? (s/n): ";
    std::cin >> opcion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return (opcion == 's' || opcion == 'S');
}

void importarDesdeCSV(std::vector<Estudiante>& estudiantes, const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo. Asegúrese de que el nombre del archivo incluya la extensión '.csv'." << std::endl;
        return;
    }
    estudiantes.clear();
    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        Estudiante estudiante;
        std::getline(ss, estudiante.nombre, ',');
        std::getline(ss, estudiante.apellido, ',');
        std::string notaStr;
        while (std::getline(ss, notaStr, ',')) {
            estudiante.notas.push_back(std::stoi(notaStr));
        }
        estudiantes.push_back(estudiante);
    }
    archivo.close();
    std::cout << "Datos importados correctamente." << std::endl;
}

void exportarACSV(const std::vector<Estudiante>& estudiantes, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo para escribir. Asegúrese de que el nombre del archivo incluya la extensión '.csv'." << std::endl;
        return;
    }
    for (const auto& estudiante : estudiantes) {
        archivo << estudiante.nombre << "," << estudiante.apellido;
        for (const auto& nota : estudiante.notas) {
            archivo << "," << nota;
        }
        archivo << "\n";
    }
    archivo.close();
    std::cout << "Datos exportados correctamente." << std::endl;
}

// Función de intercambio
void swap(Estudiante& a, Estudiante& b) {
    Estudiante temp = a;
    a = b;
    b = temp;
}

// Partición para Quicksort
int partition(std::vector<Estudiante>& arr, int low, int high) {
    float pivot = arr[high].calcularPromedio();
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j].calcularPromedio() > pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Implementación de Quicksort
void quicksort(std::vector<Estudiante>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Implementación de Insertion Sort
void insertsort(std::vector<Estudiante>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        Estudiante key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].calcularPromedio() < key.calcularPromedio()) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void mostrarEstudiantesOrdenadosPorPromedio(const std::vector<Estudiante>& estudiantes) {
    std::vector<Estudiante> estudiantesOrdenados = estudiantes;

    // Usar aleatoriamente quicksort o insertsort para ordenar los estudiantes por promedio
    std::srand(std::time(nullptr)); // Inicializar la semilla para generar números aleatorios
    if (std::rand() % 2 == 0) {
        quicksort(estudiantesOrdenados, 0, estudiantesOrdenados.size() - 1);
        std::cout << "\nEstudiantes ordenados por promedio usando quicksort:\n";
    } else {
        insertsort(estudiantesOrdenados);
        std::cout << "\nEstudiantes ordenados por promedio usando insertsort:\n";
    }

    for (const auto& estudiante : estudiantesOrdenados) {
        std::cout << estudiante.nombreCompleto() << " - Promedio: " << estudiante.calcularPromedio() << std::endl;
    }
}

bool deseaExportarAntesDeSalir() {
    char opcion;
    std::cout << "¿Desea exportar los datos antes de salir? (s/n): ";
    std::cin >> opcion;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return (opcion == 's' || opcion == 'S');
}

int main() {
    std::vector<Estudiante> estudiantes;
    bool salir = false;

    std::cout << "Bienvenido al sistema de gestión de estudiantes.\n";
    std::cout << "Este programa permite gestionar estudiantes y sus notas. Puede agregar, modificar y eliminar estudiantes, asignar y cambiar notas, y exportar/importar datos en formato CSV.\n";

    do {
        std::cout << "\nMenú:\n";
        std::cout << "1. Agregar estudiante\n";
        std::cout << "2. Asignar nota parcial\n";
        std::cout << "3. Cambiar nota de estudiante\n";
        std::cout << "4. Eliminar nota de estudiante\n";
        std::cout << "5. Mostrar calificaciones de un estudiante\n";
        std::cout << "6. Cambiar nombre/apellido de un estudiante\n";
        std::cout << "7. Eliminar estudiante\n";
        std::cout << "8. Mostrar lista de estudiantes ordenados por promedio\n";
        std::cout << "9. Importar datos desde un archivo CSV\n";
        std::cout << "10. Exportar datos a un archivo CSV\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opción: ";
        int opcion = obtenerEntradaNumerica();

        switch (opcion) {
            case 1: {
                std::string nombre, apellido;
                std::cout << "\nIngrese el nombre del estudiante: ";
                nombre = obtenerEntradaTexto();
                std::cout << "Ingrese el apellido del estudiante: ";
                apellido = obtenerEntradaTexto();
                estudiantes.push_back({ nombre, apellido, {} });
                std::cout << "Estudiante agregado correctamente." << std::endl;
                break;
            }
            case 2: {
                bool reintentar;
                do {
                    reintentar = false;
                    if (estudiantes.empty()) {
                        std::cout << "No hay estudiantes registrados." << std::endl;
                        break;
                    }

                    std::cout << "\nSeleccione el estudiante por número:\n";
                    for (size_t i = 0; i < estudiantes.size(); ++i) {
                        std::cout << i + 1 << ". " << estudiantes[i].nombreCompleto() << std::endl;
                    }
                    int seleccion = obtenerEntradaNumerica() - 1;

                    if (seleccion >= 0 && seleccion < estudiantes.size()) {
                        std::cout << "Ingrese la nota a asignar (0-100): ";
                        int nota = obtenerEntradaNumerica();
                        if (nota >= 0 && nota <= 100) {
                            estudiantes[seleccion].agregarNota(nota);
                            std::cout << "Nota agregada correctamente." << std::endl;
                        } else {
                            std::cout << "Nota fuera de rango. Debe ser entre 0 y 100." << std::endl;
                            reintentar = deseaReintentar();
                        }
                    } else {
                        std::cout << "Selección inválida." << std::endl;
                        reintentar = deseaReintentar();
                    }
                } while (reintentar);
                break;
            }
            case 3: {
                bool reintentar;
                do {
                    reintentar = false;
                    if (estudiantes.empty()) {
                        std::cout << "No hay estudiantes registrados." << std::endl;
                        break;
                    }

                    std::cout << "\nSeleccione el estudiante por número:\n";
                    for (size_t i = 0; i < estudiantes.size(); ++i) {
                        std::cout << i + 1 << ". " << estudiantes[i].nombreCompleto() << std::endl;
                    }
                    int seleccion = obtenerEntradaNumerica() - 1;

                    if (seleccion >= 0 && seleccion < estudiantes.size()) {
                        std::cout << "Seleccione la nota que desea cambiar:\n";
                        estudiantes[seleccion].mostrarCalificaciones();
                        int indiceNota = obtenerEntradaNumerica() - 1;

                        if (indiceNota >= 0 && indiceNota < estudiantes[seleccion].notas.size()) {
                            std::cout << "Ingrese la nueva nota (0-100): ";
                            int nuevaNota = obtenerEntradaNumerica();
                            if (nuevaNota >= 0 && nuevaNota <= 100) {
                                estudiantes[seleccion].cambiarNota(indiceNota, nuevaNota);
                                std::cout << "Nota cambiada correctamente." << std::endl;
                            } else {
                                std::cout << "Nota fuera de rango. Debe ser entre 0 y 100." << std::endl;
                                reintentar = deseaReintentar();
                            }
                        } else {
                            std::cout << "Selección de nota inválida." << std::endl;
                            reintentar = deseaReintentar();
                        }
                    } else {
                        std::cout << "Selección inválida." << std::endl;
                        reintentar = deseaReintentar();
                    }
                } while (reintentar);
                break;
            }
            case 4: {
                bool reintentar;
                do {
                    reintentar = false;
                    if (estudiantes.empty()) {
                        std::cout << "No hay estudiantes registrados." << std::endl;
                        break;
                    }

                    std::cout << "\nSeleccione el estudiante por número:\n";
                    for (size_t i = 0; i < estudiantes.size(); ++i) {
                        std::cout << i + 1 << ". " << estudiantes[i].nombreCompleto() << std::endl;
                    }
                    int seleccion = obtenerEntradaNumerica() - 1;

                    if (seleccion >= 0 && seleccion < estudiantes.size()) {
                        std::cout << "Seleccione la nota que desea eliminar:\n";
                        estudiantes[seleccion].mostrarCalificaciones();
                        int indiceNota = obtenerEntradaNumerica() - 1;

                        if (indiceNota >= 0 && indiceNota < estudiantes[seleccion].notas.size()) {
                            estudiantes[seleccion].eliminarNota(indiceNota);
                            std::cout << "Nota eliminada correctamente." << std::endl;
                        } else {
                            std::cout << "Selección de nota inválida." << std::endl;
                            reintentar = deseaReintentar();
                        }
                    } else {
                        std::cout << "Selección inválida." << std::endl;
                        reintentar = deseaReintentar();
                    }
                } while (reintentar);
                break;
            }
            case 5: {
                if (estudiantes.empty()) {
                    std::cout << "No hay estudiantes registrados." << std::endl;
                    break;
                }

                std::cout << "\nSeleccione el estudiante por número:\n";
                for (size_t i = 0; i < estudiantes.size(); ++i) {
                    std::cout << i + 1 << ". " << estudiantes[i].nombreCompleto() << std::endl;
                }
                int seleccion = obtenerEntradaNumerica() - 1;

                if (seleccion >= 0 && seleccion < estudiantes.size()) {
                    estudiantes[seleccion].mostrarCalificaciones();
                } else {
                    std::cout << "Selección inválida." << std::endl;
                }
                break;
            }
            case 6: {
                bool reintentar;
                do {
                    reintentar = false;
                    if (estudiantes.empty()) {
                        std::cout << "No hay estudiantes registrados." << std::endl;
                        break;
                    }

                    std::cout << "\nSeleccione el estudiante por número:\n";
                    for (size_t i = 0; i < estudiantes.size(); ++i) {
                        std::cout << i + 1 << ". " << estudiantes[i].nombreCompleto() << std::endl;
                    }
                    int seleccion = obtenerEntradaNumerica() - 1;

                    if (seleccion >= 0 && seleccion < estudiantes.size()) {
                        std::cout << "Ingrese el nuevo nombre: ";
                        std::string nuevoNombre = obtenerEntradaTexto();
                        std::cout << "Ingrese el nuevo apellido: ";
                        std::string nuevoApellido = obtenerEntradaTexto();
                        estudiantes[seleccion].cambiarNombre(nuevoNombre);
                        estudiantes[seleccion].cambiarApellido(nuevoApellido);
                        std::cout << "Nombre y apellido cambiados correctamente." << std::endl;
                    } else {
                        std::cout << "Selección inválida." << std::endl;
                        reintentar = deseaReintentar();
                    }
                } while (reintentar);
                break;
            }
            case 7: {
                bool reintentar;
                do {
                    reintentar = false;
                    if (estudiantes.empty()) {
                        std::cout << "No hay estudiantes registrados." << std::endl;
                        break;
                    }

                    std::cout << "\nSeleccione el estudiante por número:\n";
                    for (size_t i = 0; i < estudiantes.size(); ++i) {
                        std::cout << i + 1 << ". " << estudiantes[i].nombreCompleto() << std::endl;
                    }
                    int seleccion = obtenerEntradaNumerica() - 1;

                    if (seleccion >= 0 && seleccion < estudiantes.size()) {
                        estudiantes.erase(estudiantes.begin() + seleccion);
                        std::cout << "Estudiante eliminado correctamente." << std::endl;
                    } else {
                        std::cout << "Selección inválida." << std::endl;
                        reintentar = deseaReintentar();
                    }
                } while (reintentar);
                break;
            }
            case 8: {
                mostrarEstudiantesOrdenadosPorPromedio(estudiantes);
                break;
            }
            case 9: {
                std::cout << "Ingrese el nombre del archivo CSV desde el cual importar los datos (incluya la extensión '.csv'): ";
                std::string nombreArchivo = obtenerEntradaTexto();
                importarDesdeCSV(estudiantes, nombreArchivo);
                break;
            }
            case 10: {
                std::cout << "Ingrese el nombre del archivo CSV al cual exportar los datos (incluya la extensión '.csv'): ";
                std::string nombreArchivo = obtenerEntradaTexto();
                exportarACSV(estudiantes, nombreArchivo);
                break;
            }
            case 0: {
                if (deseaExportarAntesDeSalir()) {
                    std::cout << "Ingrese el nombre del archivo CSV al cual exportar los datos (incluya la extensión '.csv'): ";
                    std::string nombreArchivo = obtenerEntradaTexto();
                    exportarACSV(estudiantes, nombreArchivo);
                }
                salir = true;
                break;
            }
            default:
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                break;
        }
    } while (!salir);

    std::cout << "Gracias por usar el sistema de gestión de estudiantes." << std::endl;
    return 0;
}
