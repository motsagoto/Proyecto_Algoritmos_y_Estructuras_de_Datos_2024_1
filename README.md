# Proyecto_Algoritmos_y_Estructuras_de_Datos_2024_1


# Sistema de Gestión de Estudiantes

El "Sistema de Gestión de Estudiantes" es una aplicación de consola en C++ que permite gestionar información de estudiantes y sus calificaciones. 

## Funcionalidades

1. **Agregar Estudiante**
2. **Asignar Nota Parcial**
3. **Cambiar Nota de Estudiante**
4. **Eliminar Nota de Estudiante**
5. **Mostrar Calificaciones de un Estudiante**
6. **Cambiar Nombre/Apellido de un Estudiante**
7. **Eliminar Estudiante**
8. **Mostrar Lista de Estudiantes Ordenados por Promedio**
9. **Importar Datos desde un Archivo CSV**
10. **Exportar Datos a un Archivo CSV**
11. **Salir del Programa**

## Estructura del Proyecto

### Clase `Estudiante`

#### Atributos
- `nombre`: Nombre del estudiante.
- `apellido`: Apellido del estudiante.
- `notas`: Lista de notas del estudiante.

#### Métodos
- `nombreCompleto()`
- `agregarNota(nota)`
- `cambiarNota(indice, nuevaNota)`
- `eliminarNota(indice)`
- `mostrarCalificaciones()`
- `calcularPromedio()`
- `cambiarNombre(nuevoNombre)`
- `cambiarApellido(nuevoApellido)`

### Funciones Principales

- `obtenerEntradaNumerica()`
- `obtenerEntradaTexto()`
- `deseaReintentar()`
- `importarDesdeCSV(estudiantes, nombreArchivo)`
- `exportarACSV(estudiantes, nombreArchivo)`
- `quicksort(arr, low, high)`
- `insertsort(arr)`
- `mostrarEstudiantesOrdenadosPorPromedio(estudiantes)`
- `deseaExportarAntesDeSalir()`

## Ejecución del Programa

### Compilación

```sh
g++ -o gestion_estudiantes gestion_estudiantes.cpp
```

### Ejecución

```sh
./gestion_estudiantes
```

## Uso del Programa

Al iniciar el programa, se mostrará un menú con las opciones disponibles. El usuario puede seleccionar una opción ingresando el número correspondiente. Después de completar una operación, el menú se mostrará nuevamente hasta que el usuario decida salir del programa.

## Notas

- Asegúrese de que los archivos CSV utilizados para importar/exportar datos sigan el formato correcto: `nombre,apellido,nota1,nota2,...,notaN`.
- El programa incluye validaciones básicas para entradas numéricas y textuales, así como para la gestión de errores al abrir archivos.

## Contribuciones

Las contribuciones al proyecto son bienvenidas. Siéntase libre de realizar un fork del repositorio y enviar pull requests con mejoras o correcciones.
¡Gracias por utilizar el Sistema de Gestión de Estudiantes!
