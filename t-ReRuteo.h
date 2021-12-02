
#pragma once
#include <iostream>
#include <vector>

#include "e-Instancia.h"
#include "l-Individuo.h"


using namespace std;


class ReRuteo{
  private: 
  
  public:
    ReRuteo(){}  ; //Constructor
    ~ReRuteo(){} ; //Destructor

    Instancia* crear_instancia_de_reruteo(Individuo* individuo, Instancia* instancia) ;
};