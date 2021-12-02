
#include "h-TDDijkstra.h"


//--------------- Dijkstra (distancia) ---------------
void TDDijkstra::ruta_mas_corta(Red* red, int nodo_inicio){
  struct comparar_costo {                                    //se crea estructura para ordenar la cola de prioridad
    bool operator()(Nodo* nodo1, Nodo* nodo2){
      return nodo1->get_costo() > nodo2->get_costo()       ; //criterio de ordenamiento (de menor a mayor segun f)
    }
  }                                                        ;
  priority_queue<Nodo, vector<Nodo*>, comparar_costo> cola ; //cola de prioridad

  float costo = 0                         ; //costo acumulado
  Nodo* star = red->get_nodo(nodo_inicio) ; //nodo de inicio
  star->set_costo(costo)                  ; //distancia en el nodo de inicio
  star->set_padre(NULL)                   ; //el nodo de inicio nunca tendra un padre :((((( <<<<<<=============
  cola.push(star)                         ; //se agrega nodo de inicio a la cola de prioridad
  
  while (!cola.empty()){
    Nodo* current = cola.top() ; //se toma el nodo de la cola de prioridad
    cola.pop()                 ; //tambien se elimina
    
    for (int i=0; i<red->get_matriz_ady(current->get_id(), 1); i++){    //se recorren los nodos adyacentes
      int ady = 2+i*(2+red->get_cant_periodos())                      ; //se busca la posicion del nodo adyacente
      int id_ady = red->get_matriz_ady(current->get_id(), ady)        ; //se identifica el id
      Nodo* next = red->get_nodo(id_ady)                              ; //se identifica el nodo adyacente

      if (next == star){ continue ;} //si el nodo de inicio es adyacente se detinen la busqueda

      costo = costo + red->get_matriz_ady(current->get_id(), ady+1) ; //se calcula la distancia hasta el nodo adyacente

      if (next->get_padre() == 0 || costo < next->get_costo()){
        next->set_costo(costo)   ; //costo del nodo adyacente
        next->set_padre(current) ; //padre del nodo adyacente
        cola.push(next)          ; //se agrega nodo de adyacente a la cola de prioridad
      }
    }
  }
}


