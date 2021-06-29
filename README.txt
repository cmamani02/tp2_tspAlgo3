# tp2_tspAlgo3
Trabajo Practico N° 2- The Travelling Salesman Problem (TSP)

El código que resuelve el problema del enunciado está en el archivo tp2.cpp.
Para compilarlo se debe ejecutar el comando 
	make
en la consola.

Al ejecutarlo se le debe pasar un parámetro que indique cuál algoritmo se desea utilizar entre las siguientes opciones:
	- VMC: Fuerza bruta
	- HI: Backtracking con podas por factibilidad y optimalidad.
	- AGMH: Backtracking solamente con poda por factibilidad.
	- TSC-VMC: tabu search con memoria basada ultimas soluciones exploradas, usando VMC para solucion inicial.
	- TSC-HI: tabu search con memoria basada ultimas soluciones exploradas, usando HI para solucion inicial.
	- TSC-AGM: tabu search con memoria basada ultimas soluciones exploradas, usando AGMH para solucion inicial.
	- TSE-VMC: tabu search con memoria basada en estructura (aristas), usando VMC para solucion inicial.
	- TSE-HI: tabu search con memoria basada en estructura (aristas), usando HI para solucion inicial.
	- TSE-AGM: tabu search con memoria basada en estructura (aristas), usando AGMH para solucion inicial.

Para tabu search se pueden utilizar los siguientes parametros:
	- TAMANIO_MEMORIA: tamaño de la memoria para la lista tabu
	- PORCENTAJE_VECINDAD: es un valor numerico entero en el rango [1,..100]
	- ITERACIONES: cantidad de iteraciones a realizar por tabu search

Los parametros se utilizan de la siguiente manera: 
	./tp2 TSE-VMC TAMANIO_MEMORIA PORCENTAJE_VECINDAD ITERACIONES

Además se debe pasar la instancia por entrada estándar. Por ejemplo, para ejecutar TSE-AGM en una instancia INST1.TXT con 
tamaño de memoria = 280, porcentaje de vecindad 20, y 1000 iteraciones se debe correr el siguiente comando:
	cat INST1.txt | ./tp2 TSE-VMC 280 20 1000
La salida del programa es doble. Por la salida estándar se devuelve lo pedido por el enunciado. Por la STDERR se devuelve el tiempo de ejecución del algoritmo.

Experimentación:
La generación de instancias y corrida de experimentos de manera secuencia está programada en Python utilizando Jupyter Lab (https://jupyter.org/). Para ver los notebooks se debe instalar Jupyter Labs siguiendo las instrucciones en su web. Se recomienda seguir los pasos de instalación utilizando pip3.

Una vez instalado Jupyter Lab, abrir una consola en la carpeta python y correr el comando:
	jupyter lab

Allí, existen tres archivos:
	- generar-instancias.ipynb: genera las instancias descriptas en el trabajo y las ubica en la carpeta python/instancias.
	- experimentos.ipynb: corre los experimentos del trabajo y deja el resultado de todas las ejecuciones en un CSV en la carpeta python/resultados
	- analysis.ipynb: toma los resultados de las ejecuciones y genera todos los gráficos correspondientes.

