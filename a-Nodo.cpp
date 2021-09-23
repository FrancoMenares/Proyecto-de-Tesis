

#include "a-Nodo.h"


//------------- id -------------
void  Nodo::set_id(int id)            { this->id = id         ;}
int   Nodo::get_id(void)              { return this->id       ;} 


//------------- costo -------------
void  Nodo::set_costo(float costo)    { this->costo = costo   ;}
float Nodo::get_costo(void)           { return this->costo    ;} 


//------------- tiempo -------------
void  Nodo::set_tiempo(float tiempo)  { this->tiempo = tiempo ;}
float Nodo::get_tiempo(void)          { return this->tiempo   ;} 


//------------- padre -------------
void  Nodo::set_padre(Nodo* padre)    { this->padre = padre   ;}
Nodo* Nodo::get_padre(void)           { return this->padre    ;} 


//------------- imprimir -------------
void Nodo::imprimir_nodo(void){
  cout << "Id          : \t" << this->id+1   << endl          ;
  cout << "Costo       : \t" << this->costo  << endl          ;
  cout << "Tiempo      : \t" << this->tiempo << endl          ;
  cout << "Padre       : \t" << this->padre  << endl          ;
  cout << endl                                                ;
}

