
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "2-Red.h"

using namespace std;


class LecturaRed{
  private:
    string nombre_red   ; //nombre red
	  fstream fs          ; //para leer red
	  string cadena       ; //para leer cosas de red

  public:
    LecturaRed(string nombre_red): nombre_red(nombre_red){}  //Constructor
    ~LecturaRed(){}                                          //Destructor
    
    Red *lectura_red(void);                                  //Función para leer 
};