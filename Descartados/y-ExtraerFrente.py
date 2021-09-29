
import sys
import os


#python3 y-ExtraerFrente.py ${instancia} ${semilla} ${lambda} ${p_aceptacion} ${p_cruce} ${p_mutacion} ${generaciones} ${dir3}/${Frente}


puntos = []
with open(sys.argv[8],"r") as archivo:
  for linea in archivo:
    punto = []
    f1 = ""
    f2 = ""
    bandera1 = True

    for i in linea:
      if bandera1 == True:
        if (i == " "):
          bandera1 = False
          continue
        f1 += i
      else:
        if (i == "\n"):
          bandera1 = False
          break
        f2 += i
    
    punto.append(int(float(f1)*100))
    punto.append(int(float(f2)*100))
    punto.append(True)
    puntos.append(punto)


for i in range(len(puntos)):
  if puntos[i][2] == True:
    for j in range(i+1, len(puntos)):

      if puntos[i][0] == puntos[j][0] and puntos[i][1] == puntos[j][1]:
        puntos[j][2] = False
        continue

      if puntos[i][0] == puntos[j][0] and puntos[i][1] < puntos[j][1]:
        puntos[j][2] = False
        continue
      elif puntos[i][0] == puntos[j][0] and puntos[i][1] > puntos[j][1]:
        puntos[i][2] = False
        break

      if puntos[i][0] < puntos[j][0] and puntos[i][1] == puntos[j][1]:
        puntos[j][2] = False
        continue
      elif puntos[i][0] > puntos[j][0] and puntos[i][1] == puntos[j][1]:
        puntos[i][2] = False
        break

puntos.sort(key=lambda x: x[0])


os.makedirs('Resultados/FrentesAlgoritmo/' + sys.argv[1][0:len(sys.argv[1])-4], exist_ok=True)

nombre = "Resultados/FrentesAlgoritmo/" + sys.argv[1][0:len(sys.argv[1])-4] + "/" + sys.argv[1][0:len(sys.argv[1])-4] + "-" + sys.argv[2] + "-" + sys.argv[3] + "-" + sys.argv[4] + "-" + sys.argv[5] + "-" + sys.argv[6] + "-" + sys.argv[7] + ".txt"

g = open(nombre,"w")

for i in puntos:
  if i[2] == True:
    g.write(str(i[0]/100) + " " + str(i[1]/100) + "\n")

g.close()




