
#include "b-Red.h"



//--------------- cant_nodos ---------------
void Red::set_cant_nodos(int cant_nodos)          { this->cant_nodos = cant_nodos           ;}
int Red::get_cant_nodos(void)                     { return this->cant_nodos                 ;}


//--------------- cant_arcos ---------------
void Red::set_cant_arcos(int cant_arcos)          { this->cant_arcos = cant_arcos           ;}
int Red::get_cant_arcos(void)                     { return this->cant_arcos                 ;}


//-------------- cant_periodos -------------
void Red::set_cant_periodos(int cant_periodos)    { this->cant_periodos = cant_periodos     ;}
int Red::get_cant_periodos(void)                  { return this->cant_periodos              ;}


//--------- Matriz Adyacencia ---------
void Red::agregar_fils(int fils)                  { this->matriz_ady = new float*[fils]     ;}
void Red::agregar_cols(int fil, int cols)         { this->matriz_ady[fil] = new float[cols] ;}
void Red::set_matriz_ady(int i, int j, float val) { this->matriz_ady[i][j] = val            ;}
float Red::get_matriz_ady(int i, int j)           { return this->matriz_ady[i][j]           ;}


//--------------- Nodos ---------------
void Red::agregar_nodo(Nodo* nodo)                { this->Nodos.push_back(nodo)             ;}
Nodo* Red::get_nodo(int pos)                      { return this->Nodos.at(pos)              ;}
vector <Nodo*> Red::get_nodos(void)               { return this->Nodos                      ;}
void Red::reiniciar_nodos(void)                   {
  for (Nodo *aux: this->Nodos){
    aux->set_costo(0)                                                                       ;
    aux->set_tiempo(0)                                                                      ;
    aux->set_padre(0)                                                                       ;
  }
}


//------------ Tasas_fallo ------------
void Red::set_tam_tasas_fallo(int fils, int cols) {
  this->tasas_fallo = new float*[fils]                                                      ;
  for (int i=0; i<fils; i++){
    this->tasas_fallo[i] = new float[cols]                                                  ;
  }
}
void Red::set_tasa_fallo(int i, int p, float val) { this->tasas_fallo[i][p] = val           ;}
float Red::get_tasa_fallo(int i, int p)           { return this->tasas_fallo[i][p]          ;}


//------------ limites_periodo ------------
void Red::set_tam_periodos(int cant_periodos)     {
  this->limites_periodo = new float*[2]                                                     ;
  this->limites_periodo[1] = new float[cant_periodos]                                       ;
  this->limites_periodo[2] = new float[cant_periodos]                                       ;
}
void Red::set_periodo(int p, int t, float val)    { this->limites_periodo[t][p] = val       ;}
float Red::get_ini_periodo(int p)                 { return this->limites_periodo[1][p]      ;}
float Red::get_fin_periodo(int p)                 { return this->limites_periodo[2][p]      ;}


//------------ Tiempos_atencion ------------
void Red::set_tam_tiempos_aten(int fils, int cols) {
  this->tiempo_atencion = new float*[fils]                                                  ;
  for (int i=0; i<fils; i++){
    this->tiempo_atencion[i] = new float[cols]                                              ;
  }
}
void Red::set_tiempo_aten(int i, int p, float val) { this->tiempo_atencion[i][p] = val      ;}
float Red::get_tiempo_aten(int i, int p)           { return this->tiempo_atencion[i][p]     ;}


//------------ Imprimir info red -----------
void Red::imprimir_red(void){
  cout << endl                                                                              ;
  cout << "-----------------------------------------------------------------" << endl       ;
  cout << "N° Nodos    : \t" << this->cant_nodos    << endl                                 ;
  cout << "N° Arcos    : \t" << this->cant_arcos    << endl                                 ;
  cout << "N° Periodos : \t" << this->cant_periodos << endl                                 ;
  cout << "-----------------------------------------------------------------" << endl       ;
  cout << endl                                                                              ;
}


//------------ Imprimir info matriz de adyacencia de un nodo -----------
void Red::imprimir_ady_nodo(int id){
  for (int j=0; j<(2+this->get_matriz_ady(id, 1)*(this->get_cant_periodos()+2)); j++){
    cout << this->get_matriz_ady(id, j) << " "                                              ;
  }
  cout << endl << endl                                                                      ;
}


//------------ imprimir tasas de fallo de un nodo ------------
void Red::imprimir_tasas_nodo(int id){
  for (int j=0; j<this->get_cant_periodos(); j++){
    cout << this->get_tasa_fallo(id, j) << " "                                              ; 
  }
  cout << endl << endl                                                                      ;
}


//------------ imprimir limites de cada periodo de tiempo ------------
void Red::imprimir_limites_periodos(void){
  for (int i=0; i<this->get_cant_periodos(); i++){
    cout << i+1 << "\t" << this->get_ini_periodo(i) << "\t"  << this->get_fin_periodo(i) << endl  ;
  }
}


//------------ imprimir tiempos de atencion de un nodo ------------
void Red::imprimir_tiempos_nodo(int id){
  for (int j=0; j<this->get_cant_periodos(); j++){
    cout << this->get_tiempo_aten(id, j) << " "                                              ; 
  }
  cout << endl << endl                                                                       ;
}


