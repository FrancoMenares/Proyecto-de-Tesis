//
#include <iostream>
#include <random>
#include <vector>
#include <time.h>

#include "b-Red.h"
#include "c-LecturaRed.h"
#include "e-Instancia.h"
#include "f-LecturaInstancia.h"
#include "i-Preprocesamiento.h"
#include "n-Poblacion.h"
#include "s-Frentes.h"

#include "z-EscrituraInstancia.h"
#include "z-Trazado.h"


using namespace std;


int main(int argc, char **argv){

  //identificacion ARGV
  string archivo_red = argv[1]          ; //nombre archivo red
  string archivo_ins = argv[2]          ; //nombre archivo instancia
  float frec_salidas = atof(argv[3])/60 ; //frecuencia para preprocesamiento de la red
  int semilla = atoi(argv[4])           ; //semilla de ejecucion
  int lambda = atoi(argv[5])            ; //tamaño de la poblacion
  int p_aceptacion = atoi(argv[6])      ; //pobabilidad de aceptacion de padre
  int p_cruce = atoi(argv[7])           ; //probabilidad de cruce
  int p_mutacion = atoi(argv[8])        ; //probabilidad de mutacion
  int generaciones = atoi(argv[9])      ; //cantidad de generaciones

  bool debug = false ;
  

  //control aleatoriedad
  srand(semilla) ; //se fija una semilla 


  //Lectura Red de carreteras
  LecturaRed lr(archivo_red)      ; //se crea un objeto de tipo LecturaRed
  Red* red = lr.lectura_red()     ; //se lee la red de carreteras
  if (debug){ red->imprimir_red() ;}
  

  //Lectura Instancia
  LecturaInstancia li(archivo_ins)              ; //se crea un objeto de tipo LecturaInstancia
  Instancia* instancia = li.lectura_instancia() ; //se lee la red de carreteras
  if (debug){ instancia->imprimir_instancia()   ;}


  //Preprocesamiento de la red
  Preprocesamiento* preprocesar = new Preprocesamiento()     ; //se crea un objeto de tipo Preprocesamiento
  preprocesar->preprocesar_red(red, instancia, frec_salidas) ; //se preprocesa la rede de carreteras
  preprocesar->imprimir_tiempo_ejecucion()                   ;


  //Aprobacion de la instancia
  instancia->verificar_instancia() ; //se comprueba la conectividad de la instancia


  //Escribir .dat para el modelo
  //EscrituraInstancia escribir_i(archivo_ins) ;
  //escribir_i.escribir_instancia(instancia)   ;


  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  //:::::::::::::::::::::::::::::::::::::::::::::  NSGA-II :::::::::::::::::::::::::::::::::::::::::::::
  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  if (debug){
    cout << "-----------------------------------------------------------------" << endl ;
    cout << "Semilla          : " << semilla      << endl ;
    cout << "Tamano Poblacion : " << lambda       << endl ;
    cout << "Prob. Aceptacion : " << p_aceptacion << endl ;
    cout << "Prob. Cruce      : " << p_cruce      << endl ;
    cout << "Prob. Mutacion   : " << p_mutacion   << endl ;
    cout << "N° Generaciones  : " << generaciones << endl ;
    cout << "-----------------------------------------------------------------" << endl << endl ;
  }


  Poblacion* P = new Poblacion(instancia) ; //
  Poblacion* Q = new Poblacion(instancia) ; //
  Poblacion* R = new Poblacion(instancia) ; //
  Frentes*   F = new Frentes()            ; //


  //se inicializa el tiempo de ejecucion
  clock_t tiempo = clock()                                                 ;
  
  //inicializacion de las generaciones
  int generacion = 0                                                       ;

  //generar poblacion de padres P_0
  P->construir_poblacion_inicial(lambda)                                   ;

  //generar poblacion de descendientes Q_0
  P->generar_descendientes(Q, lambda, p_aceptacion, p_cruce, p_mutacion)   ;

  //mientras corren las generaciones t
  while (generacion < generaciones){
    //if (generacion%1000 == 0) { cout << generacion << endl ;}
    
    //combinar poblacion de padres e hijos R_t = P_t + Q_t
    R->combinar_poblacion(P, Q)                                            ;

    //clasificar individuos en los frentes F_i
    R->clasificar_poblacion(F, lambda)                                     ;
    
    //calcular distancia de hacinamiento obteniendo la proxima generacion de padres P_t+1
    P->agregar_nuevos_padres(F, lambda)                                    ;
    
    //generar la proxima generacion de hijos Q_t+1
    P->generar_descendientes(Q, lambda, p_aceptacion, p_cruce, p_mutacion) ;
    
    //avanzar a la siguiente generacion
    generacion++                                                           ;
  }

  //combinar poblacion de padres e hijos R_t = P_t + Q_t
  R->combinar_poblacion(P, Q)                                              ;

  //clasificar individuos del frente F_0
  R->obtener_frente_pareto(F)                                              ;
  //R->clasificar_poblacion(F, lambda)                                       ;
  //F->clasificar_frente_final()                                             ;

  //se finaliza el tiempo de ejecucion
  cout << " " << float (difftime(clock(), tiempo)/CLOCKS_PER_SEC) << endl  ;

  //float tiempo_ej = float (difftime(clock(), tiempo)/CLOCKS_PER_SEC)                             ;
  //cout << "=================================================================" << endl            ;
  //cout << "Tiempo NSGA-II: " << tiempo_ej                                     << " seg." << endl ;
  //cout << "=================================================================" << endl    << endl ;


  F->escribir_frente_final("Resultados/")                                  ;

  Trazado* T = new Trazado()                                               ;
  T->escibir_rutas_completas("Resultados/", F, red, instancia)             ;
}











