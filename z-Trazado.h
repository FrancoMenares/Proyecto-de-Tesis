
#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#include "b-Red.h"
#include "e-Instancia.h"
#include "g-Costos.h"
#include "h-TDDijkstra.h"
#include "l-Individuo.h"
#include "s-Frentes.h"


class Trazado{
  private:
  
  public:
    Trazado(){}       ; //Constructor
    ~Trazado(){}      ; //Destructor

    //--------------- ruta mas corta dependiente del tiempo ---------------
    void escibir_rutas_completas(string nombre_instancia, string parametros, Frentes* F, Red* red, Instancia* instancia) ;
};












