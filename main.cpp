
#include <iostream>
#include <random>
#include <vector>
#include <time.h>

#include "b-Red.h"
#include "c-LecturaRed.h"
#include "e-Instancia.h"
#include "f-LecturaInstancia.h"
#include "i-Preprocesamiento.h"
#include "m-Construccion.h"

using namespace std;

///*
int main(int argc, char **argv){

  //identificacion ARGV
  string archivo_red = argv[1]          ; //nombre archivo red
  string archivo_ins = argv[2]          ; //nombre archivo instancia
  float frec_salidas = atof(argv[3])/60 ; //frecuencia para preprocesamiento de la red
  int semilla = atoi(argv[4])           ; //semilla de ejecucion
  
  //Lectura Red de carreteras
  LecturaRed lr(archivo_red)  ; //se crea un objeto de tipo LecturaRed
  Red* red = lr.lectura_red() ; //se lee la red de carreteras
  red->imprimir_red()         ;
  
  //Lectura Instancia
  LecturaInstancia li(archivo_ins)              ; //se crea un objeto de tipo LecturaInstancia
  Instancia* instancia = li.lectura_instancia() ; //se lee la red de carreteras
  instancia->imprimir_instancia()               ;

  //preprocesamiento de la red
  Preprocesamiento* preprocesar = new Preprocesamiento()     ; //se crea un objeto de tipo Preprocesamiento
  preprocesar->preprocesar_red(red, instancia, frec_salidas) ; //se preprocesa la rede de carreteras
  preprocesar->imprimir_tiempo_ejecucion()                   ;
  

  srand(semilla) ; //se fija una semilla 


  //Solucion de prueba
  Individuo* aux = new Individuo(0);
  Construccion* construir = new Construccion(); 

  construir->individuo_aleatorio(instancia, aux);
  aux->imprimir_individuo();
  
}









