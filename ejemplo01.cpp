#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
/**
 * Programa de ejemplo que simula la ejecucion de una serie de procesos en forma paralela
 * utilizando los thread de C++
 */


/**
 * Tarea 
 * @param int id Identificador de la tarea
 * @param int time Tiempo en milisegundos que debe esperar la tarea para ejecutar el siguiente loop
 */
void tarea(int id , int time ) 
{
    // Asumimos que la tarea se ejecutara 4 veces y tomara un tiempo time en cada ciclo.
    for(int i = 0 ; i < 4 ; i++)
    {
        std::cout << "Hilo : " << (id+1) << " en ejecución ( i = " << i << ")" << std::endl;
        // Esperamos por la tarea
        std::this_thread::sleep_for( std::chrono::milliseconds ( time  ) );
    }
}

int main() 
{   
    //Numero total de hilos
    const int num_hilos = 4;

    //Vector que mantiene 
    std::vector<std::thread> hilos;

    std::cout << "Iniciando hilos. " << std::endl;
    for (int i = 0; i < num_hilos; ++i) 
    {
        hilos.push_back( std::thread( tarea, i , ( (i+1) * 2000 / 3  )) );
    }

    
    for (auto& hilo : hilos) {
        hilo.join();
    }

    std::cout << "Todos los hilos han terminado." << std::endl;

    return 0;
}