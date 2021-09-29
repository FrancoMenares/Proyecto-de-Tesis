
#include "zr-CX.h"


//--------------- extrae la secuencia de las rutas de un individuo ---------------
vector <int> CX::extraer_secuencia(Individuo* individuo){
  vector <int> secuencia ;
  for (Ruta* i: individuo->get_rutas()){
    for (Segmento* j: i->get_segmentos()){
      if (j->get_cliente_j() != individuo->get_ruta(0)->get_segmento(0)->get_cliente_i()){
        secuencia.push_back(j->get_cliente_j()->get_id_cliente()) ;
      }
    }
  }
  return secuencia ;
}


//--------------- crear dos hijos siameses a partir de dos padres ---------------
vector <int> CX::crear_hijo(vector <int> padre1, vector <int> padre2){
  bool debug = false;

  vector <int> siames(padre1.size()*2, padre1.size()) ; //vector que almacena dos hijos (siames)

  //----------------------------------- HERENCIA X -----------------------------------
  int h = 0                             ; //indice dentro de un padre
  int k = 1                             ; //contador de clientes en el ciclo de genes
  int p = padre1.size()                 ; //cantidad de clientes luego de un ciclo cerrado en h
  while (padre1.at(h) == padre2.at(h)){   //mientras haya un ciclo cerrado en h
    h++                                 ; //se corre el indice inicial
    p--                                 ; //se disminuye p
  }
  int r = h                             ; //indice desde el cual comienza el ciclo de genes

  while (true){
    siames.at(h) = padre1.at(h)               ; //se agrega gen del padre 1 al hijo 1
    siames.at(h+padre1.size()) = padre2.at(h) ; //se agrega gen del padre 2 al hijo 2

    if (debug){
      cout << "siames : " ;
      for (int i: siames){
        if (i == padre2.size()){
          cout << "- " ;
        } else {
          cout << i << " " ;
        }
      }
      cout << endl ;
    }

    for (int j=0; j<padre1.size(); j++){   //se busca indice del gen del padre 2 en el padre 1
      if (padre1.at(j) == padre2.at(h)){   //si se encuentra el indice
        h = j                            ; //se actualiza el indice
        break                            ; //se continua completando el ciclo
      }
    }

    if (h == r){   //si el nuevo indice es igual al inicial del ciclo
      break      ; //el ciclo se ha completado
    } else {
      k++        ; //se incrementa el contador de clientes
    }
  }

  if (k == p){  //si el contador de clientes es igual a la cant. de clientes disponibles
    return {} ; //se retorna un siames vacio
  }

  //----------------------------------- HERENCIA Y ----------------------------------
  r = 0 ;                                         //contador de genes iguales en los hijos
  for (int i=0; i<padre1.size(); i++){            //se busca genes brutos
    if (siames.at(i) == padre1.size()){           //si se encuentra un gen bruto
      siames.at(i) = padre2.at(i)               ; //se setea gen del padre 2 en el hijo 1
      siames.at(i+padre1.size()) = padre1.at(i) ; //se setea gen del padre 1 en el hijo 2
    }
    
    if (siames.at(i) == padre1.at(i)){   //si el gen del hijo es igual al del padre
      r++                              ; //se incrementa el contador
    }
  }

  if (r == padre1.size()){   //si contador de genes repetidos es igual a cantidad de clientes
    return {}              ; //se retorna un siames vacio
  }

  if (debug){
    cout << "siames : " ;
    for (int i: siames){
      if (i == padre2.size()){
        cout << "- " ;
      } else {
        cout << i << " " ;
      }
    }
    cout << endl << endl ;
  }

  return siames ; //se retorna el siames
} 


//--------------- cruza dos padres generando dos hijos ---------------
void CX::cruzar_individuos(Individuo* individuo1, Individuo* individuo2, Instancia* instancia){

  vector <int> padre1 = this->extraer_secuencia(individuo1) ;
  vector <int> padre2 = this->extraer_secuencia(individuo2) ;

  if (false){
    cout << "padre1 : " ;
    for (int i: padre1){
      cout << i << " " ;
    }
    cout << endl ;

    cout << "padre2 : " ;
    for (int i: padre2){
      cout << i << " " ;
    }
    cout << endl ;
  }

  vector <int> hijo1 = this->crear_hijo(padre1, padre2) ;
  vector <int> hijo2                                    ;

  if (!hijo1.empty()){
    int i = hijo1.size()/2             ;   
    while (hijo2.size() < i){            
      hijo2.push_back(hijo1.at(i))     ; 
      hijo1.erase(hijo1.begin() + (i)) ; 
    }
  }

  if (true){
    cout << endl << "hijo1 : " ;
    for (int i: hijo1){
      cout << i << " " ;
    }
    cout << endl ;
    
    cout << "hijo2 : " ;
    for (int i: hijo2){
      cout << i << " " ;
    }
    cout << endl << endl ;
  }
}