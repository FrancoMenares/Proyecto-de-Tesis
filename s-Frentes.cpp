
#include "s-Frentes.h"



void Frentes::crear_frente(void)                               {this->frentes.push_back({})                 ;}
void Frentes::agregar_frente(vector <Individuo*> frente)       {this->frentes.push_back(frente)             ;}

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
  int j = 1 ; 
  for (Individuo* i: this->frentes.at(pos)){
    cout << j << " ::: " ; 

    cout << i->get_f1() << " - " << i->get_f2() << "\t::: " << i->get_ranking() << ", " << i->get_hacinamiento() << endl ;

    j++ ; 
  }
}

void Frentes::imprimir_frente_2(int pos){
  int j = 1 ;
  cout << "N° \t   F1 \t F2" << endl ;
  for (Individuo* i: this->frentes.at(pos)){
    //if (i->get_hacinamiento() != 0){
    cout << j << "\t" << i->get_f1() << "\t" << i->get_f2() << endl ;
    //}
    j++ ;
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

void Frentes::imprimir_frentes_3(void){
  vector <Individuo*> j ;
  for (int i=0; i<this->frentes.size(); i++){
    cout << i << "\t"                                                                         ;
    cout << this->get_individuo(i, 0)->get_f1() << "\t"                                       ;
    cout << this->get_individuo(i, 0)->get_f1() + this->get_individuo(i, 1)->get_f1() << "\t" ;
    cout << this->get_individuo(i, 0)->get_f2() << endl                                       ;

    //cout << i+1 << "\t" << this->get_frente(0).size() << endl ;
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


void Frentes::clasificar_frente_final(int lambda){

  for (Individuo* i: this->frentes.at(0)){
    i->set_f1(int(i->get_f1()*100)) ;
    i->set_f2(int(i->get_f2()*100)) ;
  }

  for (int i=0; i<this->frentes.at(0).size(); i++){
    Individuo* p = this->frentes.at(0).at(i) ;

    if (p->get_ranking() == 0){
      for (int j=i+1; j<this->frentes.at(0).size(); j++){
        Individuo* q = this->frentes.at(0).at(j) ;

        if ((p->get_f1() == q->get_f1()) && (p->get_f2() == q->get_f2())){
          q->set_ranking(1) ;
          continue          ;
        }

        if ((p->get_f1() == q->get_f1()) && (p->get_f2() < q->get_f2())){
          q->set_ranking(1) ;
          continue          ;
        } else if ((p->get_f1() == q->get_f1()) && (p->get_f2() > q->get_f2())){
          p->set_ranking(1) ;
          break             ;
        }

        if ((p->get_f1() < q->get_f1()) && (p->get_f2() == q->get_f2())){
          q->set_ranking(1) ;
          continue          ;
        } else if ((p->get_f1() > q->get_f1()) && (p->get_f2() == q->get_f2())){
          p->set_ranking(1) ;
          break             ;
        }
      }
    }
  }
  
  int j = 0 ;
  while (j < this->frentes.at(0).size()){
    Individuo* i = this->frentes.at(0).at(j) ;

    i->set_f1(float(i->get_f1()/100)) ;
    i->set_f2(float(i->get_f2()/100)) ;

    if (i->get_ranking() == 0){
      j++ ;
    }
    
    if (i->get_ranking() != 0){
      this->frentes.at(0).erase(this->frentes.at(0).begin() + j) ;
      delete i ;
    }
  }

  this->calcular_distancia_hacinamiento(0) ;
  
  sort(this->frentes.at(0).begin(), this->frentes.at(0).end(), [] (Individuo* &i1, Individuo* &i2){ 
    return i1->get_hacinamiento() > i2->get_hacinamiento() ;
  });

  while (this->frentes.at(0).size() > lambda){
    Individuo* k = this->get_individuo(0, lambda) ;
    this->eliminar_individuo(0, lambda) ;
    delete k ;
  }

  sort(this->frentes.at(0).begin(), this->frentes.at(0).end(), [] (Individuo* &i1, Individuo* &i2){ 
    return i1->get_f1() < i2->get_f1() ;
  });
}


void Frentes::escribir_frente_final(string nombre_instancia, string parametros){

  ofstream archivo1                                                                         ;
  //archivo1.open(ruta + "Individuos.txt")                                                    ; 
  archivo1.open("Resultados/SolucionesAlgoritmo/" + nombre_instancia + "/" + nombre_instancia + "-" + parametros + ".txt") ; 

  for (Individuo* i: this->frentes.at(0)){
    archivo1 << "=================================================================" << endl ;

    archivo1 << "F1 : " << i->get_f1()                                              << endl ;
    archivo1 << "F2 : " << i->get_f2()                                              << endl ;

    for (Ruta* r: i->get_rutas()){
      archivo1 << endl                                                                      ;
      archivo1 << "Id            :\t" << r->get_id()                 << endl                ;
      archivo1 << "Aporte f1     :\t" << r->get_aporte_f1()          << endl                ;
      archivo1 << "Aporte f2     :\t" << r->get_aporte_f2()          << endl                ;
      archivo1 << "T. Inicio     :\t" << r->get_tiempo_inicio()      << endl                ;
      archivo1 << "T. Termino    :\t" << r->get_tiempo_termino()     << endl                ;
      archivo1 << "T. Restante   :\t" << r->get_tiempo_restante()    << endl                ;
      archivo1 << "Cap. Restante :\t" << r->get_capacidad_restante() << endl                ;
      archivo1 << "Ruta          :\t"                                                       ;    

      for (int j=0; j<r->get_segmentos().size(); j++){
        if (j == r->get_segmentos().size()-1){
          archivo1 << r->get_segmento(j)->get_cliente_i()->get_id_nodo()+1 << " - "         ;
          archivo1 << r->get_segmento(j)->get_cliente_j()->get_id_nodo()+1 << endl          ;
          break                                                                             ; 
        } else {
          archivo1 << r->get_segmento(j)->get_cliente_i()->get_id_nodo()+1 << " - "         ;
        } 
      }
    }

    archivo1 << "-----------------------------------------------------------------" << endl ;
    archivo1 << endl                                                                        ;
  }
  archivo1.close()                                                                          ;

  
  ofstream archivo2                                       ; 
  //archivo2.open(ruta + "Frente.txt")                      ; 
  archivo2.open("Resultados/FrentesAlgoritmo/" + nombre_instancia + "/" + nombre_instancia + "-" + parametros + ".txt") ; 

  for (Individuo* i: this->frentes.at(0)){
    archivo2 << i->get_f1() << " " << i->get_f2() << endl ; 
  }
  archivo2.close()                                        ; 
}




void Frentes::escribir_frente_final_re(Frentes* F, string nombre_instancia, string parametros){

  ofstream archivo1                                                                         ;
  //archivo1.open(nombre_instancia + "xxxxxx-" + parametros + ".txt")                         ; 
  archivo1.open("Resultados/SolucionesReRuteo/" + nombre_instancia + "/" + nombre_instancia + "-" + parametros + ".txt") ; 

  for (int j=0; j<F->get_frente(0).size(); j++){

    archivo1 << endl << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl ;
    archivo1 << ":::::::::::::::::::::::::::::::::::::::::::::::::::: " << j+1 << " :::::::::::::::::::::::::::::::::::::::::::::::::::" << endl ;
    archivo1 << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl << endl ;

    for (Individuo* i: this->get_frente(j)){
      archivo1 << "=================================================================" << endl ;

      archivo1 << "F1 : " << i->get_f1()                                              << endl ;
      archivo1 << "F2 : " << i->get_f2()                                              << endl ;

      for (Ruta* r: i->get_rutas()){
        archivo1 << endl                                                                      ;
        archivo1 << "Id            :\t" << r->get_id()                 << endl                ;
        archivo1 << "Aporte f1     :\t" << r->get_aporte_f1()          << endl                ;
        archivo1 << "Aporte f2     :\t" << r->get_aporte_f2()          << endl                ;
        archivo1 << "T. Inicio     :\t" << r->get_tiempo_inicio()      << endl                ;
        archivo1 << "T. Termino    :\t" << r->get_tiempo_termino()     << endl                ;
        archivo1 << "T. Restante   :\t" << r->get_tiempo_restante()    << endl                ;
        archivo1 << "Cap. Restante :\t" << r->get_capacidad_restante() << endl                ;
        archivo1 << "Ruta          :\t"                                                       ;    

        for (int j=0; j<r->get_segmentos().size(); j++){
          if (j == r->get_segmentos().size()-1){
            archivo1 << r->get_segmento(j)->get_cliente_i()->get_id_nodo()+1 << " - "         ;
            archivo1 << r->get_segmento(j)->get_cliente_j()->get_id_nodo()+1 << endl          ;
            break                                                                             ; 
          } else {
            archivo1 << r->get_segmento(j)->get_cliente_i()->get_id_nodo()+1 << " - "         ;
          } 
        }
      }

      archivo1 << "-----------------------------------------------------------------" << endl ;
      archivo1 << endl                                                                        ;
    }
  }
  archivo1.close()                                                                          ;



  ofstream archivo2                                           ; 
  //archivo2.open(nombre_instancia + "-" + parametros + ".txt") ; 
  archivo2.open("Resultados/FrentesReRuteo/" + nombre_instancia + "/" + nombre_instancia + "-" + parametros + ".txt") ;
  
  float costo_min  ;
  float costo_prom ;
  float costo_max  ;

  for (int i=0; i<F->get_frente(0).size(); i++){
    //archivo2 << i+1 << " " ;

    costo_min  = 999999999 ;
    costo_prom = 0         ;
    costo_max  = 0         ;

    Individuo* k = F->get_individuo(0, i) ;

    for (Individuo* j: this->get_frente(i)){
      archivo2 << j->get_f1() + k->get_f1() << " " ;

      if (j->get_f1() + k->get_f1() < costo_min){
        costo_min = j->get_f1() + k->get_f1() ;
      }
      if (j->get_f1() + k->get_f1() > costo_max){
        costo_max = j->get_f1() + k->get_f1() ;
      }
      costo_prom = costo_prom + j->get_f1() + k->get_f1() ;

    }
    archivo2 << costo_min << " " << costo_prom/this->get_frente(i).size() << " " << costo_max << " " << k->get_f2() << endl ;
  }
  archivo2.close() ; 
}