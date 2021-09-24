
#include "s-Frentes.h"



void Frentes::crear_frente(void)                               {this->frentes.push_back({})                 ;}
void Frentes::agregar_individuo(int pos, Individuo* individuo) { this->frentes.at(pos).push_back(individuo) ;}

void Frentes::eliminar_individuo(int pos1, int pos2){
  this->frentes.at(pos1).erase(this->frentes.at(pos1).begin() + pos2) ;
}

Individuo* Frentes::get_individuo(int pos1, int pos2)          { return this->frentes.at(pos1).at(pos2)     ;}
vector <Individuo*> Frentes::get_frente(int pos)               { return this->frentes.at(pos)               ;}
vector <vector <Individuo*>> Frentes::get_frentes(void)        { return this->frentes                       ;}

void Frentes::eliminar_frente_1(int pos){
  this->frentes.at(pos).clear()           ;
  this->frentes.at(pos).shrink_to_fit()   ;
}

void Frentes::eliminar_frente_2(int pos){
  for (Individuo* i: this->frentes.at(pos)){
    delete i                                 ; //
  }
  this->eliminar_frente_1(pos)               ; //

  this->frentes.clear()                      ; //
  this->frentes.shrink_to_fit()              ; //
}


void Frentes::imprimir_frente_1(int pos){
  int j = 0 ; 
  for (Individuo* i: this->frentes.at(pos)){
    cout << j << " ::: " ; 

    cout << i->get_f1() << " - " << i->get_f2() << "\t::: " << i->get_ranking() << ", " << i->get_hacinamiento() << endl ;

    j++ ; 
  }
}

void Frentes::imprimir_frente_2(int pos){
  for (Individuo* i: this->frentes.at(pos)){
    if (i->get_hacinamiento() != 0){
      cout << i->get_f1() << "\t" << i->get_f2() << endl ;
      //i->imprimir_individuo() ;
      //getchar() ;
    }
  }
}


void Frentes::imprimir_frentes_1(void){
  for (int i=0; i<this->frentes.size(); i++){
    cout << "------ Frente : " << i+1 << " ------" << endl ;
    this->imprimir_frente_1(i)                               ;
    cout << endl                                           ;
  }
}

void Frentes::imprimir_frentes_2(void){
  for (int i=0; i<this->frentes.size(); i++){
    cout << "------ Frente : " << i+1 << " ------" << endl ;
    this->imprimir_frente_2(i)                               ;
    cout << endl                                           ;
  }
}


//--------------- calculo de la distancia de hacinamiento ---------------
void Frentes::calcular_distancia_hacinamiento(int frente){
  float distancia ; //distancia de hacinamiento del objetivo
  float f_max     ; //maximo valor del objetivo
  float f_min     ; //minimo valor del objetivo

  float inf = numeric_limits<float>::infinity() ; //numero infinito

  //----------------------------- f1 -----------------------------
  sort(this->frentes.at(frente).begin(), this->frentes.at(frente).end(), [] (Individuo* &i1, Individuo* &i2){ 
    return i1->get_f1() < i2->get_f1() ; //ordenamiento de f1 de menor a mayor
  });

  this->frentes.at(frente).at(0)->set_ranking(frente)   ; //se setea el frente para primer individuo
  this->frentes.at(frente).at(0)->set_hacinamiento(inf) ; //tambien se setea el hacinamiento
  f_min = this->frentes.at(frente).at(0)->get_f1()      ; //este tienen el minimo valor de f1

  this->frentes.at(frente).at(this->frentes.at(frente).size()-1)->set_ranking(frente)   ; //se setea el frente para ultimo individuo
  this->frentes.at(frente).at(this->frentes.at(frente).size()-1)->set_hacinamiento(inf) ; //tambien se setea el hacinamiento
  f_max = this->frentes.at(frente).at(this->frentes.at(frente).size()-1)->get_f1()      ; //este tienen el maximo valor de f1

  if (this->frentes.at(frente).size() > 2){                         //si exiten individuos intermedio
    for (int i=1; i<this->frentes.at(frente).size()-1; i++){        //se recorren los individuos intermedios
      this->frentes.at(frente).at(i)->set_ranking(frente)         ; //se setea el frente del individuo
      //se calcula la distancia de hacinamiento del objetivo
      distancia = (this->frentes.at(frente).at(i+1)->get_f1()-this->frentes.at(frente).at(i-1)->get_f1()) / (f_max-f_min) ;
      this->frentes.at(frente).at(i)->set_hacinamiento(distancia) ; //se setea la distancia de hacinamiento
    }
  }

  //----------------------------- f2 -----------------------------
  sort(this->frentes.at(frente).begin(), this->frentes.at(frente).end(), [] (Individuo* &i1, Individuo* &i2){ 
    return i1->get_f2() < i2->get_f2() ;
  });

  this->frentes.at(frente).at(0)->set_hacinamiento(inf) ; //se setea hacinamiento para primer individuo
  f_min = this->frentes.at(frente).at(0)->get_f2()      ; //este tienen el minimo valor de f2
  
  this->frentes.at(frente).at(this->frentes.at(frente).size()-1)->set_hacinamiento(inf) ; //setea hacinamiento para ultimo individuo
  f_max = this->frentes.at(frente).at(this->frentes.at(frente).size()-1)->get_f2()      ; //este tienen el maximo valor de f2

  if (this->frentes.at(frente).size() > 2){                    //si exiten individuos intermedio
    for (int i=1; i<this->frentes.at(frente).size()-1; i++){   //se recorren los individuos intermedios
      this->frentes.at(frente).at(i)->set_ranking(frente)    ; //se setea el frente del individuo
      //se calcula la distancia de hacinamiento del objetivo
      distancia = (this->frentes.at(frente).at(i+1)->get_f2()-this->frentes.at(frente).at(i-1)->get_f2()) / (f_max-f_min) ;
      //se setea la distancia de hacinamiento
      this->frentes.at(frente).at(i)->set_hacinamiento(this->frentes.at(frente).at(i)->get_hacinamiento() + distancia)    ;
    }
  }
}


//--------------- ordenar individuos de un frente ---------------
void Frentes::ordenar_frente(int frente){
  sort(this->frentes.at(frente).begin(), this->frentes.at(frente).end(), [] (Individuo* &i1, Individuo* &i2){   //
    if (i1->get_ranking() < i2->get_ranking()){                                                                 //
      return i1->get_ranking() < i2->get_ranking()                                                            ; //   
    }
    if (i1->get_ranking() == i2->get_ranking() && i1->get_hacinamiento() > i2->get_hacinamiento()){             //
      return i1->get_hacinamiento() > i2->get_hacinamiento()                                                  ; //
    }
    return i2->get_ranking() < i1->get_ranking()                                                              ; //
  });
}


void Frentes::escribir_frente_final(string nombre_archivo){
  ofstream archivo                                         ; //
  archivo.open(nombre_archivo)                             ; // 
  for (vector <Individuo*> i: this->frentes){                // 
    for (Individuo* j: i){                                   // 
      archivo << j->get_f1() << " " << j->get_f2() << endl ; //
    }
  }
  archivo.close()                                          ; //
}








