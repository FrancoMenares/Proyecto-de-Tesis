#!/bin/bash


dir3="Resultados"
FrentesM="FrentesModelo"
FrentesA="FrentesAlgoritmo"
FrentesG="FrentesGrafico"
Hiper="HiperVolumen"
RutasA="RutasAlgoritmo"
SolucionesA="SolucionesAlgoritmo"
TiemposA="TiemposAlgoritmo"

Frente="Frente.txt"
Individuos="Individuos.txt"
Punto="PuntoRef.txt"
Rutas="Rutas.txt"
Seguimiento="Seguimiento.txt"

FrentesRE="FrentesReRuteo"
SolucionesRE="SolucionesReRuteo"


rm -r rm ${dir3}/${FrentesA}/* ${dir3}/${FrentesG}/* ${dir3}/${Hiper}/* 
rm -r rm ${dir3}/${RutasA}/* ${dir3}/${SolucionesA}/* ${dir3}/${TiemposA}/* 
rm -r rm ${dir3}/${FrentesRE}/* ${dir3}/${SolucionesRE}/*

clear