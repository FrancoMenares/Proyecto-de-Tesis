
#pragma once
#include <iostream>
#include <vector>
#include <random>

#include "e-Instancia.h"
#include "l-Individuo.h"

using namespace std;


class InvertirClientes{
  private:
  
  public:
    InvertirClientes(){}       ; //Constructor
    ~InvertirClientes(){}      ; //Destructor
    
    //--------------- invertir los clientes de un segmento ---------------
    void invertir_clientes_segmento(Individuo* individuo, Instancia* instancia) ; 

    //--------------- actualizacion de la ruta ---------------
    bool actualizar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde) ;

    //--------------- evaluacion de la ruta ---------------
    bool evaluar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde) ;
};