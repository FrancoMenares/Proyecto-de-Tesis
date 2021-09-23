//
#include "n-Poblacion.h"


Poblacion::Poblacion(Instancia* instancia){
  this->instancia = instancia ;
}


//--------------- Instancia ---------------
Instancia* Poblacion::get_instancia(void)          { return this->instancia         ;}


//--------------- Poblacion ---------------
void Poblacion::agregar_individuo(Individuo* i)    { this->poblacion.push_back(i)   ;}
void Poblacion::insertar_individuo(int pos, Individuo* i){
  this->poblacion.insert(this->poblacion.begin()+pos, i)                            ;
}

vector <Individuo*> Poblacion::get_poblacion(void) { return this->poblacion         ;}
Individuo* Poblacion::get_individuo(int pos)       { return this->poblacion.at(pos) ;}

void Poblacion::eliminar_poblacion(void) {
  this->poblacion.clear()                                                           ;
  this->poblacion.shrink_to_fit()                                                   ;
}

void Poblacion::limpiar_poblacion(void){
  for (Individuo* i: this->poblacion){
    if (i->get_dominado_por() != 0){
      delete i                           ;
    } else {
      i->eliminar_individuos_dominados() ;
    }
  }
  this->poblacion.clear()                ;
  this->poblacion.shrink_to_fit()        ;
}


//--------------- imprimir poblacion ---------------
void Poblacion::imprimir_poblacion(void){
  for (Individuo* i: this->poblacion){
    i->imprimir_individuo() ;
  }
}


//--------------- contruccion de la poblacion inicial ---------------
void Poblacion::construir_poblacion_inicial(int lambda){
  Individuo* aux                                         ; //individuo temporal
  Construccion* construir = new Construccion()           ; //objeto para contruir individuo
  for (int i=0; i<lambda; i++){
    aux = new Individuo()                                ; //se crea un nuevo individuo
    construir->individuo_aleatorio(this->instancia, aux) ; //se construye la solucion
    this->poblacion.push_back(aux);
  }
  delete construir                                       ; //se destruye objeto
}

    
//--------------- seleccion de padre para cruce ---------------
Individuo* Poblacion::torneo_binario_1(int aceptacion){
  Individuo* p = this->get_individuo(rand()%(this->poblacion.size())) ; //se elige un padre
  Individuo* q = this->get_individuo(rand()%(this->poblacion.size())) ; //se elige otro padre
  while (p == q){                                                       //si los padres son iguales
    q = this->get_individuo(rand()%(this->poblacion.size()))          ; //se elige otro otro padre
  }

  int prob = rand()%(100)                                    ; //probabilidad aleatoria
  if (p->get_ranking() < q->get_ranking()){                    //si p domina a q
    if (prob <= aceptacion){                                   //y se acepta p
      return p                                               ; //se retorna p
    } else {                                                   //si no se acepta p
      return q                                               ; //se retorna q
    }
  } else if (q->get_ranking() < p->get_ranking()){             //q domina a p
    if (prob <= aceptacion){                                   //y se acepta q
      return q                                               ; //se retorna q
    } else {                                                   //si no se acepta q
      return p                                               ; //se retorna p
    }
  } else if (p->get_hacinamiento() > q->get_hacinamiento()){   //si no se dominan, pero p mejor que q
    if (prob <= aceptacion){                                   //y se acepta p
      return p                                               ; //se retorna p
    } else {                                                   //si no se acepta p
      return q                                               ; //se retorna q
    }
  } else {                                                     //si no se dominan, pero q mejor o igual que p
    if (prob <= aceptacion){                                   //y se acepta q
      return q                                               ; //se retorna q
    } else {                                                   //si no se acepta q
      return p                                               ; //se retorna p
    }
  }
}

Individuo* Poblacion::torneo_binario_2(Individuo* p, Individuo* q){
  if (p->get_ranking() < q->get_ranking()){                    //si p domina a q
    return p                                                 ; //se retorna p
  } else if (q->get_ranking() < p->get_ranking()){             //q domina a p
    return q                                                 ; //se retorna q
  } else if (p->get_hacinamiento() > q->get_hacinamiento()){   //si no se dominan, pero p mejor que q
    return p                                                 ; //se retorna p
  } else {                                                     //si no se dominan, pero q mejor o igual que p
    return q                                                 ; //se retorna q
  }
}
    

