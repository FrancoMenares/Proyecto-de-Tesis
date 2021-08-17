
#pragma once
#include <iostream>
#include <vector>

#include "e-Instancia.h"
#include "l-Individuo.h"
#include "m-Construccion.h"

using namespace std;


class Poblacion{
  private:
    Instancia* instancia          ; //instancia del problema
    vector <Individuo*> poblacion ; //vector de soluciones
  
  public:
    Poblacion(Instancia* instancia) ; //Constructor
    ~Poblacion(){}                  ; //Destructor

    //--------------- Poblacion ---------------
    vector <Individuo*> get_poblacion(void)      ;
    Individuo* get_individuo(int pos)            ;
    
    //--------------- contruccion de la poblacion inicial ---------------
    void construir_poblacion_inicial(int lambda) ;
    
    //--------------- imprimir poblacion ---------------
    void imprimir_poblacion(void)                ;
};