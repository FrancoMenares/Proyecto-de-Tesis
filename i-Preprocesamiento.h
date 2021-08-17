
#pragma once
#include <iostream>
#include <time.h>

#include "b-Red.h"
#include "e-Instancia.h"
#include "g-Costos.h"
#include "h-TDDijkstra.h"

using namespace std;


class Preprocesamiento{
  private:
    float tiempo_ejecucion ; //tiempo de ejecucion

  public:
    Preprocesamiento(){}   ; //Constructor    
    ~Preprocesamiento(){}  ; //Destructor

    //--------------- preprocesamiento ---------------
    void preprocesar_red(Red* red, Instancia* instancia, float frecuencia) ;

    //--------------- impresiones ---------------
    void imprimir_tiempo_ejecucion(void);
};