//--------------- TD_Dijkstra (costo operativo) ---------------
void TDDijkstra::td_ruta_mas_corta(Red* red, Costos* costos, int nodo_inicio, float hora_inicio){
  struct comparar_costo {                                    //se crea estructura para ordenar la cola de prioridad
    bool operator()(Nodo* nodo1, Nodo* nodo2){
      return nodo1->get_costo() > nodo2->get_costo()       ; //criterio de ordenamiento (de menor a mayor segun f)
    }
  }                                                        ;
  priority_queue<Nodo, vector<Nodo*>, comparar_costo> cola ; //cola de prioridad

  float amplitud = 0.25      ; //amplitud de los intervalos de tiempo
  float tiempo = hora_inicio ; //tiempo de inicio de la ruta
  float costo = 0            ; //costo en el nodo de inicio
  float bandera = 0          ; //bandera que avisa si la ruta se pasa al dia siguiente

  Nodo* star = red->get_nodo(nodo_inicio) ; //nodo de inicio
  star->set_tiempo(tiempo)                ; //tiempo en el nodo de inicio
  star->set_costo(costo)                  ; //costo en el nodo de inicio
  star->set_padre(NULL)                   ; //padre del nodo de inicio
  cola.push(star)                         ; //se agrega el nodo de inicio a la cola de prioridad

  while (!cola.empty()){
    Nodo* current = cola.top() ; //se toma el nodo de la cola de prioridad
    cola.pop()                 ; //tambien se elimina

    int cant_ady = red->get_matriz_ady(current->get_id(), 1)   ; //se identifica cuantos adyacentes tiene el nodo
    for (int i=0; i<cant_ady; i++){                              //se recorren los nodos adyacentes
      int ady = 2+i*(2+red->get_cant_periodos())               ; ////se busca la posicion del nodo adyacente
      int id_ady = red->get_matriz_ady(current->get_id(), ady) ; //se identifica el id
      Nodo* next = red->get_nodo(id_ady)                       ; //se identifica el nodo adyacente

      if (next == star || current->get_padre() == next){ continue  ;}

      int p = current->get_tiempo() / amplitud                     ; //se identifica el periodo de tiempo
      if (p > red->get_cant_periodos()-1){                           //si se pasa al dia siguiente
        p = p - red->get_cant_periodos()                           ; //se ajuta el periodo
        bandera = red->get_fin_periodo(red->get_cant_periodos()-1) ; //se activa la bandera
      } else {
        bandera = 0                                                ; //se desactiva la bandera
      }

      float dist = red->get_matriz_ady(current->get_id(), ady+1)                 ; //distancia hasta el adyacente
      float vel  = red->get_matriz_ady(current->get_id(), (ady+1)+(p+1))         ; //velocidad entre el adyacente
      tiempo = dist / vel                                                        ; //tiempo entre el adyacente
      costo = current->get_costo() + costos->costo_total_arco(vel, dist, tiempo) ; //costo hasta el adyacente
      tiempo = tiempo + current->get_tiempo()                                    ; //tiempo hasta el adyacente

      if (tiempo > red->get_fin_periodo(p) + bandera){ //si existe un cambio de periodo, se recalcula segun IGP FIFO
        float t_previo = current->get_tiempo() ; //utimo tiempo que cumple FIFO
        float c_previo = current->get_costo()  ; //ultimo costo que cumple FIFO
        float d_previo = dist                  ; //distancia donde se debe comprobar FIFO

        while (tiempo > red->get_fin_periodo(p) + bandera){ //mientras hayan cambios de periodos
          float t1 = red->get_fin_periodo(p) + bandera - t_previo          ; //tiempos antes del cambio
          float v1 = red->get_matriz_ady(current->get_id(), (ady+1)+(p+1)) ; //velocidad antes del cambio
          float d1 = t1*v1                                                 ; //distancia antes del cambio
          float c1 = costos->costo_total_arco(v1, d1, t1)                  ; //costo antes del cambio

          p = (t_previo + t1) / amplitud                               ; //se identifica el nnuevo periodo (+1)
          if (p > red->get_cant_periodos()-1){                           //si se pasa al dia siguiente
            p = p - red->get_cant_periodos()                           ; //se ajuta el periodo
            bandera = red->get_fin_periodo(red->get_cant_periodos()-1) ; //se activa la bandera
          } else {
            bandera = 0                                                ; //se desactiva la bandera
          }

          float d2 = d_previo - d1                                         ; //distancia luego del cambio
          float v2 = red->get_matriz_ady(current->get_id(), (ady+1)+(p+1)) ; //velocidad luego del cambio
          float t2 = d2 / v2                                               ; //tiempo luego del cambio
          float c2 = costos->costo_total_arco(v2, d2, t2)                  ; //costo luego del cambio

          t_previo = t_previo + t1 ; //se actualiza utimo tiempo que cumple FIFO
          c_previo = c_previo + c1 ; //se actualiza ultimo costo que cumple FIFO
          d_previo = d2            ; //se actualiza distancia donde se debe comprobar FIFO

          tiempo = t_previo + t2 ; //se actualiza tiempo hasta el adyacente
          costo = c_previo + c2  ; //se actualiza costo hasta el adyacente
        }
      }

      if (next->get_padre() == 0 || costo < next->get_costo()){
        next->set_tiempo(tiempo) ; //se setea tiempo hasta el adyacente
        next->set_costo(costo)   ; //se setea costo hasta el adyacente
        next->set_padre(current) ; //se setea padre del adyacente
        cola.push(next)          ; //se agrega adyacente a la cola de prioridad
      }
    }
  }
}


//--------------- imprimir_ruta ---------------
void TDDijkstra::imprimir_ruta(Red* red, int id_inicio, int id_destino, int ruta){
  Nodo* aux = red->get_nodo(id_destino)            ;
  cout << aux->get_id()+1 << " " << ruta << endl   ;
  while (aux->get_padre() != NULL){
    aux = aux->get_padre()                         ;
    cout << aux->get_id()+1 << " " << ruta << endl ;
  }
}