# Ejemplos de uso de thread (hilos)y semaforos en C++ 11 o superior

Una de las cosas que incluyó C++ 11 es el manejo de hilos. A pesar de que esta version tiene varios años, son pocas las personas que conocen, o hacen uso de estos recuros.

En estos archivos presento algunos ejemplos de uso de Hilos y también semáforos para exclusión al momneto de acceder a un recurso compartido. Recordar, que al incorporar hilos a un programa, vamos a tener varios "agentes" intentando acceder a un recurso que es único, y en el cual solamente un "agente" puede acceder. Esto significa que mientras este agente no termine el uso del recurso compartido, no se debe permitir que otro proceso acceda a él. Una de las opciones de control es mediante el uso de semáforos.

Para compilar los ejemplos usar g++, por ejemplo. 

```
g++ ejemplo01.cpp -o ejemplo01 
```


## Ejemplo01.cpp

Es un ejemplo sencillo que lanza una serie de hilos donde cada uno de los hilos se ejecuta cada X milisegundos.

Ejemplo de salida : 

```
Iniciando hilos. 
Hilo : 1 en ejecución ( i = 1) Tiempo ejecucion 0
Hilo : 2 en ejecución ( i = 1) Tiempo ejecucion 0
Hilo : 3 en ejecución ( i = 1) Tiempo ejecucion 0
Hilo : 4 en ejecución ( i = 1) Tiempo ejecucion 0
Hilo : 1 en ejecución ( i = 2) Tiempo ejecucion 666
Hilo : 1 en ejecución ( i = 3) Tiempo ejecucion 1332
Hilo : 2 en ejecución ( i = 2) Tiempo ejecucion 1333
Hilo : 3 en ejecución ( i = 2) Tiempo ejecucion 2000
Hilo : 2 en ejecución ( i = 3) Tiempo ejecucion 2666
Hilo : 4 en ejecución ( i = 2) Tiempo ejecucion 2666
Hilo : 3 en ejecución ( i = 3) Tiempo ejecucion 4000
Hilo : 4 en ejecución ( i = 3) Tiempo ejecucion 5332
Todos los hilos han terminado.
```

# A futuro.

Voy a agregar mas ejemplos usando semaforos, colas y crearé un archivo Makefile para compilar todos los ejemplos.