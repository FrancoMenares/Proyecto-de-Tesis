
#include "e-Instancia.h"


//--------------- cant_clientes ---------------
void Instancia::set_cant_clientes(int cant_clientes) {this->cant_clientes = cant_clientes ;}
int Instancia::get_cant_clientes(void)               {return this->cant_clientes          ;}


//--------------- Clientes ---------------
void Instancia::agregar_cliente(Cliente* cliente)    {this->clientes.push_back(cliente)   ;}
Cliente* Instancia::get_cliente(int pos)             {return this->clientes.at(pos)       ;}
vector <Cliente*> Instancia::get_clientes(void)      {return this->clientes               ;}


//--------------- cant_camiones ---------------
void Instancia::set_cant_camiones(int cant_camiones) {this->cant_camiones = cant_camiones ;}
int Instancia::get_cant_camiones(void)               {return this->cant_camiones          ;}


//--------------- cap_camiones ---------------
void Instancia::set_cap_camiones(int cap_camiones)   {this->cap_camiones = cap_camiones   ;}
int Instancia::get_cap_camiones(void)                {return this->cap_camiones           ;}


//--------------- inicio_horizonte ---------------
void Instancia::set_inicio(float inicio)             {this->inicio_horizonte = inicio     ;}
float Instancia::get_inicio(void)                    {return this->inicio_horizonte       ;}


//--------------- termino_horizonte ---------------
void Instancia::set_termino(float termino)           {this->termino_horizonte = termino   ;}
float Instancia::get_termino(void)                   {return this->termino_horizonte      ;}

    
//------------ cant_salidas -------------
void Instancia::set_cant_salidas(int cant_salidas)   { this->cant_salidas = cant_salidas  ;}
int Instancia::get_cant_salidas(void)                { return this->cant_salidas          ;} 

    
//------------ frec_salidas -------------
void Instancia::set_frec_salidas(float frec_salidas) { this->frec_salidas = frec_salidas  ;}
float Instancia::get_frec_salidas(void)              { return this->frec_salidas          ;}


//------------ Impresiones -----------
void Instancia::verificar_instancia(void){
  for (Cliente* i: this->clientes){
    for (Cliente* j: this->clientes){
      for (int p=0; p<this->get_cant_salidas(); p++){
        if (i->get_tiempo_hasta(j->get_id_cliente(), p) < 0){
          cerr << "El cliente " << i->get_id_nodo()+1 << " no esta conectado a la red" << endl << endl ;
		      exit(0)                                                                          ;
        }
      }
    }
  }

  for (int i=0; i<this->cant_clientes; i++){
    if (this->clientes.at(i)->get_id_nodo() == this->clientes.at(this->cant_clientes)->get_id_nodo()){
      cerr << "El cliente " << this->clientes.at(i)->get_id_nodo()+1 << " tambien es el deposito" << endl << endl ;
      exit(0)                                                                             ;
    }

    for (int j=0; j<this->cant_clientes; j++){
      if (i != j){
        if (this->clientes.at(i)->get_id_nodo() == this->clientes.at(j)->get_id_nodo()){
          cerr << "Los clientes numero " << i << " y " << j << " son iguales" << endl << endl ;
		      exit(0)                                                                             ;
        }
      }
    }
  }
}


//------------ Impresiones -----------
void Instancia::imprimir_instancia(void){
  cout << "-----------------------------------------------------------------"       << endl ;
  cout << "Deposito         : \t" << clientes.at(cant_clientes)->get_id_nodo()+1    << endl ;
  cout << "N° Clientes      : \t" << this->cant_clientes                            << endl ;
  cout << "Clientes         : \t"                                                           ;
  for (int i=0; i<this->cant_clientes; i++){
    if ((i+1)%11 == 0 && (i+1) != this->cant_clientes){
      cout << endl << "                   \t"                                               ;
    }
    cout << this->get_cliente(i)->get_id_nodo()+1 << " "                                    ;
    
    if (i+1 == this->cant_clientes){
      cout                                                                          << endl ;
    }

  }
  cout << "N° Camiones      : \t" << this->cant_camiones                            << endl ;
  cout << "Cap. Camiones    : \t" << this->cap_camiones                             << endl ;
  cout << "Horizonte Plani. : \t" << inicio_horizonte << " - " << termino_horizonte << endl ;
  cout << "-----------------------------------------------------------------"       << endl ;
  cout                                                                              << endl ;
}

