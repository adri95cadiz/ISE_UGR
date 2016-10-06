#include<iostream>
#include<fstream>
#include<time.h>
#include<string>
#include<stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <omp.h>
#include<sstream>
using namespace std;

#ifndef __BENCHMARK__
#define __BENCHMARK__

class Benchmark{
	private:
//--------------------Vars-------------------------------------------
		string dev;													//Cadena de texto que guarda la ruta del dispositivo conectado.
		int levels;													//Entero que guarda el numero de niveles (dispositivos) que se van ha realizar.
		string usbBus, usbDevice, usbName;					//Cadenas de texto con el nombre del bus, dispositivo, y nombre del mismo.
		double ** last_operation;								//Matriz que almacena la ultima operacion del experimento 1.
		double ** last_operation2;								//Matriz que almacena la ultima operacion del experimento 2.
//--------------------Write and Read operations----------------------
/*Funcion WriteOp(): Se encarga de realizar la escritura de un archivo de 2GB de tamanio en el dispositivo indicado con la ruta almacenada en dev.
Devuelve el tiempo que se ha tardado en realizar dicha operacion.*/
		double writeOp();
/*Funcion readOp():Se encarga de realizar la lectura de un archivo de 2GB de tamanio en el dispositivo indicado con la ruta almacenada en dev.
Devuelve el tiempo que se ha tardado en realizar dicha operacion.*/
		double readOp();
/*Funcion readwriteOp():Se encarga de realizar la escritura y lectura (alternando) de un archivo de 2GB de tamanio en el dispositivo indicado con la ruta almacenada en dev.
Devuelve el tiempo que se ha tardado en realizar dicha operacion.*/
		double readwriteOp();
/*Funcion lwriteOp():Se encarga de realizar la escritura de 100 archivos con 50MB cada uno de tamanio en el dispositivo indicado con la ruta almacenada en dev.
Devuelve el tiempo que se ha tardado en realizar dicha operacion.*/
		double lwriteOp();
/*Funcion lreadOp():Se encarga de realizar la lectura de 100 archivos con 50MB cada uno de tamanio en el dispositivo indicado con la ruta almacenada en dev.
Devuelve el tiempo que se ha tardado en realizar dicha operacion.*/
		double lreadOp();
/*Funcion lreadwriteOp():Se encarga de realizar la escritura y lectura (alternando) de 100 archivos con 50MB cada uno de tamanio en el dispositivo indicado con la ruta almacenada en dev.
Devuelve el tiempo que se ha tardado en realizar dicha operacion.*/
		double lreadwriteOp();
	public:
//--------------------Other operations-------------------------------
/*Funcion Benchmark():Constructor de la clase Benchmark se encarga de inicializar las matrices last_operation y las variables necesarias.*/
		Benchmark(int levels);
/*Funcion ~Benchmark():Destructor de la clase Benchmark para la memoria dinamica reservada con las matrices.*/
		~Benchmark();
/*Funcion showLastBenchmark(): Muestra por pantalla el contenido de la matriz oper.*/
		void showLastBenchmark(double **oper);
/*Funcion usbInfo():Se encarga de recopilar datos del USB en cuestion sin embargo no se ha podido dar una utilidad completa por falta de tiempo.*/
		void usbInfo();
/*Funcion mbps():Calcula los MB/s a partir del tiempo time y el tamaño de archivo file_size*/
		double mbps(double time, double file_size);
/*Funcion saveData():Copia los datos obtenidos en un archivo csv que permite manipularlos con un editor estadistico.*/
		void saveData(int exp);
/*Funcion itos():convierte un int a un string*/
		string itos(int i){
    		stringstream s;
    		s << i;
    		return s.str();
		}
//--------------------USB devices Benchmark--------------------------
/*Funcion usbMemoryTest():Es a funcion principal se encarga de realizar los test para conseguir los datos de los experimentos 1 y 2, ejecuta unas 5 veces cada funcion de lectura y escritura para obtener los datos y los va almacenando en las matrices.*/
		void usbMemoryTest(int level, int exp);
};

#endif
