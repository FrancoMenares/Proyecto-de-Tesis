
#pragma once
#include <iostream>
#include <vector>
#include <random>

#include "e-Instancia.h"
#include "l-Individuo.h"

using namespace std;


class CambioCliente{
  private:
  
  public:
    CambioCliente(){}       ; //Constructor
    ~CambioCliente(){}      ; //Destructor

    //--------------- cambio nodo aleatorio ---------------
    void cambiar_cliente_aleatorio(Individuo* individuo, Instancia* instancia) ; 

    //--------------- actualizacion de la ruta ---------------
    bool actualizar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde) ;

    //--------------- evaluacion de la ruta ---------------
    bool evaluar_ruta_desde(Instancia* instancia, Ruta* ruta, int desde) ;

    //---------------crearcion de una nueva ruta ---------------
    Ruta* crear_nueva_ruta(Instancia* instancia, Segmento* aux1, Segmento* aux2, int id) ;
};