//--------------- generacion de los hijos ---------------
void Poblacion::generar_descendientes(Poblacion* Q, int lambda, int p_aceptacion, int p_cruce, int p_mutacion){
  Poblacion* hijos = Q                                ; //se crea objeto para la poblacion de hijo
  OX* ox = new OX()                                   ; //se crea objeto para cruzar padres
  AjusteHora* ajustar = new AjusteHora()              ; //se crea objeto para ajustar la hora de salida
  CambioCliente* cambiar = new CambioCliente()        ; //se crea objeto para cambiar un cliente de posicion
  InvertirClientes* invertir = new InvertirClientes() ; //se crea objeto para invertir los clientes de un segmento

  Individuo* p               ; //un padre a cruzar
  Individuo* q               ; //otro padre a cruzar
  int cant_hijos             ; //cantidad de hijo a obtener en un cruce
  int elegir_o               ; //identificador de operador de mutacion
  vector <Individuo*> pulgas ; //vector que entrega los hijos luego de un

  while (hijos->get_poblacion().size() < lambda){         //mientras no se alcance el tamaño de la poblacion
    p = this->torneo_binario_1(p_aceptacion)            ; //se identifica padre un a cruzar
    q = this->torneo_binario_1(p_aceptacion)            ; //se identifica padre otro a cruzar
    
    if ( (lambda - hijos->get_poblacion().size()) < 2){   //si falta un hijo en la nueva poblacion
      cant_hijos = 1                                    ; //se debe obtener un hijo del cruzamiento
    } else {                                              //si faltan dos o mas
      cant_hijos = 2                                    ; //se deben obtener dos hijos del cruzamiento
    }

    if (rand()%(100) <= p_cruce){                         //si se acepta la probabilidad de cruzamiento
      pulgas = ox->cruzar_individuos(p, q, hijos->get_instancia(), cant_hijos) ; // se realiza el cruce

      for (Individuo* hijo: pulgas){       //para cada hijo del cruce
        if (rand()%(100) <= p_mutacion){   //si se acepta la probabilidad de mutacion
          elegir_o = rand()%(99)         ; //se selecciona operador de mutacion aleatorio

          if (elegir_o < 34){                                                    //entre 0 y 33 
            ajustar->ajustar_hora_ruta(hijo, hijos->get_instancia())           ; //se ajusta la hora
          } else if (elegir_o > 66 ){                                            //entre 67 y 99 
            cambiar->cambiar_cliente_aleatorio(hijo, hijos->get_instancia())   ; //se cambia cliente de posicion
          } else {                                                               //entre 34 y 66 
            invertir->invertir_clientes_segmento(hijo, hijos->get_instancia()) ; //se invierte un segmento
          }
        }
        hijos->agregar_individuo(hijo) ; //se agrega el hijo a la nueva poblacion
      }

    //PADRES QUE NO PASARON POR EL CRUZAMIENTO
    } else {                                                          //si no se acepta la probabilidad de cruce
      if (cant_hijos == 1){                                           //si solo falta un hijo a la poblacion
        p = new Individuo(*this->torneo_binario_2(p, q)) ; //se seleciona el mejor padre

        if (rand()%(100) <= p_mutacion){   //si se acepta la probabilidad de mutacion
          elegir_o = rand()%(99)         ; //se selecciona operador de mutacion aleatorio

          if (elegir_o < 34){                                                 //entre 0 y 33 
            ajustar->ajustar_hora_ruta(p, hijos->get_instancia())           ; //se ajusta la hora
          } else if (elegir_o > 66 ){                                         //entre 67 y 99 
            cambiar->cambiar_cliente_aleatorio(p, hijos->get_instancia())   ; //se cambia cliente de posicion
          } else {                                                            //entre 34 y 66 
            invertir->invertir_clientes_segmento(p, hijos->get_instancia()) ; //se invierte un segmento
          }
        }
        hijos->agregar_individuo(p) ; //se agrega el hijo a la nueva poblacion

      } else {
        p = new Individuo(*p)            ; //se seleciona el mejor padre
        if (rand()%(100) <= p_mutacion){   //si se acepta la probabilidad de mutacion
          elegir_o = rand()%(99)         ; //se selecciona operador de mutacion aleatorio

          if (elegir_o < 34){                                                 //entre 0 y 33 
            ajustar->ajustar_hora_ruta(p, hijos->get_instancia())           ; //se ajusta la hora
          } else if (elegir_o > 66 ){                                         //entre 67 y 99 
            cambiar->cambiar_cliente_aleatorio(p, hijos->get_instancia())   ; //se cambia cliente de posicion
          } else {                                                            //entre 34 y 66 
            invertir->invertir_clientes_segmento(p, hijos->get_instancia()) ; //se invierte un segmento
          }
        }
        hijos->agregar_individuo(p)                                         ; //se agrega p a la poblacion


        q = new Individuo(*q)            ; //se seleciona el mejor padre
        if (rand()%(100) <= p_mutacion){   //si se acepta la probabilidad de mutacion
          elegir_o = rand()%(99)         ; //se selecciona operador de mutacion aleatorio

          if (elegir_o < 34){                                                 //entre 0 y 33 
            ajustar->ajustar_hora_ruta(q, hijos->get_instancia())           ; //se ajusta la hora
          } else if (elegir_o > 66 ){                                         //entre 67 y 99 
            cambiar->cambiar_cliente_aleatorio(q, hijos->get_instancia())   ; //se cambia cliente de posicion
          } else {                                                            //entre 34 y 66 
            invertir->invertir_clientes_segmento(q, hijos->get_instancia()) ; //se invierte un segmento
          }
        }
        hijos->agregar_individuo(q)                                         ; //se agrega q a la poblacion
      }
    }  
  }

  delete ox              ; //se elimina objeto
  delete ajustar         ; //se elimina objeto
  delete cambiar         ; //se elimina objeto
  delete invertir        ; //se elimina objeto
  pulgas.clear()         ; //se limpia vector
  pulgas.shrink_to_fit() ; //reduce el tamaño del vector
}

    
//--------------- generacion de los hijos ---------------
void Poblacion::combinar_poblacion(Poblacion* P, Poblacion* Q){
  for (int i=0; i<Q->get_poblacion().size(); i++){     //para cada padre e hijo
    this->insertar_individuo(i, P->get_individuo(i)) ; //se agrega el padre sucesivamente
    this->agregar_individuo(Q->get_individuo(i))     ; //se agrega el hijo al final (tambien sucesivamente)
  }
  P->eliminar_poblacion() ; //se limpia la poblacion de padres
  Q->eliminar_poblacion() ; //se limpia la poblacion de hijos
}


