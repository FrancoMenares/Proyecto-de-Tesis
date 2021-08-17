
#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "e-Instancia.h"

using namespace std;


class LecturaInstancia{
  private:
    string nombre_instancia; //nombre instancia
	  fstream fs;              //para leer instancia
	  string cadena;           //para leer cosas de instancia

  public:
    LecturaInstancia(string nombre_instancia): nombre_instancia(nombre_instancia) {}  //Constructor
    ~LecturaInstancia() {}                                                            //Destructor
    
    Instancia *lectura_instancia();                                                   //Función que lee 
};