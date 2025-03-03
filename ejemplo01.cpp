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
    for(int i = 0 ; i < 3 ; i++)
    {
        std::cout << "Hilo : " << (id+1) << " en ejecución ( i = " << (i + 1) << ")" << std::endl;
        // Esperamos time milisegundos para que no se termine tan rapido
        std::this_thread::sleep_for( std::chrono::milliseconds ( time  ) );
    }
}

int main() 
{   
    //Numero total de hilos
    const int num_hilos = 3;

    //Vector que mantiene 
    std::vector<std::thread> hilos;

    std::cout << "Iniciando hilos. " << std::endl;
    for (int i = 0; i < num_hilos; ++i) 
    {
        hilos.push_back( std::thread( tarea, i , ( (i+1) * 2000 / 3  )) );
    }

    // Recorre los threads que tengo y va esperando a que todos terminen. s
    for (auto& hilo : hilos) {
        hilo.join();
    }

    // Hilos finalizados. 
    std::cout << "Todos los hilos han terminado." << std::endl;

    return 0;
}