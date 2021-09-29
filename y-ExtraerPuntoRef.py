
import sys
import os


def extraer_puntos(nombre_archivo):
  F1 = []
  F2 = []
  with open(nombre_archivo,"r") as archivo:
    for linea in archivo:
      f1 = ""
      f2 = ""
      bandera = True
      for i in linea:
        if bandera == True:
          if (i == " "):
            bandera = False
            continue
          f1 += i
        else:
          if (i == "\n"):
            break
          f2 += i
      F1.append(float(f1))
      F2.append(float(f2))
  return F1, F2


f1_min = 99999999
f1_max = 0
f2_min = 99999999
f2_max = 0


with os.scandir('Resultados/FrentesModelo/') as carpeta:
  archivos = [archivo.name for archivo in carpeta]

if sys.argv[1] in archivos:
  f1, f2 = extraer_puntos('Resultados/FrentesModelo/' + sys.argv[1])

  if min(f1) < f1_min:
    f1_min = min(f1)
  if max(f1) > f1_max:
    f1_max = max(f1)

  if min(f2) < f2_min:
    f2_min = min(f2)
  if max(f2) > f2_max:
    f2_max = max(f2)


direccion = 'Resultados/FrentesAlgoritmo/' + sys.argv[1][0:len(sys.argv[1])-4] + "/"

with os.scandir(direccion) as carpeta:
  archivos = [archivo for archivo in carpeta if archivo.name[0:len(sys.argv[1])-4] == sys.argv[1][0:len(sys.argv[1])-4]]
  
for i in archivos:
  f1, f2 = extraer_puntos(i)
  
  if min(f1) < f1_min:
    f1_min = min(f1)
  if max(f1) > f1_max:
    f1_max = max(f1)

  if min(f2) < f2_min:
    f2_min = min(f2)
  if max(f2) > f2_max:
    f2_max = max(f2)

  

f = open("Resultados/PuntoRef.txt","w")

f.write(str(round(f1_max*1.1, 3)) + " " + str(round(f2_max*1.1, 3)) + "\n")

f.write(str(f1_min) + " " + str(f1_max) + "\n")
f.write(str(f2_min) + " " + str(f2_max) + "\n")

f.close()

