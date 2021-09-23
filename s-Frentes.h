
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#include "l-Individuo.h"


using namespace std;


class Frentes{
  private:
    vector <vector <Individuo*>> frentes ; 
  
  public:
    Frentes(){}  ; //Constructor
    ~Frentes(){} ; //Destructor


    void crear_frente(void)                               ;

    void agregar_individuo(int pos, Individuo* individuo) ;
    void eliminar_individuo(int pos1, int pos2)           ;
    
    vector <vector <Individuo*>> get_frentes(void)        ;
    vector <Individuo*> get_frente(int pos)               ;
    Individuo* get_individuo(int pos1, int pos2)          ;

    void eliminar_frente_1(int pos)                       ;
    void eliminar_frente_2(int pos)                       ;

    void imprimir_frente_1(int pos)                       ;
    void imprimir_frente_2(int pos)                       ;

    void imprimir_frentes_1(void)                         ;
    void imprimir_frentes_2(void)                         ;

    //--------------- calculo de la distancia de hacinamiento ---------------
    void calcular_distancia_hacinamiento(int frente)      ;

    //--------------- ordenar individuos de un frente ---------------
    void ordenar_frente(int frente)                       ;
};