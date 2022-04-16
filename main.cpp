
#include <iostream>
#include <random>
#include <vector>
#include <time.h>
#include <string.h>

#include "b-Red.h"
#include "c-LecturaRed.h"
#include "e-Instancia.h"
#include "f-LecturaInstancia.h"
#include "i-Preprocesamiento.h"
#include "n-Poblacion.h"
#include "s-Frentes.h"

#include "t-ReRuteo.h"


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
  int num_reruteos  = atoi(argv[10])    ; //numero de reruteos
  int criterio_parada = 50              ; //generaciones estancadas para GA

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
  //preprocesar->imprimir_tiempo_ejecucion()                   ;


  //Aprobacion de la instancia
  instancia->verificar_instancia() ; //se comprueba la conectividad de la instancia


  //Escribir .dat para el modelo
  //EscrituraInstancia escribir_i(archivo_ins) ;
  //escribir_i.escribir_instancia(instancia)   ;


  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  //:::::::::::::::::::::::::::::::::::::::::::::  NSGA-II :::::::::::::::::::::::::::::::::::::::::::::
  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
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
  R->obtener_frente_pareto(F, lambda)                                      ;
  
  
  //se finaliza el tiempo de ejecucion
  float tiempo_ej = float (difftime(clock(), tiempo)/CLOCKS_PER_SEC)                             ;
  //cout << "=================================================================" << endl            ;
  //cout << "Tiempo NSGA-II: " << tiempo_ej                                     << " seg." << endl ;
  //cout << "=================================================================" << endl    << endl ;

  //F->imprimir_frente_2(0);
  



  ///*
  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  //::::::::::::::::::::::::::::::::::::::::::::: RERUTEO ::::::::::::::::::::::::::::::::::::::::::::::
  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  ReRuteo* RE = new ReRuteo()                               ; //se crea un objeto de tipo ReRuteo
  Preprocesamiento* preprocesar_re = new Preprocesamiento() ; //se crea un objeto de tipo Preprocesamiento
  
  Frentes* F_re = new Frentes()    ; //frente reruteado
  vector <Individuo*> frente = {}  ; //cada frente contien un par (individuo, individuo de reruteo)
  Individuo* aux = new Individuo() ; //individuo auxiliar para individuos que no tienen reruteo
  
  Poblacion* P_re   ; //poblacion de padres
  Poblacion* Q_re   ; //poblacion de hijos
  float MC          ; //mejor f1
  int estancamiento ; //estancamiento de la soluciones
  int p_cruce_2     ; //probabilidad de cruce

  int lambda2 = int (lambda/4) ;

  //int num_reruteos  = 30 ; //
  float tiempo_re_1 = 0  ; //
  float tiempo_re_2      ; //
  
  
  for (Individuo* i: F->get_frente(0)){    //se recorre el frente de pareto

    for (int ll=0; ll<num_reruteos; ll++){ //para cada individuo se rerutea varias veces

      Instancia* instancia_re = RE->crear_instancia_de_reruteo(i, instancia) ; //se crea instancia con clientes a rerutear
      preprocesar_re->preprocesar_red(red, instancia_re, frec_salidas)       ; //se preprocesa la red de carreteras
      instancia_re->verificar_instancia()                                    ; //se verifica que conectividad de la instancia

      if (instancia_re->get_cant_clientes() > 2){
        p_cruce_2 = p_cruce ;
      } else {
        p_cruce_2 = -1      ;
      }

      if (instancia_re->get_cant_clientes() > 0){
        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        //::::::::::::::::::::::::::::::::::::::::::::::: GA :::::::::::::::::::::::::::::::::::::::::::::::
        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        P_re = new Poblacion(instancia_re) ;
        Q_re = new Poblacion(instancia_re) ; 
        MC = 99999999.9                    ;
        estancamiento = 0                  ;
        tiempo_re_2 = 0                    ;
        
        //se inicializa el tiempo de ejecucion
        clock_t tiempo_re = clock()                                                        ;

        //inicializacion de las generaciones
        generacion = 0                                                                     ;

        //generar poblacion de padres P_0
        P_re->construir_poblacion_inicial(lambda2)                                          ;

        //generar poblacion de descendientes Q_0
        P_re->generar_descendientes_2(Q_re, lambda2, p_aceptacion, p_cruce_2, p_mutacion)   ;

        //mientras corren las generaciones t
        while (generacion < generaciones && estancamiento < criterio_parada){

          //clasificar la proxima generacion de padres P_t+1
          P_re->clasificar_poblacion_2(Q_re, lambda2)                                       ;

          //verificar estancamiento del algoritmo
          if (P_re->get_individuo(0)->get_f1() < MC){
            MC = P_re->get_individuo(0)->get_f1()                                          ;
            estancamiento = 0                                                              ;
          } else {
            estancamiento++                                                                ;
          }

          //generar la proxima generacion de hijos Q_t+1
          P_re->generar_descendientes_2(Q_re, lambda2, p_aceptacion, p_cruce_2, p_mutacion) ;

          //avanzar a la siguiente generacion
          generacion++                                                                     ;
        }
        
        //clasificar ultima generacion de padres P_t+1
        P_re->clasificar_poblacion_2(Q_re, lambda2)                                         ;
        
        //se finaliza el tiempo de ejecucion
        tiempo_re_2 = tiempo_re_2 + float (difftime(clock(), tiempo_re)/CLOCKS_PER_SEC)    ;

        //obtener el mejor individuo
        P_re->get_individuo(0)->set_f2(tiempo_re_2) ; //
        frente.push_back(P_re->get_individuo(0))    ; //

        delete instancia_re    ; //
        delete P_re            ; // 
        delete Q_re            ; // 
      
      } else {
        tiempo_re_2 = 0        ; //
        frente.push_back(aux)  ; //
        
        delete instancia_re    ; //
      }

      tiempo_re_1 = tiempo_re_1 + tiempo_re_2 ; //
    }

    F_re->agregar_frente(frente) ; //
    frente.clear()               ; //
    frente.shrink_to_fit()       ; //
  }

  //cout << endl ;
  //F_re->imprimir_frentes_2();
  

  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  //::::::::::::::::::::::::::::::::::::::::::::::::: Resultados :::::::::::::::::::::::::::::::::::::::
  //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  cout << semilla << " " << lambda << " " << p_aceptacion << " " << p_cruce << " " << p_mutacion << " " << generaciones << " " << preprocesar->get_tiempo_pre_prop() << " " << tiempo_ej << " " << tiempo_re_1 << endl ;

  int pos = archivo_ins.find("-")                                 ;
  string nom_inst = ""                                            ;
  for (int i=0; i<archivo_ins.substr(pos-1).length()-4; i++){
    nom_inst = nom_inst + archivo_ins.substr(pos-1)[i]            ;
  }
  string params = to_string(semilla) + "-" + to_string(lambda) + "-" + to_string(p_aceptacion) + "-" + to_string(p_cruce) + "-" + to_string(p_mutacion) + "-" + to_string(generaciones) ;


  //----------- resultados NSGA-II -----------
  F->escribir_frente_final(nom_inst, params)                      ;
  Trazado* T = new Trazado()                                      ;
  T->escibir_rutas_completas(nom_inst, params, F, red, instancia) ;

  
  //-------------- resultados GA -------------
  F_re->escribir_frente_final_re(F, nom_inst, params)             ;

  //*/

}











