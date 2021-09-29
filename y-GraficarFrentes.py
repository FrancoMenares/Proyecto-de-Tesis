
import sys
import os
import matplotlib.pyplot as plt



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



def extraer_punto_ref():
  f1_min = ""
  f1_max = ""
  f2_min = ""
  f2_max = ""

  with open('Resultados/PuntoRef.txt',"r") as archivo:
    j = 0
    for linea in archivo:
      if j == 1:
        bandera = 1
        for i in linea:
          if i == " ":
            bandera = 0
            continue
          elif i == "\n":
            break

          if bandera == 1:
            f1_min = f1_min + i
          if bandera == 0:
            f1_max = f1_max + i

      if j == 2:
        bandera = 1
        for i in linea:
          if i == " ":
            bandera = 0
            continue
          elif i == "\n":
            break

          if bandera == 1:
            f2_min = f2_min + i
          if bandera == 0:
            f2_max = f2_max + i

      j += 1

  return float(f1_min), float(f1_max), float(f2_min), float(f2_max)



f1_min, f1_max, f2_min, f2_max = extraer_punto_ref()

with os.scandir('Resultados/FrentesModelo/') as carpeta:
  archivos = [archivo.name for archivo in carpeta]

if sys.argv[1] in archivos:
  f1, f2 = extraer_puntos('Resultados/FrentesModelo/' + sys.argv[1])

  f1 = [(i - f1_min)/(f1_max - f1_min) for i in f1]
  f2 = [(i - f2_min)/(f2_max - f2_min) for i in f2]

  plt.plot(f1, f2,'sr',linewidth=2)
  plt.plot(f1, f2,'--r',linewidth=2)

direccion = 'Resultados/FrentesAlgoritmo/' + sys.argv[1][0:len(sys.argv[1])-4] + "/"

with os.scandir(direccion) as carpeta:
  archivos = [archivo for archivo in carpeta if archivo.name[0:len(sys.argv[1])-4] == sys.argv[1][0:len(sys.argv[1])-4]]
  
for i in archivos:
  f1, f2 = extraer_puntos(i)

  f1 = [(i - f1_min)/(f1_max - f1_min) for i in f1]
  f2 = [(i - f2_min)/(f2_max - f2_min) for i in f2]

  plt.plot(f1, f2,'o',linewidth=2)

plt.grid()
plt.xlabel('Costo Operativo')
plt.ylabel('Tasa de Fallo')
plt.title('Instancia: ' + sys.argv[1][0:len(sys.argv[1])-4])
plt.savefig("Resultados/FrentesGrafico/" + sys.argv[1][0:len(sys.argv[1])-4] + ".png")  
plt.close()




