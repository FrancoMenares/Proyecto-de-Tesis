
#include "n-Poblacion.h"


Poblacion::Poblacion(Instancia* instancia){
  this->instancia = instancia ;
}

//--------------- Poblacion ---------------
vector <Individuo*> Poblacion::get_poblacion(void) { return this->poblacion         ;}
Individuo* Poblacion::get_individuo(int pos)       { return this->poblacion.at(pos) ;}

//--------------- contruccion de la poblacion inicial ---------------
void Poblacion::construir_poblacion_inicial(int lambda){
  Individuo* aux                                         ;
  Construccion* construir = new Construccion()           ;
  for (int i=0; i<lambda; i++){
    aux = new Individuo(i)                               ;
    construir->individuo_aleatorio(this->instancia, aux) ;
    this->poblacion.push_back(aux);
  }
  delete construir                                       ;
}

//--------------- imprimir poblacion ---------------
void Poblacion::imprimir_poblacion(void){
  for (Individuo* i: this->poblacion){
    i->imprimir_individuo() ;
  }
}



