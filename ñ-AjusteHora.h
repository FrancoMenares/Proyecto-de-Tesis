
#pragma once
#include <iostream>
#include <vector>
#include <random>

#include "e-Instancia.h"
#include "l-Individuo.h"

using namespace std;


class AjusteHora{
  private:
  
  public:
    AjusteHora(){}       ; //Constructor
    ~AjusteHora(){}      ; //Destructor
    

    //--------------- evalua si el ajuste de hora es factible ---------------
    void ajustar_hora_ruta(Individuo* individuo, Instancia* instancia)     ; 
    
    //--------------- ajusta la ruta a la hora de salida ---------------
    bool evaluar_ruta(Instancia* instancia, Ruta* ruta, float hora_inicio) ;

    //--------------- ajusta la hora de salida de una ruta ---------------
    void ajustar_ruta(Instancia* instancia, Ruta* ruta, float hora_inicio) ;
};

