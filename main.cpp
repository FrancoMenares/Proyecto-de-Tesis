
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
#include "z-EscrituraFrente.h"
#include "z-Trazado.h"

using namespace std;


int main(int argc, char **argv){

  //identificacion ARGV
  string archivo_red = argv[1]          ; //nombre archivo red
  string archivo_ins = argv[2]          ; //nombre archivo instancia
  float frec_salidas = atof(argv[3])/60 ; //frecuencia para preprocesamiento de la red
  int semilla = atoi(argv[4])           ; //semilla de ejecucion
  int lambda = atoi(argv[5])             ; //tamaño de la poblacion
  int p_aceptacion = atoi(argv[6])      ; //pobabilidad de aceptacion de padre
  int p_cruce = atoi(argv[7])           ; //probabilidad de cruce
  int p_mutacion = atoi(argv[8])        ; //probabilidad de mutacion
  int generaciones = atoi(argv[9])      ; //cantidad de generaciones
  

  //control aleatoriedad
  //srand(semilla)              ; //se fija una semilla 


  //Lectura Red de carreteras
  LecturaRed lr(archivo_red)  ; //se crea un objeto de tipo LecturaRed
  Red* red = lr.lectura_red() ; //se lee la red de carreteras
  red->imprimir_red()         ;
  

  //Lectura Instancia
  LecturaInstancia li(archivo_ins)              ; //se crea un objeto de tipo LecturaInstancia
  Instancia* instancia = li.lectura_instancia() ; //se lee la red de carreteras
  instancia->imprimir_instancia()               ;


  //Preprocesamiento de la red
  Preprocesamiento* preprocesar = new Preprocesamiento()     ; //se crea un objeto de tipo Preprocesamiento
  preprocesar->preprocesar_red(red, instancia, frec_salidas) ; //se preprocesa la rede de carreteras
  preprocesar->imprimir_tiempo_ejecucion()                   ;


  //Aprobacion de la instancia
  instancia->verificar_instancia() ; //se comprueba la conectividad de la instancia


  //Escribir .dat para el modelo
  EscrituraInstancia escribir_i(archivo_ins) ;
  escribir_i.escribir_instancia(instancia)   ;


  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  //:::::::::::::::::::::::::::::::::::::::::::::  NSGA-II :::::::::::::::::::::::::::::::::::::::::::::
  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  lambda       = 50    ;
  p_aceptacion = 80    ;
  p_cruce      = 90    ;
  p_mutacion   = 90    ;
  generaciones = 10000 ;

  srand(111)         ;

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

    if (generacion%500 == 0) { cout << generacion << endl ;}
    
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

  //clasificar individuos en los frentes F_i
  R->clasificar_poblacion(F, lambda)                                       ;

  //F->imprimir_frentes_1()                                                  ;
  F->imprimir_frentes_2()                                                  ;

  //calcular distancia de hacinamiento obteniendo la proxima generacion de padres P_t+1
  //P->agregar_nuevos_padres(F, lambda)                                      ;

  //se finaliza el tiempo de ejecucion
  cout << "================================================================="    << endl            ;
  cout << "Tiempo NSGA-II: " << float (difftime(clock(), tiempo)/CLOCKS_PER_SEC) << " seg." << endl ;
  cout << "================================================================="    << endl    << endl ;

}



























/*
  for (Individuo* s: P->get_poblacion()){
    cout << s->get_f1() << "\t" << s->get_f2() << "\t" << s->get_ranking() << "/" << s->get_hacinamiento() << endl ;
  }
*/

/*
    if (debug){
      cout << endl << "1 ::::"                            ; 
      cout << "\t P: " << P->get_poblacion().size()       ;
      cout << "\t Q: " << Q->get_poblacion().size()       ;
      cout << "\t R: " << R->get_poblacion().size()       ;
      cout << "\t F: " << F->get_frentes().size() << endl ;

      cout << endl ;
      cout << "PADRES" << endl ;
      for (Individuo* i: P->get_poblacion()){
        cout << i->get_f1() << "\t" << i->get_f2() << " \t" << i->get_dominado_por() << "/" << i->get_individuos_dominados().size() << "\t" << i->get_ranking() << "/" << i->get_hacinamiento() << endl ;
      }
      cout << endl ;

      cout << "HIJOS" << endl ;
      for (Individuo* i: Q->get_poblacion()){
        cout << i->get_f1() << "\t" << i->get_f2() << " \t" << i->get_dominado_por() << "/" << i->get_individuos_dominados().size() << "\t" << i->get_ranking() << "/" << i->get_hacinamiento() << endl ;
      }
      cout << endl ;
    }

    if (debug){
      cout << "2 ::::"                            ; 
      cout << "\t P: " << P->get_poblacion().size()       ;
      cout << "\t Q: " << Q->get_poblacion().size()       ;
      cout << "\t R: " << R->get_poblacion().size()       ;
      cout << "\t F: " << F->get_frentes().size() << endl ;

      cout << endl ;
      cout << "UNION" << endl ;
      for (Individuo* i: R->get_poblacion()){
        cout << i->get_f1() << "\t" << i->get_f2() << " \t" << i->get_dominado_por() << "/" << i->get_individuos_dominados().size() << "\t" << i->get_ranking() << "/" << i->get_hacinamiento() << endl ;
      }
      cout << endl ;
    }

    if (debug){
      cout << "3 ::::"                            ; 
      cout << "\t P: " << P->get_poblacion().size()       ;
      cout << "\t Q: " << Q->get_poblacion().size()       ;
      cout << "\t R: " << R->get_poblacion().size()       ;
      cout << "\t F: " << F->get_frentes().size() << endl ;

      ///*
      cout << endl ;
      cout << "FRENTE" << endl ;
      for (vector <Individuo*> i: F->get_frentes()){
        for (Individuo* j: i){
          cout << j->get_f1() << "\t" << j->get_f2() << "\t" << j->get_dominado_por() << "/" << j->get_individuos_dominados().size() << "\t" << j->get_ranking() << "/" << j->get_hacinamiento() << endl ;
        }
      }
      cout << endl ;
    }

    if (debug){
      cout << "4 ::::"                            ; 
      cout << "\t P: " << P->get_poblacion().size()       ;
      cout << "\t Q: " << Q->get_poblacion().size()       ;
      cout << "\t R: " << R->get_poblacion().size()       ;
      cout << "\t F: " << F->get_frentes().size() << endl ;

      cout << endl ;
      cout << "NUEVOS PADRES" << endl ;
      for (Individuo* i: P->get_poblacion()){
        cout << i->get_f1() << "\t" << i->get_f2() << " \t" << i->get_dominado_por() << "/" << i->get_individuos_dominados().size() << "\t" << i->get_ranking() << "/" << i->get_hacinamiento() << endl ;
      }
      cout << endl ;
    }

    if (debug){
      cout << "5 ::::"                            ; 
      cout << "\t P: " << P->get_poblacion().size()       ;
      cout << "\t Q: " << Q->get_poblacion().size()       ;
      cout << "\t R: " << R->get_poblacion().size()       ;
      cout << "\t F: " << F->get_frentes().size() << endl ;

      cout << endl ;
      cout << "NUEVOS HIJOS" << endl ;
      for (Individuo* i: Q->get_poblacion()){
        cout << i->get_f1() << "\t" << i->get_f2() << " \t" << i->get_dominado_por() << "/" << i->get_individuos_dominados().size() << "\t" << i->get_ranking() << "/" << i->get_hacinamiento() << endl ;
      }
      cout << endl ;
    }
*/