//--------------- detectar solucion dominada ---------------
int Poblacion::dominancia(Individuo* p, Individuo* q){
  int punto_para_p = 0                               ; //contador de objetivos en los que gana p
  int punto_para_q = 0                               ; //contador de objetivos en los que gana q

  if (p->get_f1() < q->get_f1()){                      //si en f1 gana p
    punto_para_p++                                   ; //se suma 1 al contador de p
  } else if (p->get_f1() > q->get_f1()){               //si gana q
    punto_para_q++                                   ; //se suma 1 al contador de q
  }

  if (p->get_f2() < q->get_f2()){                      //si en f2 gana p
    punto_para_p++                                   ; //se suma 1 al contador de p
  } else if (p->get_f2() > q->get_f2()){               //si gana q
    punto_para_q++                                   ; //se suma 1 al contador de q
  }

  if (punto_para_p > 0 && punto_para_q == 0){          //p domina a q 
    return 1                                         ; //
  } else if (punto_para_p == 0 && punto_para_q > 0){   //q domina a p
    return -1                                        ; //
  } else {                                             //soluciones no dominadas
    return 0                                         ; //
  }
}


//--------------- clasificacion no dominada de las soluciones ---------------
void Poblacion::clasificar_poblacion(Frentes* F, int lambda){
  int dominancia ;
  F->crear_frente()                                      ; //se crea el primer frente
  for (Individuo* p: this->poblacion){                     //se recorre los individuos de la poblacion
    for (Individuo* q: this->poblacion){                   //se recooren los individuos de la poblacion
      if (p != q){                                         //si son distintos
        dominancia = this->dominancia(p, q)              ; //se evalua dominancia entre p y q
        if (dominancia == 1){                              //si p domina a q
          p->agregar_individuo_dominado(q)               ; //se agrega q a la lista de dominados de p
        } else if (dominancia == -1){                      //si q domina a p
          p->set_dominado_por(p->get_dominado_por()+1)   ; //se suma 1 a la cantidad de individuos que dominan a p
        }
      }
    }
    if (p->get_dominado_por() == 0){                       //si p no esta dominado por ninguna solucion
      F->agregar_individuo(0, p)                         ; //se agrega p a primer frente
      p->set_ranking(0)                                  ; //se setea el ranking del individuo
    }
  }
  
  int suma = F->get_frente(0).size()                     ; //contador de individuo en los frentes
  int i = 1                                              ; //contador de frente actual
  while (suma < lambda){                                   //mientras no se supere la cantidad de nuevos padres
    F->crear_frente()                                    ; //se crea un nuevo frente
    for (Individuo* p: F->get_frente(i-1)){                //se recorren las soluciones del frente actual
      for (Individuo* q: p->get_individuos_dominados()){   //se recorren las doluciones dominadas por p
        q->set_dominado_por(q->get_dominado_por()-1)     ; //se descuenta 1 al contador de soluciones que dominan a q
        if (q->get_dominado_por() == 0){                   //si se recoorieron todas las soluciones que dominan a q
          F->agregar_individuo(i, q)                     ; //se agrega q al nuevo frente
          q->set_ranking(i)                              ; //se setea el ranking del individuo
        }
      }
    }
    suma = suma + F->get_frente(i).size()                ; //se actualiza la cantidad de individuos
    i++                                                  ; //se pasa al siguiente frente
  }
  this->limpiar_poblacion()                              ; //se eliminan los individuos de peor calidad
}


