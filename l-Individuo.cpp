
#include "l-Individuo.h"


Individuo::Individuo(int id)               { this->id = id               ;}

//------------- id -------------
void Individuo::set_id(int id)             { this->id = id               ;}
int Individuo::get_id(void)                { return this->id             ;}

//------------- rutas -------------
void Individuo::agregar_ruta(Ruta* ruta)   { this->rutas.push_back(ruta) ;}
void Individuo::reemplazar_ruta(int pos, Ruta* ruta) {
  for (Segmento* i: this->rutas.at(pos)->get_segmentos()){
    delete i                                                             ;
  }
  this->rutas.at(pos)->get_segmentos().clear()                           ;
  this->rutas.at(pos)->get_segmentos().shrink_to_fit()                   ;
  delete rutas.at(pos); 
  rutas.at(pos) = ruta                                                   ;
}
void Individuo::eliminar_ruta(int pos)     { this->rutas.erase(this->rutas.begin()+pos) ;}
Ruta* Individuo::get_ruta(int pos)         { return this->rutas.at(pos)  ;}
vector <Ruta*> Individuo::get_rutas(void)  { return this->rutas          ;}

//------------- f1 / f2 -------------
void Individuo::set_f1(float f1)           { this->f1 = f1               ;}
float Individuo::get_f1(void)              { return this->f1             ;}

void Individuo::set_f2(float f2)           { this->f2 = f2               ;}
float Individuo::get_f2(void)              { return this->f2             ;}

void Individuo::actualizar_funciones(void){
  this->f1 = 0 ;
  this->f2 = 0 ;
  for (Ruta* i: this->rutas){
    this->f1 = (int)this->f1 + i->get_aporte_f1()*100;
    this->f2 = (int)this->f2 + i->get_aporte_f2()*100;
  }
  this->f1 = (float)this->f1/100 ;
  this->f2 = (float)this->f2/100 ;
}

//------------- imprimir individuo -------------
void Individuo::imprimir_individuo(void){
  cout << "================================================================================" << endl ;
  cout << "Id :\t" << this->id << endl ;  
  cout << "F1 :\t" << this->f1 << endl ;
  cout << "F2 :\t" << this->f2 << endl ;
  //cout << "================================================================================" << endl ;
  cout << endl                         ;

  for (Ruta* i: this->rutas){
    i->imprimir_ruta()                 ;
    cout << endl                       ;
  } 
  cout << "--------------------------------------------------------------------------------" << endl ;
  cout << endl                         ;
}

//------------- imprimir individuo -------------
void Individuo::imprimir_individuo_2(void){
  cout << "================================================================================" << endl ;
  cout << "Id :\t" << this->id << endl ;  
  cout << "F1 :\t" << this->f1 << endl ;
  cout << "F2 :\t" << this->f2 << endl ;
  //cout << "================================================================================" << endl ;
  cout << endl                         ;
}



















