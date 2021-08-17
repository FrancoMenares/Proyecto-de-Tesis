
#pragma once
#include <iostream>
#include <vector>

using namespace std;

#include "b-Red.h"
#include "e-Instancia.h"
#include "g-Costos.h"
#include "h-TDDijkstra.h"
#include "l-Individuo.h"


class Trazado{
  private:
  
  public:
    Trazado(){}       ; //Constructor
    ~Trazado(){}      ; //Destructor
    
    //--------------- impresiones ---------------
    void imprimir_ruta(Individuo* individuo, Red* red, Instancia* instancia) ;
};