//--------------- pasar nuevos padres del frente a la poblacion ---------------
void Poblacion::agregar_nuevos_padres(Frentes* F, int lambda){
  int i = 0                                                           ; //contador de frente
  while (this->poblacion.size() + F->get_frente(i).size() <= lambda){   //mientras no se supere el tamaño de la poblacion
    F->calcular_distancia_hacinamiento(i)                             ; //se calcula dist de hacinamiento al frente i
    for (Individuo* j: F->get_frente(i)){                               //cada individuo en el frente i
      this->agregar_individuo(j)                                      ; //se agrega el individuo a la nueva poblacion
    }
    F->eliminar_frente_1(i)                                           ; //se eliminan los individuos del frente i
    i++                                                               ; //se pasa al siguiente frente
    if (i == F->get_frentes().size()) {                                 //si se sobrepasa la cantidad de frentes
      i--                                                             ; //se reretrocede al ultimo frente
      break                                                           ; //se acaba el ciclo
    }
  }
  
  int faltantes = lambda - this->poblacion.size()     ; //se calcula individuos faltantes en nueva poblacion
  if (faltantes > 0){                                   //si faltan individuos
    F->calcular_distancia_hacinamiento(i)             ; //se calcula dist de hacinamiento al frente i
    F->ordenar_frente(i)                              ; //se ordena el frente segun dist de hacinamiento
    for (int j=0; j<faltantes; j++){                    //para cada individuo faltante
      this->agregar_individuo(F->get_individuo(i, 0)) ; //se selecciona el primero en el frente
      F->eliminar_individuo(i, 0)                     ; //se elimina el individuo del frente
    }
  }
  F->eliminar_frente_2(i)                             ; //se limpian y eliminan todos los frentes
}





