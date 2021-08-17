
#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <random>

#include "e-Instancia.h"
#include "l-Individuo.h"

using namespace std;


class AjusteHora{
  private:
  
  public:
    AjusteHora(){}       ; //Constructor
    ~AjusteHora(){}      ; //Destructor
    
    //--------------- cambia la hora de inicio de una ruta ---------------
    void ajustar_hora_ruta(Individuo* individuo, Instancia* instancia)                ; 

    //--------------- recalcula parametros de la ruta ---------------
    bool evaluar_ruta(Instancia* instancia, Ruta* ruta, float hora_inicio) ;
};