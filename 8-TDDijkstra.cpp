
#include "8-TDDijkstra.h"


//--------------- TD_Dijkstra ---------------
void TDDijkstra::ruta_mas_corta(Red* red, Instancia* instancia, Costos* costos, int nodo_inicio, float hora_inicio){
  struct comparar_costo {                                    //se crea estructura para ordenar la cola de prioridad
    bool operator()(Nodo* nodo1, Nodo* nodo2){
      return nodo1->get_costo() > nodo2->get_costo()       ; //criterio de ordenamiento (de menor a mayor segun f)
    }
  }                                                        ;
  priority_queue<Nodo, vector<Nodo*>, comparar_costo> cola ; //se crea la cola de prioridad
  
  float costo = 0              ; //al inicio del algoritmo el costo siempre es 0
  float tiempo = hora_inicio   ; //al inicio del algoritmo el tiempo transcurrido es la hora de inicio
  float amplitud = 0.25        ; //diferencia entre el inicio y termino de un periodo
  int superado = 0             ; //banderin para detectar si el recorrido se pasa al dia siguiente

  Nodo* start = red->get_nodo(nodo_inicio) ; //identificamos el nodo de incio
  start->set_costo(costo)                  ; //el costo en el nodo de inicio es el costo inicial
  start->set_tiempo(tiempo)                ; //el tiempo en el nodo de inicio es el tiempo inicial
  cola.push(start)                         ; //se agrega el nodo inicio a la cola de prioridad

  while (!cola.empty()){         //mientras hayan nodos en la cola de prioridad continua la busqueda
    Nodo* current = cola.top() ; //se toma el primer nodo de la cola de prioridad

    for (int i=0; i<red->get_matriz_ady(current->get_id(), 1); i++){            //se recorre la cantidad de adyacentes que tiene el nodo actual
      int ady = 2+i*(2+red->get_cant_periodos())                              ; //se identifica donde se encuentra el nodo adyacente
      Nodo* next = red->get_nodo(red->get_matriz_ady(current->get_id(), ady)) ; //se toma el nodo adyacente
      
      if (next != start){                                //se evita entrar al nodo de inicio con otro costo
        int periodo = current->get_tiempo()/amplitud   ; //se obtiene el periodo de tiempo
        if (periodo >= red->get_cant_periodos()){        //si se acaba el dia 
          periodo = periodo - red->get_cant_periodos() ; //pasamos al siguiente
        }

        // >>>>>>>>>>>>> INICIO PROCEDIMIENTO IGP <<<<<<<<<<<<<                         //se calcula tiempo y costo de viaje 
        float distancia = red->get_matriz_ady(current->get_id(), ady+1)               ; //se identifica la distancia del arco
        float velocidad = red->get_matriz_ady(current->get_id(), (ady+1)+(periodo+1)) ; //se identifica la velocidad del arco
        tiempo = current->get_tiempo() + (distancia / velocidad)                      ; //se calcula el tiempo
        costo = current->get_costo() + costos->costo_total_arco(velocidad, distancia, tiempo-current->get_tiempo()) ; //se calcula el costo

        if (tiempo > red->get_fin_periodo(red->get_cant_periodos()-1)){    //si la ruta se pasa al dia siguiente
          superado = red->get_fin_periodo(red->get_cant_periodos()-1)    ; //se ajustan los limites de cada periodo
        } else {
          superado = 0                                                   ; //se mantienen los limite originales
        }

        if (tiempo > red->get_fin_periodo(periodo) + superado){ //si se excede el periodo se ajusta tiempo y costo
          float t_previo = current->get_tiempo()     ; //tiempo de viaje que si cumple FIFO
          float c_previo = current->get_costo()      ; //costo de viaje que si cumple FIFO
          float x_previo = distancia                 ; //distancia no cumple FIFO

          while (tiempo > red->get_fin_periodo(periodo) + superado){ //mientras no se ajusten todos los periodo

            float t1 = red->get_fin_periodo(periodo) - t_previo                    ; //tiempo antes del siguiente periodo
            float v1 = red->get_matriz_ady(current->get_id(), (ady+1)+(periodo+1)) ; //velocidad antes del siguiente periodo
            float x1 = t1 * v1                                                     ; //distancia antes del siguiente periodo
            float c1 = costos->costo_total_arco(v1, x1, t1)                        ; //costo antes del siguiente periodo
            
            periodo++                                      ; //se pasa al siguiente periodo
            if (periodo >= red->get_cant_periodos()){        //si se acaba el dia 
              periodo = periodo - red->get_cant_periodos() ; //se pasa al dia siguiente
            }

            float x2 = x_previo - x1                                               ; //distancia para el siguiente periodo
            float v2 = red->get_matriz_ady(current->get_id(), (ady+1)+(periodo+1)) ; //velocidad para el siguiente periodo
            float t2 = x2 / v2                                                     ; //tiempo para el siguiente periodo
            float c2 = costos->costo_total_arco(v2, x2, t2)                        ; //costo para el siguiente periodo
            
            tiempo = t_previo + t1 + t2 ; //tiempo de viaje ajustadp
            costo = c_previo + c1 + c2  ; //costo de viaje ajustado

            t_previo = t_previo + t1 ; //tiempo de viaje que si cumple FIFO
            c_previo = c_previo + c1 ; //costo de viaje que si cumple FIFO
            x_previo = x2            ; //distancia puede no cumplir FIFO

            if (tiempo > red->get_fin_periodo(red->get_cant_periodos()-1)){    //si la ruta se pasa al dia siguiente
              superado = red->get_fin_periodo(red->get_cant_periodos()-1)    ; //se ajustan los limites de cada periodo
            } else {
              superado = 0                                                   ; //se mantienen los limite originales
            }
          }
        }
        // >>>>>>>>>>>>> FIN PROCEDIMIENTO IGP <<<<<<<<<<<<< 

        if (next->get_padre() == 0 || costo < next->get_costo()){   //si el adyacente no tiene padre o se encuentra un mejor costo
          if (costo > 0){
            next->set_tiempo(tiempo)                                ; //se setea el tiempo del adyacente hasta el nodo adyacente
            next->set_costo(costo)                                  ; //se setea el costo del adyacente hasta el nodo adyacente
            next->set_padre(current)                                ; //se setea el padre del adyacente
            cola.push(next)                                         ; //se agrega el adyacente a la cola de prioridad
          }
        }
      }
    }
    cola.pop() ; //se quita el nodo actual de la cola de prioridad
  }
}

//--------------- imprimir_ruta ---------------
void TDDijkstra::imprimir_ruta(Red* red, int id_inicio, int id_destino){
  Nodo* aux = red->get_nodo(id_destino)                    ;
  cout << aux->get_id()+1 << endl                          ;
  if (aux->get_padre() != 0){
    while (aux != red->get_nodo(id_inicio)){
      getchar();
      aux = aux->get_padre()                               ;
      cout << aux->get_id()+1 << endl                      ;
    }
    //cout << endl                                           ;
  } else {
    //cout << endl                                           ;
  }
}









