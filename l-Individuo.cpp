
#include "l-Individuo.h"


Individuo::Individuo(){ 
  this->f1 = 0.0         ;
  this->f2 = 0.0         ;
  this->dominado_por = 0 ;
}

Individuo::Individuo(const Individuo &i){
  for (Ruta* r: i.rutas){
    Ruta* j = new Ruta(*r)   ;
    this->rutas.push_back(j) ;
  }
  this->f1 = i.f1            ;
  this->f2 = i.f2            ;  

  this->dominado_por = i.dominado_por ;
  for (Individuo* j: i.domina_a){
    this->domina_a.push_back(j)       ;
  }
  this->ranking = i.ranking           ;
  this->dist_h = i.dist_h             ;
}

Individuo::~Individuo(){
  this->domina_a.clear()         ;
  this->domina_a.shrink_to_fit() ;

  for (Ruta *r: this->rutas) {
    delete r                     ;
  }
  this->rutas.clear()            ;
  this->rutas.shrink_to_fit()    ;
}


//------------- rutas -------------
void Individuo::agregar_ruta(Ruta* ruta)   { this->rutas.push_back(ruta) ;}
void Individuo::reemplazar_ruta(int pos, Ruta* ruta) {
  delete rutas.at(pos)                                                   ; 
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
  this->f1 = 0                                                           ;
  this->f2 = 0                                                           ;
  for (Ruta* i: this->rutas){
    this->f1 = this->f1 + i->get_aporte_f1()                             ;
    this->f2 = this->f2 + i->get_aporte_f2()                             ;
  }
}


//------------- dominado -------------
void Individuo::set_dominado_por(int cant)   { this->dominado_por = cant ;}
int Individuo::get_dominado_por(void)        { return this->dominado_por ;}


//------------- dominado -------------
void Individuo::agregar_individuo_dominado(Individuo* individuo) {this->domina_a.push_back(individuo) ;}
Individuo* Individuo::get_individuo_dominado(int pos)            {return this->domina_a.at(pos)       ;}
vector <Individuo*> Individuo::get_individuos_dominados(void)    {return this->domina_a               ;}
void Individuo::Individuo::eliminar_individuos_dominados(void){
  this->domina_a.clear()         ;
  this->domina_a.shrink_to_fit() ;
}


//------------- dominado_por -------------
void Individuo::set_ranking(int ranking) { this->ranking = ranking ;}
int Individuo::get_ranking(void)         { return this->ranking    ;}


//------------- dominado_por -------------
void Individuo::set_hacinamiento(float dist) { this->dist_h = dist ;}
float Individuo::get_hacinamiento(void)      { return this->dist_h ;}


//------------- imprimir individuo -------------
void Individuo::imprimir_individuo(void){
  cout << "=================================================================" << endl ;
  cout << "F1 :\t" << this->f1 << endl ;
  cout << "F2 :\t" << this->f2 << endl ;
  cout << endl                         ;

  for (Ruta* i: this->rutas){
    i->imprimir_ruta()                 ;
    cout << endl                       ;
  } 
  cout << "-----------------------------------------------------------------" << endl ;
  cout << endl                         ;
}


//------------- imprimir individuo -------------
void Individuo::imprimir_individuo_2(Instancia* instancia){
  cout << "=================================================================" << endl ;
  cout << "F1 :\t" << this->f1 << endl ;
  cout << "F2 :\t" << this->f2 << endl ;
  cout << endl                         ;

  for (Ruta* i: this->rutas){
    i->imprimir_ruta_2(instancia)      ;
    cout << endl                       ;
  } 
  cout << "-----------------------------------------------------------------" << endl ;
  cout << endl                         ;
}


















