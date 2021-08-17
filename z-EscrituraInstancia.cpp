
#include "z-EscrituraInstancia.h"
#include <sstream>


void EscrituraInstancia::escribir_instancia(Instancia* instancia){
  string aux1 = "InstanciasModelo"                 ;
  string aux2 = ""                                 ;
  string aux3 = ".dat"                             ;
  for (int i=0; i<nombre_instancia.size()-4; i++){
    aux2 = aux2 + nombre_instancia[i]              ;
    if (aux2 == "Instancias"){
      aux2 = ""                                    ;
    }
  }
  this->nombre_instancia = aux1 + aux2 + aux3      ;



  ofstream archivo               ;
  archivo.open(nombre_instancia) ;



  //ponderadores
  archivo << endl                           ;
  archivo << "param sigma         " << endl ;
  archivo << ":	1	2 :=            " << endl ;
  archivo << "1	0.00001	0.99999   " << endl ;
  archivo << "2	0.1	0.9           " << endl ;
  archivo << "3	0.2	0.8           " << endl ;
  archivo << "4	0.3	0.7           " << endl ;
  archivo << "5	0.4	0.6           " << endl ;
  archivo << "6	0.5	0.5           " << endl ;
  archivo << "7	0.6	0.4           " << endl ;
  archivo << "8	0.7	0.3           " << endl ;
  archivo << "9	0.8	0.2           " << endl ;
  archivo << "10	0.9	0.1         " << endl ;
  archivo << "11	0.99999	0.00001 " << endl ;
  archivo << ";                   " << endl ;
  archivo << endl                           ;



  //deposito
  archivo << "param o := " << instancia->get_cliente(instancia->get_cant_clientes())->get_id_nodo()+1 << " ;" << endl      ;
  archivo << "param s := " << instancia->get_cliente(instancia->get_cant_clientes())->get_id_nodo()+1+5000 << " ;" << endl ;
  archivo << endl                                                                                                          ;
  

  //clientes
  archivo << "set R := "                                         ;
  for (int i=0; i<instancia->get_cant_clientes(); i++){
    archivo << instancia->get_cliente(i)->get_id_nodo()+1 << " " ; 
  }
  archivo << ";" << endl                                         ;
  

  //periodos
  archivo << "set M := "                                                                                                       ;
  for (int i=0; i<instancia->get_cant_salidas(); i++){
    if (i*instancia->get_frec_salidas()>=instancia->get_inicio() && i*instancia->get_frec_salidas()<instancia->get_termino()){
      archivo << i << " "                                                                                                      ;
    }
  }
  archivo << ";" << endl                                                                                                       ;
  

  //vehiculos
  archivo << "set K := "                                ;
  for (int i=0; i<instancia->get_cant_camiones(); i++){
    archivo << i+1 << " "                               ;
  }
  archivo << ";" << endl                                ;
  archivo << endl                                       ;
  

  //capacidad vehiculos
  archivo << "param b := " << instancia->get_cap_camiones() << " ;" << endl << endl ;
  

  //demanda clientes
  archivo << "param d := " << endl                                    ;
  for (Cliente* i: instancia->get_clientes()){
    if (i == instancia->get_cliente(instancia->get_cant_clientes())){
      archivo << i->get_id_nodo()+1 << "\t" << 0 <<endl               ; 
      archivo << i->get_id_nodo()+1+5000 << "\t" << 0 <<endl          ; 
      break;
    }
    archivo << i->get_id_nodo()+1 << "\t" << 1 <<endl                 ; 
  }
  archivo << ";" << endl << endl                                      ;


  //limite inferior
  archivo << "param TTI := " << endl                                                                                            ;
  for (int i=0; i<instancia->get_cant_salidas(); i++){
    if (i*instancia->get_frec_salidas()>=instancia->get_inicio() && i*instancia->get_frec_salidas()<instancia->get_termino()){
      archivo << i << "\t" <<  i*instancia->get_frec_salidas() << endl                                                         ;
    }
  }
  archivo << ";" << endl << endl                                                                                               ;


  //limite superior
  archivo << "param TTF := " << endl                                                                                            ;
  for (int i=0; i<instancia->get_cant_salidas(); i++){
    if (i*instancia->get_frec_salidas()>=instancia->get_inicio() && i*instancia->get_frec_salidas()<instancia->get_termino()){
      archivo << i << "\t" <<  (i+1)*instancia->get_frec_salidas() << endl                                                     ;
    }
  }
  archivo << ";" << endl << endl                                                                                               ;


  //tiempo atencion
  archivo << "param tt := " << endl                                                                                                 ;
  for (Cliente* i: instancia->get_clientes()){
    for (int p=0; p<instancia->get_cant_salidas(); p++){
      if (p*instancia->get_frec_salidas()>=instancia->get_inicio() && p*instancia->get_frec_salidas()<instancia->get_termino()){
        if (i == instancia->get_cliente(instancia->get_cant_clientes())){
          archivo << i->get_id_nodo()+1 << "\t" << p << "\t" << "0" << "\t\t"                                                       ;
        } else {
          archivo << i->get_id_nodo()+1 << "\t" << p << "\t" << i->get_tiempo_aten(p) << "\t\t"                                     ;
        }
      }
    }
    archivo << endl                                                                                                                 ;
  }
  for (int p=0; p<instancia->get_cant_salidas(); p++){
    if (p*instancia->get_frec_salidas()>=instancia->get_inicio() && p*instancia->get_frec_salidas()<instancia->get_termino()){
      archivo << instancia->get_cliente(instancia->get_cant_clientes())->get_id_nodo()+1+5000 << "\t" << p << "\t" << "0" << "\t\t" ;
    }
  }
  archivo << endl                                                                                                                   ;
  archivo << ";" << endl << endl                                                                                                    ;


  //costo atencion
  archivo << "param cc := " << endl                                                                                                 ;
  for (Cliente* i: instancia->get_clientes()){
    for (int p=0; p<instancia->get_cant_salidas(); p++){
      if (p*instancia->get_frec_salidas()>=instancia->get_inicio() && p*instancia->get_frec_salidas()<instancia->get_termino()){
        if (i == instancia->get_cliente(instancia->get_cant_clientes())){
          archivo << i->get_id_nodo()+1 << "\t" << p << "\t" << "0" << "\t\t"                                                       ;
        } else {
          archivo << i->get_id_nodo()+1 << "\t" << p << "\t" << i->get_costo_aten(p) << "\t\t"                                      ;
        }
      }
    }
    archivo << endl                                                                                                                 ;
  }
  for (int p=0; p<instancia->get_cant_salidas(); p++){
    if (p*instancia->get_frec_salidas()>=instancia->get_inicio() && p*instancia->get_frec_salidas()<instancia->get_termino()){
      archivo << instancia->get_cliente(instancia->get_cant_clientes())->get_id_nodo()+1+5000 << "\t" << p << "\t" << "0" << "\t\t" ;
    }
  }
  archivo << endl                                                                                                                   ;
  archivo << ";" << endl << endl                                                                                                    ;


  //tasa de fallo
  archivo << "param tf := " << endl                                                                                                 ;
  for (Cliente* i: instancia->get_clientes()){
    for (int p=0; p<instancia->get_cant_salidas(); p++){
      if (p*instancia->get_frec_salidas()>=instancia->get_inicio() && p*instancia->get_frec_salidas()<instancia->get_termino()){
        if (i == instancia->get_cliente(instancia->get_cant_clientes())){
          archivo << i->get_id_nodo()+1 << "\t" << p << "\t" << "0" << "\t\t"                                                       ;
        } else {
          archivo << i->get_id_nodo()+1 << "\t" << p << "\t" << i->get_tasas_fallo(p) << "\t\t"                                     ;
        }
      }
    }
    archivo << endl                                                                                                                 ;
  }
  for (int p=0; p<instancia->get_cant_salidas(); p++){
    if (p*instancia->get_frec_salidas()>=instancia->get_inicio() && p*instancia->get_frec_salidas()<instancia->get_termino()){
      archivo << instancia->get_cliente(instancia->get_cant_clientes())->get_id_nodo()+1+5000 << "\t" << p << "\t" << "0" << "\t\t" ;
    }
  }
  archivo << endl                                                                                                                   ;
  archivo << ";" << endl << endl                                                                                                    ;
  

  //tiempo de viaje
  archivo << "param t := " << endl                                                                                                                            ;
  for (Cliente* i: instancia->get_clientes()){
    for (Cliente *j: instancia->get_clientes()){
        if (i!=j){
        for (int p=0; p<instancia->get_cant_salidas(); p++){
          if (p*instancia->get_frec_salidas()>=instancia->get_inicio() && p*instancia->get_frec_salidas()<instancia->get_termino()){
            if (j == instancia->get_cliente(instancia->get_cant_clientes())){
              archivo << i->get_id_nodo()+1 << "\t" << j->get_id_nodo()+1+5000 << "\t" << p <<  "\t" << i->get_tiempo_hasta(j->get_id_cliente(), p) << "\t\t" ;
            } else {
              archivo << i->get_id_nodo()+1 << "\t" << j->get_id_nodo()+1 << "\t" << p <<  "\t" << i->get_tiempo_hasta(j->get_id_cliente(), p) << "\t\t"      ;
            }
          }
        }
        archivo << endl                                                                                                                                       ;
      }
    }
  }
  archivo << ";" << endl << endl                                                                                                                              ;
  

  //costo de viaje
  archivo << "param c := " << endl                                                                                                                           ;
  for (Cliente* i: instancia->get_clientes()){
    for (Cliente *j: instancia->get_clientes()){
        if (i!=j){
        for (int p=0; p<instancia->get_cant_salidas(); p++){
          if (p*instancia->get_frec_salidas()>=instancia->get_inicio() && p*instancia->get_frec_salidas()<instancia->get_termino()){
            if (j == instancia->get_cliente(instancia->get_cant_clientes())){
              archivo << i->get_id_nodo()+1 << "\t" << j->get_id_nodo()+1+5000 << "\t" << p <<  "\t" << i->get_costo_hasta(j->get_id_cliente(), p) << "\t\t" ;
            } else {
              archivo << i->get_id_nodo()+1 << "\t" << j->get_id_nodo()+1 << "\t" << p <<  "\t" << i->get_costo_hasta(j->get_id_cliente(), p) << "\t\t"      ;
            }
          }
        }
        archivo << endl                                                                                                                                      ;
      }
    }
  }
  archivo << ";" << endl << endl                                                                                                                             ;


  archivo.close() ;
}