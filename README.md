# Ejemplos de uso de thread (hilos)y semaforos en C++ 11 o superior

Una de las cosas que incluyó C++ 11 es el manejo de hilos. A pesar de que esta version tiene varios años, son pocas las personas que conocen, o hacen uso de estos recuros.

En estos archivos presento algunos ejemplos de uso de Hilos y también semáforos para exclusión al momneto de acceder a un recurso compartido. Recordar, que al incorporar hilos a un programa, vamos a tener varios "agentes" intentando acceder a un recurso que es único, y en el cual solamente un "agente" puede acceder. Esto significa que mientras este agente no termine el uso del recurso compartido, no se debe permitir que otro proceso acceda a él. Una de las opciones de control es mediante el uso de semáforos.


