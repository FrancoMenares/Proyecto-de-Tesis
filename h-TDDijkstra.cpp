
#include "h-TDDijkstra.h"


//--------------- Dijkstra ---------------
void TDDijkstra::ruta_mas_corta(Red* red, int nodo_inicio){
  struct comparar_costo {                                    //se crea estructura para ordenar la cola de prioridad
    bool operator()(Nodo* nodo1, Nodo* nodo2){
      return nodo1->get_costo() > nodo2->get_costo()       ; //criterio de ordenamiento (de menor a mayor segun f)
    }
  };
  priority_queue<Nodo, vector<Nodo*>, comparar_costo> cola ;

  float costo = 0;
  Nodo* star = red->get_nodo(nodo_inicio) ;
  star->set_costo(costo);
  star->set_padre(NULL);
  cola.push(star) ;
  
  while (!cola.empty()){
    Nodo* current = cola.top() ;
    cola.pop();
    
    for (int i=0; i<red->get_matriz_ady(current->get_id(), 1); i++){
      int ady = 2+i*(2+red->get_cant_periodos()) ;
      int id_ady = red->get_matriz_ady(current->get_id(), ady) ;
      Nodo* next = red->get_nodo(id_ady) ;

      if (next == star){ continue ;}

      costo = costo + red->get_matriz_ady(current->get_id(), ady+1) ;

      if (next->get_padre() == 0 || costo < next->get_costo()){
        next->set_costo(costo) ;
        next->set_padre(current) ;
        cola.push(next) ;
      }
    }
  }
}

//--------------- TD_Dijkstra ---------------
void TDDijkstra::td_ruta_mas_corta(Red* red, Costos* costos, int nodo_inicio, float hora_inicio){
  struct comparar_costo {                                    //se crea estructura para ordenar la cola de prioridad
    bool operator()(Nodo* nodo1, Nodo* nodo2){
      return nodo1->get_costo() > nodo2->get_costo()       ; //criterio de ordenamiento (de menor a mayor segun f)
    }
  };
  priority_queue<Nodo, vector<Nodo*>, comparar_costo> cola ;

  float amplitud = 0.25 ;
  float tiempo = hora_inicio;
  float costo = 0;
  float bandera = 0;

  Nodo* star = red->get_nodo(nodo_inicio);
  star->set_tiempo(tiempo);
  star->set_costo(costo);
  star->set_padre(NULL);

  cola.push(star);

  while (!cola.empty()){
    Nodo* current = cola.top() ;
    cola.pop();

    int cant_ady = red->get_matriz_ady(current->get_id(), 1);
    for (int i=0; i<cant_ady; i++){
      int ady = 2+i*(2+red->get_cant_periodos());
      int id_ady = red->get_matriz_ady(current->get_id(), ady);
      Nodo* next = red->get_nodo(id_ady) ;

      if (next == star || current->get_padre() == next){ continue ;}

      int p = current->get_tiempo() / amplitud ;
      if (p > red->get_cant_periodos()-1){
        p = p - red->get_cant_periodos() ;
        bandera = red->get_fin_periodo(red->get_cant_periodos()-1);
      } else {
        bandera = 0;
      }

      float dist = red->get_matriz_ady(current->get_id(), ady+1);
      float vel  = red->get_matriz_ady(current->get_id(), (ady+1)+(p+1));
      tiempo = dist / vel ;
      costo = current->get_costo() + costos->costo_total_arco(vel, dist, tiempo);
      tiempo = tiempo + current->get_tiempo();

      if (tiempo > red->get_fin_periodo(p) + bandera){
        float t_previo = current->get_tiempo();
        float c_previo = current->get_costo();
        float d_previo = dist ;

        while (tiempo > red->get_fin_periodo(p) + bandera){
          float t1 = red->get_fin_periodo(p) + bandera - t_previo;
          float v1 = red->get_matriz_ady(current->get_id(), (ady+1)+(p+1));
          float d1 = t1*v1;
          float c1 = costos->costo_total_arco(v1, d1, t1);

          p = (t_previo + t1) / amplitud ;
          if (p > red->get_cant_periodos()-1){
            p = p - red->get_cant_periodos() ;
            bandera = red->get_fin_periodo(red->get_cant_periodos()-1);
          } else {
            bandera = 0;
          }

          float d2 = d_previo - d1;
          float v2 = red->get_matriz_ady(current->get_id(), (ady+1)+(p+1));
          float t2 = d2 / v2 ;
          float c2 = costos->costo_total_arco(v2, d2, t2);

          t_previo = t_previo + t1;
          c_previo = c_previo + c1 ;
          d_previo = d2;

          tiempo = t_previo + t2 ;
          costo = c_previo + c2 ;
        }
      }

      if (next->get_padre() == 0 || costo < next->get_costo()){
        next->set_tiempo(tiempo);
        next->set_costo(costo) ;
        next->set_padre(current) ;
        cola.push(next) ;
      }
    }
  }
}

//--------------- imprimir_ruta ---------------
void TDDijkstra::imprimir_ruta(Red* red, int id_inicio, int id_destino, int ruta){
  Nodo* aux = red->get_nodo(id_destino) ;
  cout << aux->get_id()+1 << " " << ruta << endl ;
  while (aux->get_padre() != NULL){
    aux = aux->get_padre() ;
    cout << aux->get_id()+1 << " " << ruta << endl ;
  }
}