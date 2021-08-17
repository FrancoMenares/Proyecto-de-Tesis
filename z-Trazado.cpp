
#include "z-Trazado.h"


void Trazado::imprimir_ruta(Individuo* individuo, Red* red, Instancia* instancia){
  Costos* costos = new Costos()        ; //se crea un objeto de tipo Costos
  TDDijkstra* rutas = new TDDijkstra() ; //se crea un objeto de tipo TDDijkstra

  vector <int> trazado                 ; //almacen temporal de la ruta de un segmento de una ruta
  vector <int> trazados                ; //almance de la ruta de todas las rutas de un individuo
  
  for (Ruta* i: individuo->get_rutas()){
    for (Segmento* j: i->get_segmentos()){
      float hora_inicio = j->get_tiempo_i()            ; //hora de inicio de un semento
      float frecuencia = instancia->get_frec_salidas() ; //frecuencia de preprocesamiento
      int p_inicio = (hora_inicio/frecuencia)          ; //periodo de inicio del segmento
      hora_inicio = frecuencia*p_inicio                ; //hora inicio del periodo de inicio

      int nodo_inicio  = j->get_cliente_i()->get_id_nodo() ; //cliente de inicio del segmento
      int nodo_destino = j->get_cliente_j()->get_id_nodo() ; //cliente de termino del segmento

      rutas->td_ruta_mas_corta(red, costos, nodo_inicio, hora_inicio) ; //se obtiene ruta entre clientes

      Nodo* aux = red->get_nodo(nodo_destino)            ; 
      while (aux->get_padre() != NULL){
        aux = aux->get_padre()                           ; 
        trazado.insert(trazado.begin(), aux->get_id()+1) ; //se guarda la ruta del segmento temporalmente
      }
      for (int k: trazado){
        trazados.push_back(k) ; //se guarda la ruta permanentemente
      }
      trazado.clear()         ; //se elimina la ruta temporal
      
      red->reiniciar_nodos()  ; //se restaura la condicion inicial de los nodos de la red
    }
  }

  int x1 = 0 ; //contador de la ruta
  int x2 = 0 ; //contador de la secuencia
  for (int k: trazados){
    if (k == instancia->get_cliente(instancia->get_cant_clientes())->get_id_nodo()+1){
      x1++   ;
      x2=0   ;
    }

    cout << individuo->get_id() << k << " " << x1 << " " << x2 << endl ;
    x2++     ;
  }
  
  delete rutas  ;
  delete costos ;
}




