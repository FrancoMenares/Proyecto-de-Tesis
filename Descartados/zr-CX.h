
#pragma once
#include <iostream>
#include <vector>
#include <random>

#include "e-Instancia.h"
#include "l-Individuo.h"

using namespace std;


class CX{
  private:
  
  public:
    CX(){}  ; //Constructor
    ~CX(){} ; //Destructor
    
    //--------------- cruza dos padres generando dos hijos ---------------
    void cruzar_individuos(Individuo* individuo1, Individuo* individuo2, Instancia* instancia)        ; 

    //--------------- extrae la secuencia de las rutas de un individuo ---------------
    vector <int> extraer_secuencia(Individuo* individuo)                                              ;

    //--------------- crear dos hijos siameses a partir de dos padres ---------------
    vector <int> crear_hijo(vector <int> padre1, vector <int> padre2) ;   


    

    //--------------- se genera el hijo como un individuo ---------------
    //Individuo* generar_individuo(Individuo* individuo, vector <int> hijo, Instancia* instancia)       ;
};