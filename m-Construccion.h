
#pragma once
#include <iostream>
#include <random>
#include <queue>

#include "e-Instancia.h"
#include "j-Segmento.h"
#include "k-Ruta.h"
#include "l-Individuo.h"

using namespace std;


class Construccion{
  private:

  public:
    Construccion(){}  ; //Constructor    
    ~Construccion(){} ; //Destructor

    //--------------- ordenar clientes aleatoriamente ---------------
    vector <int> ordenar_clientes(int cant_clientes)                     ;

    //--------------- impresiones ---------------
    void imprimir_secuencia(vector <int> secuencia)            ;

    //--------------- construir ruta aleatoria ---------------
    vector <int> ruta_aleatoria(Instancia* instancia, Ruta* ruta, float inicio_hasta, vector <int> secuencia) ;

    //--------------- devolver clientes a la secuencia ---------------
    vector <int> devolver_clientes_a_secuencia(Ruta* ruta, vector <int> secuencia) ;

    //--------------- construir individuo aleatorio ---------------
    void individuo_aleatorio(Instancia* instancia, Individuo* individuo) ;
};