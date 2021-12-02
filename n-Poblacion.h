
#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#include "e-Instancia.h"
#include "l-Individuo.h"

#include "m-Construccion.h"

#include "ñ-AjusteHora.h"
#include "o-CambioCliente.h"
#include "p-InvertirClientes.h"

#include "q-OX.h"

#include "s-Frentes.h"


using namespace std;


class Poblacion{
  private:
    Instancia* instancia          ; //instancia del problema
    vector <Individuo*> poblacion ; //vector de soluciones
  
  public:
    Poblacion(Instancia* instancia) ; //Constructor
    ~Poblacion(){}                  ; //Destructor

    //--------------- Instancia ---------------
    Instancia* get_instancia(void)                 ;

    //--------------- Poblacion ---------------
    void agregar_individuo(Individuo* i)           ;
    void insertar_individuo(int pos, Individuo* i) ;
    void eliminar_individuo(int pos)               ;

    vector <Individuo*> get_poblacion(void)        ;
    Individuo* get_individuo(int pos)              ;

    void eliminar_poblacion(void)                  ;
    void limpiar_poblacion(void)                   ;
    
    //--------------- imprimir poblacion ---------------
    void imprimir_poblacion(void)                  ;
    
    //--------------- contruccion de la poblacion inicial ---------------
    void construir_poblacion_inicial(int lambda)   ;
    
    //--------------- seleccion de padre para cruce ---------------
    Individuo* torneo_binario_1(int aceptacion)             ;
    Individuo* torneo_binario_2(Individuo* p, Individuo* q) ;
    
    //--------------- generacion de los hijos ---------------
    void generar_descendientes(Poblacion* Q, int lambda, int p_aceptacion, int p_cruce, int p_mutacion) ;
    
    //--------------- union de la poblacion de padres he hijos ---------------
    void combinar_poblacion(Poblacion* P, Poblacion* Q)                               ;
    
    //--------------- detectar solucion dominada ---------------
    int dominancia(Individuo* p, Individuo* q)                                        ;

    //--------------- clasificacion no dominada de las soluciones ---------------
    void clasificar_poblacion(Frentes* F, int lambda)                                 ;
    void obtener_frente_pareto(Frentes* F, int lambda)                                            ;

    //--------------- pasar nuevos padres del frente a la poblacion ---------------
    void agregar_nuevos_padres(Frentes* F, int lambda)                                ;




    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::::::::::::::::::::::::::::::::::: PARA RERUTEO ::::::::::::::::::::::::::::::::::::::
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    
    //--------------- generacion de los hijos ---------------
    void generar_descendientes_2(Poblacion* Q, int lambda, int p_aceptacion, int p_cruce, int p_mutacion) ;
    
    //--------------- seleccion de padre para cruce ---------------
    Individuo* torneo_binario_3(int aceptacion)             ;
    Individuo* torneo_binario_4(Individuo* p, Individuo* q) ;

    //--------------- clasificacion no dominada de las soluciones ---------------
    void ordenar_poblacion(void) ;
    void clasificar_poblacion_2(Poblacion* Q, int lambda) ;

};