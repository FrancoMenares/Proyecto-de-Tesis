
#include "z-EscrituraFrente.h"
#include <sstream>

std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}


void EscrituraFrente::escribir_frente(void){
  ofstream archivo                                       ;
  archivo.open("Resultados/FrentePareto.txt")            ;
  archivo << "#" << endl                                 ;
  for (Individuo* i: this->poblacion->get_poblacion()){
    archivo << i->get_f1() << " " << Convert(i->get_f2()) << endl ;
  }
  archivo << "#" << endl                                 ;
  archivo.close()                                        ;
}