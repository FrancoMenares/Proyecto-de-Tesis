
#include "4-Cliente.h"


//--------------- id_cliente ---------------
void Cliente::set_id_cliente(int id_cliente)          { this->id_cliente = id_cliente     ;}
int Cliente::get_id_cliente(void)                     { return this->id_cliente           ;}

//--------------- id_nodo ---------------
void Cliente::set_id_nodo(int id_nodo)                { this->id_nodo = id_nodo           ;}
int Cliente::get_id_nodo(void)                        { return this->id_nodo              ;}

//------------ costo_hasta ------------
void Cliente::set_tam_costo_hasta(int fils, int cols) {
  this->costo_hasta = new float*[fils]                                                    ;
  for (int i=0; i<fils; i++){
    this->costo_hasta[i] = new float[cols]                                                ;
  }
}
void Cliente::set_costo_hasta(int i, int p, float val) { this->costo_hasta[i][p] = val    ;}
float Cliente::get_costo_hasta(int i, int p)           { return this->costo_hasta[i][p]   ;}

//------------ tiempo_hasta ------------
void Cliente::set_tam_tiempo_hasta(int fils, int cols) {
  this->tiempo_hasta = new float*[fils]                                                   ;
  for (int i=0; i<fils; i++){
    this->tiempo_hasta[i] = new float[cols]                                               ;
  }
}
void Cliente::set_tiempo_hasta(int i, int p, float val) { this->tiempo_hasta[i][p] = val  ;}
float Cliente::get_tiempo_hasta(int i, int p)           { return this->tiempo_hasta[i][p] ;}

//---------- impresiones -----------
void Cliente::imprimir_cliente(void){
  cout << "Cliente     : \t" << this->id_cliente << endl ;
  cout << "Nodo        : \t" << this->id_nodo    << endl ;
  cout << endl                                           ;
}