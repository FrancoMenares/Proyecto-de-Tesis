
#include <iostream>
#include <fstream>
#include <string>

#include "e-Instancia.h"

using namespace std;


class EscrituraInstancia{
  private:
    string nombre_instancia ; //

  public:
    EscrituraInstancia(string nombre_instancia): nombre_instancia(nombre_instancia){} //Constructor
    ~EscrituraInstancia(){}                                                           //Destructor
    
    void escribir_instancia(Instancia* instancia) ;
};