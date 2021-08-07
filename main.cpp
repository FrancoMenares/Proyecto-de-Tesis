
#include <iostream>
#include <random>
#include <vector>
#include <time.h>

#include "2-Red.h"
#include "3-LecturaRed.h"

using namespace std;


int main(int argc, char **argv){
  
  //Lectura Red de carreteras
  LecturaRed lr(argv[1])              ; //se crea un objeto de depo LecturaRed
  Red* carreteras = lr.lectura_red()  ; //se lee la red de carreteras
  
  
  
  

}













