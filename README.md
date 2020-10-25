# Taller 3, Fixture Futbol

Trabajo de Fixture Futbol para Asignatura Computación Paralela

### Lenguaje y Librerias necesarias

#### Lenguaje

* C++

#### Librerias

* Iostream y Fstream
* Vector y String
* Cmath
* OpemMP

### Pasos para activar el programa

* Ejecutar el archivo Makefile con los comandos ```make clean && make```
* Ejecutar en comando ./dist/programa

#### Lo que hace
El programa lee un archivo csv llamado "equipos", el cual guarda por vectores cada columna, luego transforma los datos "string" de los vectores latitud y longitud en un nuevo vector de tipo double, luego hace las formulas.

#### Funciones

* Se crea la función haversine que viene de la Ley del semiverseno, para calcular la distancia minima entre dos puntos con longitud y latitud

### Autores
* Javier Lopez
* Alex Bidart
* Shu-yi Wong
