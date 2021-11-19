
#include "z-Trazado.h"


void Trazado::escibir_rutas_completas(string nombre_instancia, string parametros, Frentes* F, Red* red, Instancia* instancia){
  Costos* costos = new Costos()        ;
  TDDijkstra* rutas = new TDDijkstra() ;

  ofstream archivo2                    ; 
  //archivo2.open("Resultados/Rutas.txt")    ;  
  archivo2.open("Resultados/RutasAlgoritmo/" + nombre_instancia + "/" + nombre_instancia + "-" + parametros + ".txt") ; 

  archivo2 << "Nodo,Individuo,Ruta,Segmento,Tiempo viaje,Costo viaje,Tiempo atencion,Costo atencion,Tasa fallo,Demanda" <<endl ;

  for (int i=0; i<F->get_frente(0).size(); i++){
    Individuo* I = F->get_individuo(0,i) ;

    for (int r=0; r<I->get_rutas().size(); r++){
      Ruta* R = I->get_ruta(r) ;

      float costo_aterior = 0  ;

      for (int s=0; s<R->get_segmentos().size(); s++){
        Segmento* S = R->get_segmento(s) ;

        red->reiniciar_nodos()           ;

        int nodo_inicio   = S->get_cliente_i()->get_id_nodo()           ;
        int p1 = S->get_tiempo_i()/instancia->get_frec_salidas()        ;
        float hora_inicio = (float)(p1*instancia->get_frec_salidas())   ;
        float dif_hora = S->get_tiempo_i() - hora_inicio                ;

        rutas->td_ruta_mas_corta(red, costos, nodo_inicio, hora_inicio) ;

        Nodo* aux = red->get_nodo(S->get_cliente_j()->get_id_nodo())          ;
        int p2 = (aux->get_tiempo() + dif_hora)/instancia->get_frec_salidas() ;

        if (aux->get_id() != instancia->get_cliente(instancia->get_cant_clientes())->get_id_nodo()){
          archivo2 << aux->get_id()+1                         << ","  ;
          archivo2 << i                                       << ","  ;
          archivo2 << r                                       << ","  ;
          archivo2 << s                                       << ","  ;
          archivo2 << aux->get_tiempo() + dif_hora            << ","  ;
          archivo2 << aux->get_costo() + S->get_costo_i()     << ","  ;
          archivo2 << S->get_cliente_j()->get_tiempo_aten(p2) << ","  ;
          archivo2 << S->get_cliente_j()->get_costo_aten(p2)  << ","  ;
          archivo2 << S->get_cliente_j()->get_tasas_fallo(p2) << ","  ;
          archivo2 << S->get_demanda_t()                      << endl ;
        } else {
          archivo2 << aux->get_id()+1                         << ","  ;
          archivo2 << i                                       << ","  ;
          archivo2 << r                                       << ","  ;
          archivo2 << s                                       << ","  ;
          archivo2 << aux->get_tiempo() + dif_hora            << ","  ;
          archivo2 << aux->get_costo() + S->get_costo_i()     << ","  ;
          archivo2 << 0                                       << ","  ;
          archivo2 << 0                                       << ","  ;
          archivo2 << 0                                       << endl ;
        }

        while (aux->get_padre() != 0){
          aux = aux->get_padre()                                      ; 

          archivo2 << aux->get_id()+1                         << ","  ;
          archivo2 << i                                       << ","  ;
          archivo2 << r                                       << ","  ;
          archivo2 << s                                       << ","  ;
          archivo2 << aux->get_tiempo() + dif_hora            << ","  ;
          archivo2 << aux->get_costo() + S->get_costo_i()     << endl ;
        }
      }
    }
  }

  archivo2.close()                                        ; 
}




