#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 
#include "omp.h"
#define PI 3.14159265358979323846

using namespace std;

/**
* Función haversine
*/
double haversine(double latitud1, double longitud1, double latitud2, double longitud2);

/**
 * Función que muestra los participantes del grupo
 */
void participantes();

int main()
{
    /**
     * 
     * linea se usará para quitar los titulos
     * equipo guardará el nombre de cada equipo
     * comuna guardará el nombre de cada comuna
     * estadio guardará el nombre de cada estadio
     * latitud guardará el nombre de cada latitud
     * longitud guardará el nombre de cada longitud
     */ 
    string linea,equipo,comuna,estadio,latitud,longitud;
    /**
     * vectorEquipo es un vector donde se guardarán todos los nombres de los equipos
     * vectorComuna es un vector donde se guardarán todos los nombres de las comunas
     * vectorEstadio es un vector donde se guardarán todos los nombres de los estadios
     * vectorLatitud es un vector donde se guardarán todas las Latitudes
     * VectorLongitud es un vector donde se guardarán todas las Longitudes
     */
    vector<string> vectorEquipo,vectorComuna,vectorEstadio,vectorLatitud,vectorLongitud;
    /**
     * 
     * vectorLatitudInt Vector donde alojaremos las latitudes transformadas a double
     * vectorLongitudInt Vector donde alojaremos las longitudes transformadas a double
     * 
     */
    vector<double> vectorLatitudInt,vectorLongitudInt;

    // **
    // A R C H I V O E Q U I P O S

    ifstream archivo;
    archivo.open("equipos.csv");
#pragma omp parallel
    {
#pragma omp single 
        {
    getline(archivo,linea); // Q U I T A T Í T U L O S
    
#pragma omp task
            {

    while(archivo.good())
        {
        getline(archivo, equipo, ';');
        vectorEquipo.push_back(equipo);

        getline(archivo, comuna, ';');
        vectorComuna.push_back(comuna);

        getline(archivo, estadio, ';');
        vectorEstadio.push_back(estadio);

        getline(archivo, latitud, ';');
        vectorLatitud.push_back(latitud);

        getline(archivo, longitud, '\n');
        vectorLongitud.push_back(longitud);
            }

    for (int a = 0; a < 17; a++){
        string LAT = vectorLatitud[a].substr(1,vectorLongitud[a].length());
        double LATITUD = atof(LAT.c_str());
        vectorLatitudInt.push_back(LATITUD);
        string LONG = vectorLongitud[a].substr(1,vectorLongitud[a].length());
        double LONGITUD = atof(LONG.c_str());
        vectorLongitudInt.push_back(LONGITUD);
    }

    // **
    // C R E A A R C H I V O F I X T U R E

    ofstream archivoFixture("fixture.csv");

    archivoFixture << "Fecha;";
    archivoFixture << "Local;";
    archivoFixture << "Visita;";
    archivoFixture << "Distancia\n";

    int fechas[306];

    for(int i=0;i<306;i++){
        fechas[i]=i+1;
    }

    double Latitud1,Latitud2,Longitud1,Longitud2;
    float aux;

#pragma omp critical
    string partidos[17][153][2];
    int k=0;
    for(int i=0;i<17;i++)
    {
        for(int j=0;j<18;j++)
        {
            if(i!=17-j){
            Latitud1 = vectorLatitudInt[i];
            Latitud2 = vectorLatitudInt[17-j];
            Longitud1 = vectorLongitudInt[i];
            Longitud2 = vectorLongitudInt[17-j];
            aux = haversine(Latitud1, Longitud1, Latitud2, Longitud2);
            archivoFixture << fechas[k];
            archivoFixture << ";"+vectorEquipo[i];
            archivoFixture << ";"+vectorEquipo[17-j] + ";";
            archivoFixture << aux << endl;
            k++;}
        }
        archivoFixture << endl;
                }
            }
        }
    }

    return 0;
}

/**
 * @latitud1 latitud del local
 * @longitud1 longitud del local
 * @latitud2 latitud del visitante
 * @longitud2 longitud del visitante
 * esta funcion retorna la distancia existente entre el local y el visitante
 */
double haversine(double latitud1, double longitud1, double latitud2, double longitud2) 
    { 
    double distLat = (latitud2 - latitud1) * PI / 180.0; 
    double distLon = (longitud2 - longitud1) * PI / 180.0; 
    latitud1 = (latitud1) * PI / 180.0; 
    latitud2 = (latitud2) * PI / 180.0; 
    double formula = pow(sin(distLat / 2), 2) + pow(sin(distLon / 2), 2) * cos(latitud1) * cos(latitud2); 
    double radio = 6371; 
    double ecuacion = 2 * asin(sqrt(formula)); 
    return (radio * ecuacion); 
} 

void participantes() {
    std::cout << std::endl << "=== Tarea ===" << std::endl;
    std::cout << std::endl << "Shu-yi Wong" << std::endl; 
    std::cout << std::endl << "Javier Lopez" << std::endl; 
    std::cout << std::endl << "Alex Bidart" << std::endl; 
}