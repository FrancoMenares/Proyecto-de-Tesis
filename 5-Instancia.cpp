
#include "5-Instancia.h"


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

//------------ Impresiones -----------
void Instancia::imprimir_instancia(void){
  cout << "Deposito         : \t" << this->get_cliente(this->get_cant_clientes())->get_id_nodo() << endl ;
  cout << "N° clientes      : \t" << this->cant_clientes                                         << endl ;
  cout << "Clientes         : \t"                                                                        ;
  for (int i=0; i<this->cant_clientes; i++){
    cout << this->get_cliente(i)->get_id_nodo() << " "                                                   ;
    if (i+1 == this->cant_clientes){
      cout << endl                                                                                       ;
    }
  }
  cout << "N° Camiones      : \t" << this->cant_camiones                    << endl                      ;
  cout << "Cap. Camiones    : \t" << this->cap_camiones                     << endl                      ;
  cout << "Horizonte Plani. : \t" << this->inicio_horizonte << " - " << this->termino_horizonte << endl  ;
  cout << endl                                                                                           ;
}

