
#include <iostream>
#include <fstream>
#include <string>

#include "n-Poblacion.h"

using namespace std;


class EscrituraFrente{
  private:
    Poblacion* poblacion; //

  public:
    EscrituraFrente(Poblacion* poblacion): poblacion(poblacion){} //Constructor
    ~EscrituraFrente(){}    //Destructor
    
    void escribir_frente(void) ;
};
