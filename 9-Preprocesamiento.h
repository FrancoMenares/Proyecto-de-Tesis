
#pragma once
#include <iostream>

#include "2-Red.h"
#include "5-Instancia.h"
#include "7-Costos.h"
#include "8-TDDijkstra.h"

using namespace std;


class Preprocesamiento{
  private:

  public:
    Preprocesamiento(){}  ; //Constructor    
    ~Preprocesamiento(){} ; //Destructor

    //--------------- preprocesamiento ---------------
    void preprocesar_red(Red* red, Instancia* instancia, float frecuencia) ;
};
